#include <stdio.h>
#include <unistd.h>

int main(void)
{
        char *buf[32];
        gethostname(buf,sizeof(buf));
	printf("localhost=%s\n", buf);
	return 0;
}
