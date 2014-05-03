#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *create_array(int n)
{
	int i, *p;
	if (0==n) return NULL;
	p = malloc((sizeof(int))*n);
	srand((unsigned int)time(NULL));
	for (i=0; p && i<n; i++) p[i] = rand()%100;
	return p;
}

void print_array(int *p, int n)
{
	for (;n>0;n--,p++) {
		printf("%.2d%s", *p, ((n-1)>0)? " ":"\n");
	}
}

static int cmp(const void *p, const void *q)
{
	int i = *((int *)p), j = *((int *)q);
	return (i-j);
}

#if 0
int binarysearch(int *p, int n, int v)
{
	int left = 0, right = n-1, mid, tmp;
	while (left <= right) {
		mid = (left + right) / 2;
		tmp = p[mid];
		if (tmp == v) return 1;
		else if (tmp > v) right = mid - 1;
		else left = mid + 1;
	}
	return 0;
}
#else
int binsearch(int *p, int left, int right, int v)
{
    int mid = (left + right) / 2, tmp = p[mid];
	if (left > right) return 0;
    if (tmp == v) return 1;
    else if (tmp > v) return binsearch(p, left, mid-1, v);
    else return binsearch(p, mid+1, right, v);
}

int binarysearch(int *p, int n, int v)
{
    int left = 0, right = n-1;
    return binsearch(p, left, right, v);
}
#endif

int main(int argc, char **argv)
{
	int n, *p, v;
	n = (argc>1)? atoi(argv[1]) : 10;
	p = create_array(n);
	/*print_array(p, n);*/
	qsort(p, n, 4, cmp);
	print_array(p, n);
    while (scanf("%d", &v)!=EOF) {
        printf("%d %s\n", v, binarysearch(p, n, v)? "found":"not found");
    }
	return 0;
}
