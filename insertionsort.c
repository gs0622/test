#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define SWAP
#ifdef SWAP
static void swap(int *p, int *q)
{
	int tmp = *p;
	*p = *q;
	*q = tmp;
}
#endif

static int *create_array(int n)
{
	int i, *p;

	p = malloc((sizeof(int))*n);
	srand((unsigned int)time(NULL));
	for (i=0; p && i<n; i++) {
		p[i] = rand()%100;
	}
	return p;
}

static void print_array(int *p, int n)
{
	for (;p && n>0;n--,p++) printf("%.2d%s", *p, ((n-1)>0)? " ":"\n");
}

/* insertion sort, a.k.a. selection sort, p == array, n = size
 * reference: http://en.wikipedia.org/wiki/Insertion_sort
 */
void insertionsort(int *p, int n)
{
#ifdef SWAP
	int i, j;
    for (i=1;p && i<n;i++) {
        j=i;
        while (j && p[j-1]>p[j]) /*ascending order*/
            swap(&p[j-1], &p[j]), j-=1; /*slightly faster then swap version*/
#else
	int i, j, key;
    for (i=1;p && i<n;i++) {
        j=i, key=p[j]; /*O(1) space complexity*/
        while (j && p[j-1]>key) /*ascending order*/
            p[j]=p[j-1], j-=1; /*slightly faster then swap version*/
        p[j]=key;
#endif
    }
}

int main(int argc, char **argv)
{
	int n, *p;
	n = (argc>1)? atoi(argv[1]) : 10;
	p = create_array(n);
	print_array(p, n);
	//insertionsort(p, n);
    insertionsort(p, n);
	print_array(p, n);
	return 0;
}
