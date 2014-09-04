/*mbr read example*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct {
    char code[440];
    char ignore[6];
    char partation[4][16];
    char signature[2];
} mbr_t;

int main(int argc, char *argv[])
{
    int fd, nread;
    mbr_t mbr;
    if (1 == argc) return 0;
    printf("fi=%s\n", argv[1]);
    fd = open(argv[1], O_RDONLY);
    printf("fd=%d\n", fd);
    nread = read(fd, &mbr, sizeof(mbr));
    printf("nread=%d\n", nread);
    if (fd > 0) close(fd);
    return 0;
}

