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

int partition(int *p, int left, int right)
{
	int i, pivot, idx = left;

	pivot = p[idx];
	swap(&p[idx], &p[right]);
	for (i=left; i<right; i++) {
		if (p[i] < pivot) {
			swap(&p[idx++], &p[i]);
		}
	}
	swap(&p[right], &p[idx]);
	return idx;
}

void quicksort(int *p, int left, int right)
{
	int idx;
	if (left > right) return;
	idx = partition(p, left, right);
	quicksort(p, left, idx-1);
	quicksort(p, idx+1, right);
}

int main(int argc, char **argv)
{
	int n, *p;
	n = (argc>1)? atoi(argv[1]) : 10;
	p = create_array(n);
	print_array(p, n);
	quicksort(p, 0, n-1);
	print_array(p, n);
	return 0;
}

