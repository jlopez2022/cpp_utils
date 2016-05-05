#include <stdio.h>

typedef unsigned char byte;

//Pone a 1 el bit n de a
void setbitn(byte *a,long n)
{
	*a |=(1<<n);
}

//Pone a 0 el bit n de a
void resetbitn(byte *a,long n)
{
	*a &=(~(1<<n));
}


void main()
{

	byte a;long i;
	for (i=0;i<16;i++) 
	{
		a=i;setbitn(&a,0);printf("\n%X %X ",i,a);a=i;resetbitn(&a,0);printf("%X",a);
	}
	printf("\n================");
	for (i=0;i<16;i++) 
	{
		a=i;setbitn(&a,1);printf("\n%X %X ",i,a);a=i;resetbitn(&a,1);printf("%X",a);
	}
	printf("\n================");
	for (i=0;i<16;i++) 
	{
		a=i;setbitn(&a,2);printf("\n%X %X ",i,a);a=i;resetbitn(&a,2);printf("%X",a);
	}
	printf("\n================");
	for (i=0;i<16;i++) 
	{
		a=i;setbitn(&a,3);printf("\n%X %X ",i,a);a=i;resetbitn(&a,3);printf("%X",a);
	}
	printf("\n================");
	getchar();getchar();
}