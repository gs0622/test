#include <stdio.h>
#include <netdb.h>

int main(int argc, char **argv)
{
	const char *def="127.0.0.1";
	struct hostent *h;
	h=gethostbyname((argc==1)?def:argv[1]);
	printf("def=%s\n", def);
	printf("h@%p\n", h);
	printf("n=%s\n", h->h_name);
	printf("t=%d\n", h->h_addrtype);
	printf("l=%d\n", h->h_length);
	printf("a=0x%.8x\n", *(unsigned int *)(h->h_addr_list[0]));
        printf("ip=%s\n", (char *)inet_ntoa(*((struct in_addr *)h->h_addr_list[0])));
	return 0;
}
