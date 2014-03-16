#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *create_array(int n)
{
	int i, *p;

	p = malloc((sizeof(int))*n);
	srand((unsigned int)time(NULL));
	for (i=0; p && i<n; i++) {
		p[i] = rand()%1000;
	}
	return p;
}

void print_array(int *p, int n)
{
#if 0
	for (p;n>0;n--,p++) {
		printf("%.3d%s", *p, ((n-1)>0)? " ":"\n");
	}
#endif
}

void swap(int *p, int *q)
{
	int tmp = *p;
	*p = *q;
	*q = tmp;
}

int bubblesort(int *p, int n)
{
	int i, j;
	for (i=n-1; i>0; i--)
		for (j=0; j<i; j++) {
			//if (p[j]>p[j+1]) swap(&p[j], &p[j+1]); /*ascending*/
			if (p[j]<p[j+1]) swap(&p[j], &p[j+1]); /*descending*/
		}
}

int main(int argc, char **argv)
{
	int n, *p;
	n = (argc>1)? atoi(argv[1]) : 10;
	p = create_array(n);
	print_array(p, n);
	bubblesort(p, n);
	print_array(p, n);
	return 0;
}

