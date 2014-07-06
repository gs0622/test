/*reference: sdbm, http://www.cse.yorku.ca/~oz/hash.html*/
#include <stdio.h>
static unsigned long hash(char *str)
{
    unsigned long hash = 0;
    int c;
    while ('\0'!=(c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;
    return hash;
}
int main(int argc, char *argv[])
{
    int i, n=argc-1;
    for (i=0;i<n;i++) printf("h(%s)=%ld\n", argv[i+1], hash(argv[i+1]));
    return 0;
}

