#include <string.h>

typedef char ch8[8];

void main()
{
ch8 *label8,c1[12];
unsigned int long_ch=0;
char a;                                          
label8=&c1[0];


strcpy(&label8[0][0],"0123");
long_ch=0;
while (label8[0][long_ch]&&long_ch<8) long_ch++;
strcpy(&label8[0][0],"01234567890");
long_ch=0;
while (label8[0][long_ch]&&long_ch<8) long_ch++;
strcpy(&label8[0][0],"01234567");
long_ch=0;
while (label8[0][long_ch]&&long_ch<8) long_ch++;
label8[0][0]='\0';
long_ch=0;
while (label8[0][long_ch]&&long_ch<8) long_ch++;

}
