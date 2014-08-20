#include <stdio.h>
#include <time.h>
#include <limits.h>

double get_time(void)
{
    struct timespec ts;
    double now;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    now = ts.tv_sec + (double)ts.tv_nsec/1000000000L;
    return now;
}

int main(void)
{
    double t;
    t = get_time();
    printf("%f\n", t);
    printf("%.10f\n", t);
    sleep(1);
    t = get_time();
    printf("%f\n", t);
    printf("%.10f\n", t);

}
