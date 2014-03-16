#include <stdlib.h>

int main(int argc, char **argv)
{
	int i, s, n = (argc>1)? atoi(argv[1]): 10/*default*/;
	for (i=0; i<n; i++) {
		s = rand()%100;
		printf("%2d%c", s, (i==(n-1))? '\n': ' ');
	}
}

