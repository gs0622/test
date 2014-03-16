#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
	int i, s, n = (argc>1)? atoi(argv[1]): 10/*default*/;
	struct timespec t;

	for (i=0; i<n; i++) {
		clock_gettime(CLOCK_MONOTONIC, &t);
		srand((int)t.tv_nsec);
		s = rand()%100;
		printf("%2d%c", s, (i==(n-1))? '\n': ' ');
	}
}

