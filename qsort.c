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
		/*printf("%d: %d\n", i, p[i]);*/
	}
	return p;
}

void print_array(int *p, int n)
{
	for (p;n>0;n--,p++) {
		printf("%.2d%s", *p, ((n-1)>0)? " ":"\n");
	}
}

static int cmp(const void *p, const void *q)
{
	int i = *((int *)p), j = *((int *)q);
	/*printf("%d vs %d\n", i, j);*/
	return (i-j);
}

int main(int argc, char **argv)
{
	int n, *p;
	n = (argc>1)? atoi(argv[1]) : 10;
	p = create_array(n);
	print_array(p, n);
	qsort(p, n, 4, cmp);
	print_array(p, n);
	return 0;
}
