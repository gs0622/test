#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
    char *s;
    if (argc<3) return 0;
    if (s = strstr(argv[1], argv[2])) /*argv[1]=string, argv[2]=pattern*/
        printf("pattern \"%s\" is found in string \"%s\"\n", argv[2], argv[1]);
    else 
        printf("pattern \"%s\" is not found in string \"%s\"\n", argv[2], argv[1]);
}
