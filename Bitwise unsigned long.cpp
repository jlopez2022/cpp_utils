#include <stdio.h>

typedef unsigned long ulong;

int main()
{
	ulong i;i=0xC128F126LU;

	printf("\ni<<0=%08X",i);
	printf("\ni<<1=%08X",i<<1);
	printf("\ni<<2=%08X",i<<2);

	i=0xC128F126LU;
	printf("\ni>>0=%08X",i);
	printf("\ni>>1=%08X",i>>1);
	printf("\ni>>2=%08X",i>>2);

	i=0xFF000000LU;
	printf("\ni<<0=%08X",i);
	printf("\ni<<1=%08X",i<<1);
	printf("\ni<<2=%08X",i<<2);

	i=0x100000FFLU;
	printf("\ni>>0=%08X",i);
	printf("\ni>>1=%08X",i>>1);
	printf("\ni>>2=%08X",i>>2);

	getchar();getchar();
	return 0;
}