#include <stdlib.h>
#include <stdio.h>

void main()
{
double x;
char c[80];

x=1.23456e-5;
_gcvt(x,15,&c[0]);
printf("%lg=%s\n",x,c);
x=1.23456e5;
_gcvt(x,15,&c[0]);
printf("%lg=%s\n",x,c);
scanf("%c%c",c,c);
}