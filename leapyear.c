#include <stdio.h>

int leap(int yy)
{
    return !(yy % 4) && (yy % 100) || !(yy % 400);
}

int main(void)
{
    int yy;
    while (scanf("%d", &yy) != EOF) {
        printf("%d: %s\n", yy, leap(yy)? "leap": "common");
    }
    return 0;
}

