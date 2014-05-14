#include <stdio.h>
#include <math.h>
    
int main(int argc, char **argv)
{
    int i, n;
    scanf("%d",&n);
    //while (n%2==0) printf("%d ", 2), n/=2;
    for (i=2;i<n;i++) {
        if (n%i==0) n/=i, printf("%d ", i--);
    }
    printf("%d\n", i);
    return 0;
}
