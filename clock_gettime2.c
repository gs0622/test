#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
	struct timespec t;
	int n = (argc>1)? atoi(argv[1]) : 10000;
	while (n--) clock_gettime(CLOCK_MONOTONIC, &t);
	return 0;
}
