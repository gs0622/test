#include <stdio.h>

void factorize(int n)
{
    int d=2;
    while (d<=n) { /*prime factorization*/
        if (n%d==0) n/=d, printf("%d ", d);
        else d+=(d==2)?1:2;
    }
}

int main(int argc, char **argv)
{
    int n;
    scanf("%d",&n);
    factorize(n);
    return 0;
}
