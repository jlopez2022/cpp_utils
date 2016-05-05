#include <stdio.h>      // printf 


int main ()
{
	long k;
	for (k=0;k<20;k++)
		if (k&1)
			printf("k=%i\n",k);
	printf("===FIN===\n");getchar();getchar();
	return 0;
}