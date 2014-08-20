#include <stdio.h>
#include <time.h>

int main(void)
{
    unsigned short us;
    unsigned int ui;
    unsigned long ul;
    unsigned long long ull;
    double d;
    time_t t;
    /*check sizeof for various arch*/
    us=sizeof(us);
    ui=sizeof(ui);
    ul=sizeof(ul);
    ull=sizeof(ull);
    t=sizeof(t);
    printf("us=%d ui=%d ul=%d ull=%d t=%d d=%d\n", us, ui, ul, ull, t, sizeof(d));
    return 0;
}
