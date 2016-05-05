#include <stdio.h>
#include <thread>
#include <Windows.h>
#include <time.h>
#define NUM_THREADS 8
#define SIZE 1000000L

void funcion(int *mat, int size,int tarea)
{
	clock_t tiempo;
	tiempo = clock();printf("\ntarea %i ini:%lg", tarea, (double)(1.0*tiempo / CLOCKS_PER_SEC));
	long i,j;
	for (j = 0; j < 1000; j++)
		for (i = 0; i < size; i++)
			mat[i] = i+10L*j;
	tiempo = clock(); printf("\ntarea %i fin:%lg", tarea, (double)(1.0*tiempo / CLOCKS_PER_SEC));
}

int main()
{
	printf("\nNUMERO DE TAREAS=%li", NUM_THREADS);
	clock_t tiempo;
	tiempo = clock(); printf("\nINICIO:%lg", (double) (1.0*tiempo/CLOCKS_PER_SEC));
	int (*mat)[SIZE] = new int[NUM_THREADS][SIZE];
	long i;

	/*	std::thread t1(funcion, mat[0], SIZE,0);
	if (t1.joinable())
		t1.join();*/

	std::thread t[NUM_THREADS];
	
	for (i = 0; i < NUM_THREADS; i++)
		t[i]=std::thread(funcion, mat[i], SIZE,i);

	for (i = 0; i < NUM_THREADS; i++)
		t[i].join();

	tiempo = clock(); printf("\nFIN:%lg", (double)(1.0*tiempo / CLOCKS_PER_SEC));
	printf("\nEND");
	delete[] mat;
	getchar(); getchar();
	return 1;
}