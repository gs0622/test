#include <stdio.h>

int main(void)
{
	unsigned short us;
	unsigned int ui;
	unsigned long ul;
	unsigned long long ull;
	/*check sizeof for various arch*/
	us=sizeof(us);
	ui=sizeof(ui);
	ul=sizeof(ul);
	ull=sizeof(ull);
	printf("us=%d ui=%d ul=%d ull=%d\n", us, ui, ul, ull);
	return 0;
}
