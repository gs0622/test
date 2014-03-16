#include <stdio.h>
#include <unistd.h>

int main(void)
{
	pid_t child;
	child=fork();
	if (0<=child) {
		if (child>0) {
			printf("parent: cpid=%d mypid=%d\n", child, getpid());
		} else {
			printf("child : ppid=%d mypid=%d\n", getppid(), getpid());
		}
	} else {
		printf("fork failed\n");
	}
	return 0;
}

