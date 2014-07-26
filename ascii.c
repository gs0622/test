#include <stdio.h>
int main(void)
{
    char str[128], *p;
    while (gets(str)) {
        for (p=str;*p!='\0';p++)
            printf("%d ", *p);
        printf("\n");
    }
    return 0;
}

