#include <stdio.h>
typedef union uPack
{
unsigned char Array[8]; //full packet
struct {
unsigned char Code; //code or command
unsigned char ID[6]; //identification
unsigned char CRC; //check
};
}uPack;

int main()
{
uPack PackList[2]; // 2 packets or more
unsigned char i;
//...
// receiving the firs packet
for (i=0; i<8; i++)
{
PackList[0].Array[i]=i;
}

//using the packet - this is OK
printf(" Code: %u ", PackList[0].Array[0]);
printf(" Id: %u%u%u%u%u%u ", PackList[0].Array[6], PackList[0].Array[5], PackList[0].Array[4], PackList[0].Array[3], PackList[0].Array[2], PackList[0].Array[1]);
printf(" CRC: %u \n", PackList[0].Array[7]);
//...
//using the packet - this is NOT OK
printf(" Code: %u ", PackList[0].Code); //OK, same address then PackList[0].Array[0];
printf(" ID: %u ", PackList[0].ID[0]); //NOT OK, same address then PackList[0].Array[0];
printf(" CRC: %u \n", PackList[0].CRC); //NOT OK, same address then PackList[0].Array[0];
//...
return 0;
}

