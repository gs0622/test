#include <stdio.h>
#include <string.h>
unsigned int hash(const void *buf, size_t buflength) {
    const unsigned char *buffer = (const unsigned char*)buf;
    unsigned int s1 = 1, s2 = 0;
    size_t n;

    for (n = 0; n < buflength; n++) {
        s1 = (s1 + buffer[n]) % 65521;
        s2 = (s2 + s1) % 65521;
    }     
    return (s2 << 16) | s1;
}
int main(int argc, char *argv[])
{
    int i, n=argc-1;
    for (i=0;i<n;i++) printf("h(%s)=%u\n", argv[i+1], hash(argv[i+1], strlen(argv[i+1])));
    return 0;
}

