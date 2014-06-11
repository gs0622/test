#include <stdio.h>

#define INT_MAXD    (19+2)  /*max for 64-bit, 9223372036854775808L*/

char *itoa(int i)
{
    static char s[INT_MAXD];
    char *p = &s[INT_MAXD-1]; /*point to last '\0'*/
    char sign = (i>=0)? 1: 0;
    do {
        *--p = sign? '0'+(i%10):'0'-(i%10);
        i/=10;
    } while (i!=0);
    if (sign==0) *--p = '-';
    return p;
}

int main(void)
{
    int i;
    while (scanf("%i", &i)!=EOF) {
        printf("itoa  : %s\n", itoa(i));
    }
    return 0;
}
