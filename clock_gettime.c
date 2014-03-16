#include <stdio.h>
#include <time.h>

int main(void)
{
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	printf("%lu, %lu\n", t.tv_sec, t.tv_nsec);
	clock_gettime(CLOCK_REALTIME, &t);
	printf("%lu, %lu\n", t.tv_sec, t.tv_nsec);
	return 0;
}
