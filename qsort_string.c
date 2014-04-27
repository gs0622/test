#include <stdio.h>
#include <stdlib.h>

static int cmp(const void *p, const void *q)
{
	return strcmp((char *)p, (char *)q);
}

int main(int argc, char **argv)
{
    char p[5][20] = {"cc", "ca", "ce", "cb", "cd"};
	qsort(p, 5, 20, cmp);
	return 0;
}
