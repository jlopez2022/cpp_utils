#include <stdio.h>
#include <thread>
#include <Windows.h>
#include <time.h>
#include <queue> 
#define NUM_THREADS 8
#define SIZE 1000000L

struct s_mensaje
{
	int tarea,posicion; 
};
std::queue<s_mensaje> mensaje;

void funcion(int *mat, int size,int tarea)
{
	clock_t tiempo;
	tiempo = clock();printf("\ntarea %i ini:%lg", tarea, (double)(1.0*tiempo / CLOCKS_PER_SEC));
	long i, j; s_mensaje mensaje1; mensaje1.tarea = tarea;
	for (j = 0; j < 3200; j++)
	{
		if (j % 500 == 0)
		{
			mensaje1.posicion = j;
			mensaje.push(mensaje1);
		}
		for (i = 0; i < size; i++)
			mat[i] = i + 10L*j;
	}
	tiempo = clock(); printf("\ntarea %i fin:%lg", tarea, (double)(1.0*tiempo / CLOCKS_PER_SEC));
}

char TERMINATE_THREADS; //Flag para terminar tareas

void leemensajes(void)
{
	printf("\n ini leemensajes()");
	while (TERMINATE_THREADS)
	{
		if (!mensaje.empty())
		{
			printf("\n \t\t\t\t Status tarea:%i posicion:%i", mensaje.front().tarea, mensaje.front().posicion); mensaje.pop();
		}
		else Sleep(1);
	}
	printf("\n fin leemensajes()");
}

int main()
{
	TERMINATE_THREADS = 1;
	printf("\nNUMERO DE TAREAS=%li", NUM_THREADS);
	clock_t tiempo;
	tiempo = clock(); printf("\nINICIO:%lg", (double) (1.0*tiempo/CLOCKS_PER_SEC));
	int (*mat)[SIZE] = new int[NUM_THREADS][SIZE];
	long i;

	std::thread tarea[NUM_THREADS];
	std::thread tarea_leeestado;
	tarea_leeestado = std::thread(leemensajes);//Lanzo tarea de mirar mensajes
	
	for (i = 0; i < NUM_THREADS; i++)
		tarea[i]=std::thread(funcion, mat[i], SIZE,i);

	for (i = 0; i < NUM_THREADS; i++)
		if (tarea[i].joinable())
			tarea[i].join();

	TERMINATE_THREADS = 0;//Mando terminar lav tarea tarea_leeestado (y si hubiera alguna otra pues también)
	tiempo = clock(); printf("\nFIN:%lg", (double)(1.0*tiempo / CLOCKS_PER_SEC));
	if (tarea_leeestado.joinable())
		tarea_leeestado.join();
	delete[] mat;
	printf("\nEND");
	getchar(); getchar();
	return 1;
}