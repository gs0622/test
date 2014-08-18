#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    unsigned int n;
    if (1 < argc) { 
        n = (unsigned int)atoi(argv[1]);
        printf("%s\n", (n & (n-1))==0? "yes": "no");
    } else {
        for (n = 1; n < 128; n++)
            printf("%d: %s\n", n, (n & (n-1))==0? "yes": "no");
    }
    return 0;
}
