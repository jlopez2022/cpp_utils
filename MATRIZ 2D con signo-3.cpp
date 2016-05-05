#include <stdio.h>
#include <string.h>
//incluye extremos!!


void main()
{
	const int DELTA=8;
	char memoria[(2*DELTA+1)*(2*DELTA+1)],(*memo2)[2*DELTA+1];
	memo2=(char (*)[2*DELTA+1]) &memoria[DELTA*(2*DELTA+1)+DELTA];

	if (&memo2[-DELTA][-DELTA]!=&memoria[0])
		printf("Error1\n");
	if (&memo2[DELTA][DELTA]!=&memoria[(2*DELTA+1)*(2*DELTA+1)-1]) 
		printf("Error2\n");

	//otra forma:
	int array_m[2*DELTA+1][2*DELTA+1];
	int (*array2)[2*DELTA+1]=(int(*)[2*DELTA+1]) &array_m[DELTA][DELTA];
	memset(array_m,0,(2*DELTA+1)*(2*DELTA+1)*sizeof(int));
	if (&array2[-DELTA][-DELTA]!=&array_m[0][0])
		printf("Error3\n");
	if (&array2[DELTA][DELTA]!=&array_m[2*DELTA+1-1][2*DELTA+1-1]) 
		printf("Error4\n");


	printf("\n\n===FIN===\n");
	char c; scanf("%c%c",&c,&c);
}