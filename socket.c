#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>

void server(void)
{
	char buf[256];
	int fd, ret, cfd, i=0;
	struct sockaddr_in sa;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	sa.sin_port = htons(6666);
	ret = bind(fd, (const struct sockaddr *)&sa, sizeof(sa));
	if (-1==(ret=listen(fd, 10))) {
		printf("failed in listen\n");
	}
	cfd = accept(fd, (struct sockaddr*)0, 0);
	while (1) {
		sprintf(buf, "hello %d\n\r", i++);
		printf("s: %s", buf);
		write(cfd, buf, strlen(buf));
		//close(cfd);
		sleep(3);
	}
	close(cfd);
}

void client(void)
{
	char buf[256];
	int fd, ret, rd;
	struct sockaddr_in sa;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr("127.0.0.1");
	sa.sin_port = htons(6666);
	if (0>(ret=connect(fd, (struct sockaddr *)&sa, sizeof(sa)))) {
		printf("failed in listen\n");
		return;
	}
	while (0 < (rd=read(fd, buf, sizeof(buf)-1))) {
                buf[rd]=0;
		printf("c: %s\n", buf);
	}
}

int main(void)
{
	pid_t child;
	child=fork();
	if (child<0) {
		printf("fork failed\n");
		exit(-1);
	}
	if (child>0) {
		//printf("parent: cpid=%d mypid=%d\n", child, getpid());
		server();
	} else {
		//printf("child : ppid=%d mypid=%d\n", getppid(), getpid());
		client();
	}
	return 0;
}

