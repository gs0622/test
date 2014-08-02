#include <stdio.h>
int main(void)
{
    int i=1, j, k;
    printf("%d %d %d\n", i++, i++, i);
    i=1;
    printf("%d %d %d\n", ++i, i++, i);
    i=j=k=1;
    printf("%d %d %d\n", i++, j++, k);
}
