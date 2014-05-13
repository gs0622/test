#include <stdio.h>

unsigned long long fac(unsigned long long i)
{
    return (i>0)? i*fac(i-1) : 1;
}
int main(void)
{
    unsigned long long i;
    for (i=1;i<14;i++) printf("%llu\n", fac(i));
    return 0;
}
