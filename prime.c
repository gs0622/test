#include <stdio.h>
#include <math.h>

int isprime(int n)
{
    int maxdiv;
    int div = 5;
    if (n<2) return 0; /*false*/
    if ((n==2)||(n==3)) return 1; /*true*/
    if ((n%2==0)||(n%3==0)) return 0;
    maxdiv = (int)(sqrt((double)n))+1;
    div = 5;
    while (div<maxdiv) {
        if ((n%div==0)||(n%(div+2)==0)) return 0;
        div+=6;
    }
    return 1;
}
    
int main(int argc, char **argv)
{
    int i, j, n = (argc>1)? atoi(argv[1]):10;
    for (i=2,j=0;n;i++) {
        if (isprime(i)) {
            printf("%d%s", i, (++j%8)?", ":",\n");
            n--;
        }
    }
    return 0;
}
