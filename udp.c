#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <error.h>

void server(void)
{
	char buf[256];
	int fd, rd, tmp;
	struct sockaddr_in sa, ca;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	sa.sin_port = htons(6666);
	bind(fd, (const struct sockaddr *)&sa, sizeof(sa));
	//while (0 < (rd=read(fd, buf, sizeof(buf)-1))) {
	tmp=sizeof(&ca);
	while (1) {
                bzero(&buf, sizeof(buf));
                //rd=recvfrom(fd, (void *)buf, sizeof(buf)-1, 0, (struct sockaddr *)&ca, &tmp);
                rd=recvfrom(fd, (void *)buf, sizeof(buf)-1, 0, 0, 0);
                printf("rd=%d\n", rd);
                buf[rd]=0;
		printf("s: %s\n", buf);
                sleep(3);
	};
	close(fd);
}

void client(void)
{
        char buf[256];
	int fd, ret, wr, i=0;
	struct sockaddr_in sa;
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr("127.0.0.1");
	sa.sin_port = htons(6666);
	do {
		wr = sprintf(buf, "hello %d\n\r", i++);
		buf[wr]=0;
		printf("c: %s\n", buf);
                sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&sa, sizeof(sa));
                sleep(3);
	} while (1);
	close(fd);
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

