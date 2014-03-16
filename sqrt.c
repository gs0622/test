#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
		printf("%.2d%s", *p, ((n-1)>0)? "+":"=\n");
	}
}

int sum(int *p, int n)
{
	int i, s;

	for (i=0,s=0; i<n; i++) s=s+p[i];
	return s;
}

int main(int argc, char **argv)
{
	int n, *p, s, a, i;
	double d;
	n = (argc>1)? atoi(argv[1]) : 10;
	p = create_array(n);
	print_array(p, n);
	s = sum(p, n);
	a = s/n;
	for (i=0,d=0; i<n; i++) d+=(double)(p[i]-a)*(double)(p[i]-a);
	d = sqrt(d/n);
	printf("%d\navg=%d sd=%f\n", s, s/n, d);
	return 0;
}
