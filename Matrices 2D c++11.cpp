#include <stdio.h>



int main()
{
	long imax = 10;
	auto matriz = new double[imax][10];

	long i, j;
	for (i = 0; i < imax; i++)
		for (j = 0; j < imax; j++)
			matriz[i][j] = i* 1000.0 + j;

	for (i = 0; i < imax; i++)
	{
		for (j = 0; j < imax; j++)
			printf("%7lg ", matriz[i][j]);
		printf("\n");
	}

	delete[] matriz;
	getchar(); getchar();
	return 1;
}
