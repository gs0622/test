#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	//if (argc<3) exit(0);
	//printf("s1=%s\ns2=%s\ncmp=%d\n", argv[1], argv[2], strcmp(argv[1], argv[2]));
	printf("cmp=%d\n", strcmp("ab", "abc"));
	printf("cmp=%d\n", strcmp("abc", "abc"));
	printf("cmp=%d\n", strcmp("abc", "ab"));
	printf("cmp=%d\n", strcmp("acb", "abc"));
	return 0;
}

