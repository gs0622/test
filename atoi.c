#include <stdio.h>
#include <stdlib.h> /*for atoi()*/

#define INT_MAX     (0x7fffffff)

static int myatoi(const char *s)
{
    int total = 0, ch, sign=1;
    if (NULL==s) return 0; /*no conversion*/
    if (s[0]=='-') sign=-1, s++;
    if (s[0]=='+') s++;
    while (*s != '\0') {
        ch = (int)*s++;
        if (ch >= '0' && ch <= '9') { /*isdigit*/
            if (total > INT_MAX/10) return 0; /*break or no convert is undefined*/
            if (sign == 1 && total == INT_MAX/10 && ((ch-'0') > INT_MAX%10)) return 0;
            if (sign == -1 && total == INT_MAX/10 && ((ch-'0') > INT_MAX%10 + 1)) return 0;
            total = (total * 10) + (ch - '0');
        } else break; /*if not break, it might concatenate numbers*/
    }
    return sign*total;
}

int main(void)
{
    char s[128];
    while (scanf("%s", s)!=EOF) {
        printf("atoi  : %d\n", atoi(s));
        printf("myatoi: %d\n", myatoi(s));
    }
    return 0;
}
