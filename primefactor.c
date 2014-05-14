#include <stdio.h>
    
int main(int argc, char **argv)
{
    int n, d=2;
    scanf("%d",&n);
    while (d<=n) { /*prime factorization*/
        if (n%d==0) n/=d, printf("%d ", d);
        else d+=(d==2)?1:2;
    }
    return 0;
}
