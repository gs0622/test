#include <stdio.h>
#include <stdlib.h>

char dtob(double n)
{
    int i, j;
    unsigned long long m = *(unsigned long long *)&n;
    static char buf[128];
    for (i = sizeof(double)-1, j = 0; i >= 0; i--)
        buf[j++] = (m & (1 << i))? '1': '0';
    buf[j] = 0;
    return buf;
}

int main(int argc, char *argv[])
{
    char str[128];
    double n;
    while (gets(str)) {
        n = atof(str);
        printf("%f\n", n);
        printf("%s\n", dtob(n));
        printf("%.8llx\n", *(unsigned long long *)&n);
    }
    return 0;
}

