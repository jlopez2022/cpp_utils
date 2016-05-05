//Prueba bitset
#include <stdio.h>

typedef unsigned long ulong;

ulong bitmap1[32],bitmap0[32];

void set1(ulong &a,int bit)
{
	if (bit>=32)
	{
		printf("\nError:bit>=32");
		char ch;scanf("%c%c",&ch,&ch);
		return;
	}
	a=a | bitmap1[bit];
	return;
}

void set0(ulong &a,int bit)
{
	if (bit>=32)
	{
		printf("\nError:bit>=32");
		char ch;scanf("%c%c",&ch,&ch);
		return;
	}
	a=a & bitmap0[bit];
	return;
}

void main()
{
	ulong a,b,c,d;
	a=0xABE56733L;
	b=0xABCA7644L;
	c=0xFFFFFFFFL;
	d=0x00000000L;
	//1. Inicializo bitmaps
	int i;
	ulong x=1;
	for (i=0;i<32;i++)
	{
		bitmap1[i]=x;
		bitmap0[i]=~x;
		x=x<<1;
	}

	ulong y;
	for (i=0;i<32;i++)
	{
		y=c;set0(y,i);printf("\n%2i %X",i,y);
		y=d;set1(y,i);printf(" %8X",y);
	}

	set1(a,3);
	set1(a,7);
	printf("\na=%10X",a);
	set1(a,32);
}