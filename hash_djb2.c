/*reference: djb2, http://www.cse.yorku.ca/~oz/hash.html*/
#include <stdio.h>
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ('\0'!=(c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int main(int argc, char *argv[])
{
    int i, n=argc-1;
    for (i=0;i<n;i++) printf("h(%s)=%ld\n", argv[i+1], hash(argv[i+1]));
    return 0;
}

