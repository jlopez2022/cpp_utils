//Prueba exclusive nor
#include <stdio.h>



void main()
{
	unsigned long a,b,c;
	a=0xABE567L;
	b=0xABCA76L;
	c=a^b;//c= a "exclusive nor" b
	printf("\na=%10X",a);
	printf("\nb=%10X",b);
	printf("\nc=%10X",c);
	char ch;
	scanf("%c%c",&ch,&ch);
}