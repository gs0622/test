#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t s;
	while (1) {
		s=time(0);
		printf("%d\n", s);
		sleep(1);
	}
	return 0;
}
