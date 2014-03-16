#include <stdio.h>

#define SWAP16(x)	((((x)>>8)|((x)<<8))&0xffff)
#define SWAP32(x)	((SWAP16((x)&0xffff)<<16)|(SWAP16((x)>>16)))
#define BSWAP32(x)	((((x)&0xff000000)>>24)|(((x)&0x00ff0000)>>8)|(((x)&0xff00)<<8)|(((x)&0xff)<<24))

int main(void)
{
	unsigned short x=0x1234;
	unsigned int y=0xbabeface;
	unsigned int z=0xdeadf00d;
	printf("swap16 0x%.4x->0x%.4x\n", x, SWAP16(x));
	printf("swap32 0x%.8x->0x%.8x\n", y, SWAP32(y));
	printf("swap32 0x%.8x->0x%.8x\n", z, BSWAP32(z));
	return 0;
}

