#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *create_array(int n)
{
	int i, *p;

	if (0==n) return NULL;
	p = malloc((sizeof(int))*n);
	srand((unsigned int)time(NULL));

	for (i=0; p && i<n; i++) {
		p[i] = rand()%100;
	}
	return p;
}

void print_array(int *p, int n)
{
	for (p;n>0;n--,p++) {
		printf("%.2d%s", *p, ((n-1)>0)? " ":"\n");
	}
}
void swap(int *p, int *q)
{
	int tmp = *p;
	*p = *q;
	*q = tmp;
}

static int cmp(const void *p, const void *q)
{
	int i = *((int *)p), j = *((int *)q);
	return (i-j);
}

int mode(int *p, int n, int *c)
{
	int i, j, m, d, t, x;
	if (!p || !c) return -1;
	m = p[0];
	x = *c;
	for (i=1; i<n; i++) {
		d=1;
		swap(&p[i], &p[0]);
		for (j=1;j<n;j++) if (p[j]==p[0]) d++;
		swap(&p[0], &p[i]);
		if (d>x) {x=d; m=p[i];}
		if (*c>1 && d==x) m=p[i]; /*tweak for 2nd in*/
	}
	*c = x;
	return m;
}

int main(int argc, char **argv)
{
	int n, *p, m, m1, i, j, c=1, d=1;
	n = (argc>1)? atoi(argv[1]) : 10;
	p = create_array(n);
	qsort(p, n, 4, cmp);
	print_array(p, n);
	m = mode(p, n, &c);
	printf("\nm=%.2d c=%.2d\n", m, c);
	m1 = mode(p, n, &c);
	if (m1!=m )printf("\nm=%.2d c=%.2d\n", m1, c);
	return 0;
}

