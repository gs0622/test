/*XOR hash 64bit to 16bit*/
#include <stdio.h>
#include <stdlib.h>
short hash(long long i)
{
    short hash = (short)(i & 0xFFFF);
    hash ^= (short)((i >> 16) & 0xFFFF);
    hash ^= (short)((i >> 32) & 0xFFFF);
    hash ^= (short)((i >> 48) & 0xFFFF);
    return hash;
}
int main(int argc, char *argv[])
{
    int i, n=argc-1;
    for (i=0;i<n;i++) printf("h(%s)=%d\n", argv[i+1], hash(atoll(argv[i+1])));
    return 0;
}

