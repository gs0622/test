#include <stdio.h>

int foo(int &x)
{
	x++;
}

int main(void)
{
	int x=5;
	foo(x);
	printf("x=%d\n",x);
	return 0;
}

