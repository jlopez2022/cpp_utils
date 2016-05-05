#include <stdio.h>

void main()
{
char c;
int i=0x3333,j=0111,k;
k=0xFF11&i;
j=k>>8;
printf("%x %x\n",k,j);
scanf("%c%c",&c,&c);
}