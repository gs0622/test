/* Simulated annealing task mapping algorithm
 * 
 * The algorithm was written by Heikki Orsila <heikki.orsila@iki.fi> in 2011.
 * The code is in public domain. You may do anything you want with the code.
 *
 * General overview of the problem and algorithm is presented in [1], [2]
 * and [3]:
 *
 * [1] Heikki Orsila, Erno Salminen, Timo D. Hamalainen,
 * "Parameterizing Simulated Annealing for Distributing Kahn Process
 * Networks on Multiprocessor SoCs", Symposium on System-on-Chip,
 * Tampere, Finland, October 5-7, 2009.
 * http://zakalwe.fi/~shd/publications/orsila_parameterizing_simulated_annealing_for_distributing_kahn_process_networks_2009.pdf
 *
 * [2] Heikki Orsila, "Optimizing Algorithms for Task Graph Mapping on
 * Multiprocessor System on Chip", PhD Thesis, Tampere University of
 * Technology, Department of Computer Systems, 2011.
 * http://zakalwe.fi/~shd/publications/optimizing-algorithms-for-task-graph-mapping-on-multiprocessor-system-on-chip-2011-orsila.pdf
 *
 * [3] Heikki Orsila, Tero Kangas, Erno Salminen, Timo D. Hamalainen,
 * "Parameterizing Simulated Annealing for Distributing Task Graphs on
 * Multiprocessor SoCs", International Symposium on System-on-Chip
 * 2006, Tampere, Finland, November 14-16, 2006, pp. 73-76.
 * http://zakalwe.fi/~shd/publications/orsila_parameterizing_simulated_annealing_2006.pdf
 *
 * Notice that the objective function is dummy. It does not work
 * properly with the autotemp() function. Autotemp() is intended to
 * work properly when execution time is optimized. The objective
 * function should be a simulator that determines the execution time
 * for a mapping.
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

#define MAX(a, b) (((a) >= (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define NPES 5
#define NTASKS 32
#define PE_FREQ 100000000

#define DIVISOR_LOWER_LIMIT 1E-14

struct mapping {
        /* Number of PEs */
        unsigned int npes;
        /* number of abstract operations per second for each PE */
        double *peperf;

        unsigned int ntasks;
        unsigned int *mappings; /* contains PE id for each task */

        /* number of abstract computation operations for each task */
        unsigned int *ops;
        int *isstatic;
};

struct sa;

struct sa {
        unsigned int L;

        double T0;
        double Tf;
        double Tt;
        double temperature_coefficient;
        double normalization_coefficient;

        double (*acceptor)(double dE, double T, const struct sa *params);
        void (*move)(struct mapping *Snew, const struct mapping *S);
        double (*objective)(const struct mapping *S);
        double (*schedule)(double T, const struct sa *params);
};

static int randfd = -1;
static double randdmax;

static void *xmalloc(size_t size)
{
        void *p = malloc(size);
        assert(p != NULL);
        return p;
}

static void *xcalloc(size_t nmemb, size_t size)
{
        void *p = calloc(nmemb, size);
        assert(p != NULL);
        return p;
}

static void copy_mapping(struct mapping *Starget, const struct mapping *S)
{
        size_t mappingssize = S->ntasks * sizeof(S->mappings[0]);
        assert(Starget->ntasks == S->ntasks);
        memcpy(Starget->mappings, S->mappings, mappingssize);
}

static struct mapping *fork_mapping(const struct mapping *S)
{
        size_t mappingssize = S->ntasks * sizeof(S->mappings[0]);
        struct mapping *Snew = xmalloc(sizeof *Snew);
        *Snew = *S;
        Snew->mappings = xmalloc(mappingssize);
        memcpy(Snew->mappings, S->mappings, mappingssize);
        return Snew;
}

static void free_mapping(struct mapping *S)
{
        free(S->mappings);
        memset(S, 0, sizeof *S);
        free(S);
}

static void print_mapping(const struct mapping *S)
{
        int taskid;
        for (taskid = 0; taskid < S->ntasks; taskid++)
                printf("%d ", S->mappings[taskid]);
        printf("\n");
}

static double randd(double a, double b)
{
        ssize_t ret;
        char buf[8];
        uint64_t u;

        if (randfd < 0) {
                randfd = open("/dev/urandom", O_RDONLY);
                randdmax = pow(2.0, 64.0);
        }

        assert(randfd >= 0);

        ret = read(randfd, buf, sizeof buf);
        assert(ret == 8);

        memcpy(&u, buf, sizeof u);
        return a + (((double) u) / randdmax) * (b - a);
}

static unsigned int randui(unsigned int a, unsigned int b)
{
        assert(a <= b);
        return a + randd(0.0, 1.0) * (b - a);
}


/*
 * A dummy objective function that tries to balance execution time load
 * on PEs. The objective value is 1E-6 + maxload - minload,
 * where maxload is the total execution time on a PE that is most loaded,
 * and minload is the total execution time on a PE that is least loaded.
 * Therefore, objective reaches minimum == 1E-6 when minload == maxload.
 */
static double dummy_objective(const struct mapping *S)
{
        double *peload = xcalloc(S->npes, sizeof peload[0]);
        unsigned int taskid;
        unsigned int peid;
        double minload;
        double maxload;
        double time;

        for (taskid = 0; taskid < S->ntasks; taskid++) {
                peid = S->mappings[taskid];
                time = S->ops[taskid] / S->peperf[peid];
                peload[S->mappings[taskid]] += time;
        }

        minload = maxload = peload[0];
        for (peid = 1; peid < S->npes; peid++) {
                minload = MIN(minload, peload[peid]);
                maxload = MAX(maxload, peload[peid]);
        }
        return 1E-6 + maxload - minload;
}

static void move_one_task(struct mapping *Snew, const struct mapping *S)
{
        unsigned int taskid;
        unsigned int peid;

        copy_mapping(Snew, S);

        /*
         * Move random task to a random PE so that the new PE is different
         * than the current one.
         */
        taskid = randui(0, S->ntasks);
        peid = randui(0, S->npes - 1);
        if (peid >= Snew->mappings[taskid])
                peid++;
        if (Snew->isstatic[taskid] == 0)
                Snew->mappings[taskid] = peid;
}

static double exponential_acceptor(double dE, double T, const struct sa *params)
{
        double exponent;
        double divisor = params->normalization_coefficient * T;
        if (divisor < DIVISOR_LOWER_LIMIT)
                return 0.0;
        exponent = -dE / divisor;
        if (exponent >= 0)
                return 1.0;
        return exp(exponent);
}

static double geometric_schedule(double T, const struct sa *params)
{
        return params->temperature_coefficient * T;
}

struct mapping *simulated_annealing(struct mapping *S0, const struct sa *params)
{
        unsigned int k = 0;
        unsigned int rejects = 0;
        double E;
        double Ebest;
        double Enew;
        struct mapping *S;
        struct mapping *Sbest;
        struct mapping *Snew;
        double diff;
        double T = params->T0;

        E = params->objective(S0);
        Ebest = E;
        S = fork_mapping(S0);
        Sbest = fork_mapping(S0);
        Snew = fork_mapping(S0);

        while (1) {
                printf("Accepted objective: %f\n", E);
                params->move(Snew, S);
                Enew = params->objective(Snew);
                diff = Enew - E;
                if (diff < 0 || randd(0, 1.0) < params->acceptor(diff, T, params)) {
                        copy_mapping(S, Snew);
                        E = Enew;
                        if (Enew < Ebest) {
                                copy_mapping(Sbest, Snew);
                                Ebest = Enew;
                                printf("A new best solution found: %f\n", params->objective(Sbest));
                        }
                        rejects = 0;
                } else if (T <= params->Tf) {
                        if (T <= params->Tt || rejects >= params->L)
                                break;
                        rejects++;
                }

                k++;
                if (k == params->L) {
                        T = params->schedule(T, params);
                        k = 0;
                }
        }

        free_mapping(S);
        free_mapping(Snew);

        return Sbest;
}

/* double comparator for qsort */
static int compare_double(const void *a, const void *b)
{
        const double *x = a;
        const double *y = b;
        if (x < y)
                return -1;
        if (y < x)
                return 1;
        return 0;
}

/*
 * Compute the initial and final temperature with the automatic
 * temperature selection algorithm presented in:
 *
 * Heikki Orsila, Erno Salminen, Timo D. Hamalainen, "Parameterizing
 * Simulated Annealing for Distributing Kahn Process Networks on
 * Multiprocessor SoCs", Symposium on System-on-Chip, Tampere,
 * Finland, October 5-7, 2009.
 */
static void autotemp(struct sa *params, const struct mapping *S)
{
        const int pivotpercentage = 5;
        const double k = 2.0;
        int i;
        double perf;
        double maxperf;
        double minperf;
        double time;
        double maxtime = 0.0;
        double mintime = 1E10;
        double maxsum = 0.0;
        double minsum = 0.0;
        double *cycles;
        double pivotvalue;

        /* Compute minimum and maximum operations per second for PEs */
        minperf = 1E10;
        maxperf = 0.0;
        for (i = 0; i < S->npes; i++) {
                perf = S->peperf[i]; /* Get operations/s value for the PE */
                assert(perf > 0);
                minperf = MIN(perf, minperf);
                maxperf = MAX(perf, maxperf);
        }

        /* For each process, compute sum of computation cycles */
        cycles = xmalloc(sizeof(cycles[0]) * S->ntasks);
        assert(cycles != NULL);
        for (i = 0; i < S->ntasks; i++)
                cycles[i] = S->ops[i];

        /* Note, sorting cycles array does not break the algorithm */
        qsort(cycles, S->ntasks, sizeof(cycles[0]), compare_double);

        for (i = 0; i < S->ntasks; i++) {
                time = cycles[i] / maxperf;
                minsum += time;

                mintime = MIN(mintime, time);

                time = cycles[i] / minperf;
                maxsum += time;

                maxtime = MAX(maxtime, time);
        }

        pivotvalue = cycles[(S->ntasks * pivotpercentage) / 100] / maxperf;
        mintime = MAX(mintime, pivotvalue);

        free(cycles);
        cycles = NULL;

        mintime = MAX(mintime, 1.0 / maxperf);
        assert(maxtime > 0.0);

        params->T0 = MIN(k * maxtime / minsum, 1.0);
        params->Tf = MIN(mintime / (k * maxsum), 1.0);
        params->Tt = params->Tf / 2;

        assert(params->T0 > 0.0);
        assert(params->Tf > 0.0);
        assert(params->Tt > 0.0);
        assert(params->T0 >= params->Tf);
        assert(params->Tf >= params->Tt);

        printf("SA_autotemp: k: %e T0: %.9f Tf: %.9f\n", k, params->T0, params->Tf);
}

static void initialize_parameters(struct sa *params, const struct mapping *S)
{
        *params = (struct sa) {.L = S->ntasks * (S->npes - 1),
                               .temperature_coefficient = 0.95,
                               .acceptor = exponential_acceptor,
                               .move = move_one_task,
                               .objective = dummy_objective,
                               .schedule = geometric_schedule,
                              };

        params->normalization_coefficient = 0.5 * params->objective(S);

        autotemp(params, S);
}

struct mapping *create_mapping(unsigned int npes, unsigned int ntasks)
{
        unsigned int taskid;
        unsigned int peid;
        struct mapping *S = xmalloc(sizeof(struct mapping));

        assert(npes > 0);
        assert(ntasks > 0);

        S->npes = npes;
        S->ntasks = ntasks;

        S->peperf = xmalloc(S->npes * sizeof S->peperf[0]);
        for (peid = 0; peid < S->npes; peid++)
                S->peperf[peid] = PE_FREQ;

        S->mappings = xcalloc(S->ntasks, sizeof S->mappings[0]);

        S->ops = xmalloc(S->ntasks * sizeof S->ops[0]);
        for (taskid = 0; taskid < S->ntasks; taskid++)
                S->ops[taskid] = 1000 + (taskid * 1111) % 4000;

        S->isstatic = xcalloc(S->ntasks, sizeof S->isstatic[0]);
        S->isstatic[0] = 1; /* task 0 is stays on the initial mapping */

        return S;
}

int main(int argc, char *argv[])
{
        struct sa params;
        struct mapping *S0 = create_mapping(NPES, NTASKS);
        struct mapping *Sf;
        double C0;
        double Cf;

        initialize_parameters(&params, S0);

        /* Sf is the optimized mapping */
        Sf = simulated_annealing(S0, &params);

        C0 = params.objective(S0);
        Cf = params.objective(Sf);
        printf("Initial objective: %f\n", C0);
        printf("Final objective: %f\n", Cf);
        printf("Gain: %.3f\n", C0 / Cf);

        printf("Final mapping: ");
        print_mapping(Sf);

        return 0;
}

