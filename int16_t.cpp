#include <stdio.h>
//#include <stdint.h> //uncomment microsoft >vs2010: 
#ifndef int16_t
	#define int16_t __int16
	#define uint16_t unsigned __int16
	#define int32_t __int32
	#define uint32_t unsigned __int32
#endif


long main()
{
	int16_t a;
	uint16_t b;
	int32_t c;

	a = b = c = (32 * 1024 - 1);
	printf("\n\n===FIN==="); getchar(); getchar();
	return 1;
}