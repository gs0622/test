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

int reverse(int *p, int n)
{
	int i, tmp;
	for (i=0;i<(n/2);i++) swap(&p[i], &p[n-1-i]);
}

int main(int argc, char **argv)
{
	int n, *p, m, m1, i, j, c=1, d=1;
	n = (argc>1)? atoi(argv[1]) : 10;
	p = create_array(n);
	qsort(p, n, 4, cmp);
	print_array(p, n);
	reverse(p, n);
	print_array(p, n);
	return 0;
}

