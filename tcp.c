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
		perror("listen");
		close(fd);
		exit(0);
	}
	cfd = accept(fd, (struct sockaddr*)0, 0);
	while (1) {
		sprintf(buf, "hello %d", i++);
		printf("s: %s\n", buf);
		write(cfd, buf, strlen(buf));
		sleep(3);
	}
	close(fd);
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
		perror("connect");
		return;
	}
	while (0 < (rd=read(fd, buf, sizeof(buf)-1))) {
                buf[rd]=0;
		printf("c: %s\n", buf);
	}
	close(fd);
}

int main(int argc, char **argv)
{
	if (argc==1) server();
	if (argv[1][0]=='s') server();
	if (argv[1][0]=='c') client(); 
	return 0;
}

