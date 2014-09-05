/*mbr read example*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct {
    unsigned char code[440];
    unsigned char dsig[6];
    unsigned char part[4][16];
    unsigned char bsig[2];
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
    //printf("nread=%d\n", nread);
    printf("disk_sig=%1x%1x%1x%1x%1x%1x\n",
        mbr.dsig[0], mbr.dsig[1], mbr.dsig[2],
        mbr.dsig[3], mbr.dsig[4], mbr.dsig[5]);
    printf("boot_sig=%1x%1x\n", mbr.bsig[0], mbr.bsig[1]);
    if (fd > 0) close(fd);
    return 0;
}

