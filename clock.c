#include <stdio.h>
#include <time.h>

int main(void)
{
	clock_t c;
        unsigned int i;
        printf("csz=%ld cps=%ld\n", sizeof(c), CLOCKS_PER_SEC);
	while (1) {
		c=clock();
		printf("%lu\n", (unsigned long)c/CLOCKS_PER_SEC);
		//sleep(1);
                for (i=0x0fffffff; i>0; i--);
	}
	return 0;
}
