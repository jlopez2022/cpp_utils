#include <stdio.h>

void imprime(double matriz[][10],long imax)
{
	for (long i = 0; i < imax; i++)
	{
		for (long j = 0; j < 10; j++)
			printf("%7lg ", matriz[i][j]);
		printf("\n");
	}
}


int main()
{
	long imax = 20;
	auto matriz = new double[imax][10];

	long i, j;
	for (i = 0; i < imax; i++)
		for (j = 0; j < 10; j++)
			matriz[i][j] = i* 1000.0 + j;

	for (i = 0; i < imax; i++)
	{
		for (j = 0; j < 10; j++)
			printf("%7lg ", matriz[i][j]);
		printf("\n");
	}
	printf("\n");
	imprime(matriz, imax);

	delete[] matriz;
	getchar(); getchar();
	return 1;
}
