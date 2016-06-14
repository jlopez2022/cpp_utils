/*¡¡CAUTION!!: project->setting->C/C++,code generation, use runtime libray: multithreating dll*/ 
//VER: Curl y Pthreads.cpp 
//En esta version, cuatro tareas  quedan atascadas y se para desde la tarea principal

#include <stdio.h>
#include <process.h>    /* _beginthread, _endthread */
#include <stdlib.h>
#include <windows.h>    //Sleep
#include <time.h>
#include <conio.h>     //_kbhit
#define TIMEOUT 5 //numero maximo de segundos
#define TAREAS 8


void funcion(void *ppp);//tareas
struct funcion_s		//estructura de datos da las tareas
{
	long dir;	//Nombre de la tarea
	char status;//0,1 0=iniciado,1=finalizado
	unsigned long tarea;//Handler de la tarea
	long tiempo;//para mirar si ocurre timeout
	char finalizar;//0:seguir, 1, finalizar
	//variables de entrada en la tarea (cambiarlas)
	long delay;
	//variables de salida (cambiarlas)
	double x;
	char c;
};

long ftiempo()
{
	time_t tt;time(&tt);
	return (long) tt;
}



int main()
{
	//ejemplo de uso de las tareas:
	funcion_s s[TAREAS];
	long i;
	for (i=0;i<TAREAS;i++)//lanzo las tareas
	{
		s[i].dir=i;
		//Configuro la tarea a realizar:
		s[i].delay=2+i;
		s[i].tarea=_beginthread( funcion, 0, (void *) (&s[i])  );
		s[i].finalizar=0;
	}

	long timeini;
	timeini=ftiempo();
	BOOL bb=0;DWORD ww=0;long final=0;long acabadas=0;
	do
	{
		long tiempo1;
		tiempo1=ftiempo();
		acabadas=0;
		for (i=0;i<TAREAS;i++)//Miro si alguna tarea atascada
		{
			if ( ( (tiempo1-s[i].tiempo)>TIMEOUT ) && s[i].status==0)//tarea atascada
			{
				s[i].status=1;bb=TerminateThread((HANDLE) s[i].tarea,ww);char cc[10]="OK";if (!bb) strcpy(cc,"FAIL");
				printf("\nAcabada tarea %li a la fuerza, resultado=%s",i,cc);
			}
			acabadas+=s[i].status;
		}
	}while(!_kbhit() );

	//Acabo todas las tareas que aun no estaban acabadas
	for (i=0;i<TAREAS;i++)
	{
		s[i].finalizar=1;
	}
	while(acabadas<TAREAS)
	{
		acabadas=0;
		for (i=0;i<TAREAS;i++)
			acabadas+=s[i].status;
	}

	printf("\nFIN");getchar();getchar();

	return 1;
}



void funcion(void *ppp)
{
	funcion_s *s;
	s=(funcion_s *) ppp;
	s->status=0;//inicio

	//inicio de la funcion, cambiar todo el codigo de abajo
	printf("\ninicio tarea:%li",s->dir);
	s->x=1.0*rand()/RAND_MAX;
	s->c=(char) (s->x*256);
	while(!s->finalizar)
	{
		Sleep((DWORD) (1000*s->delay));
		s->tiempo=ftiempo();
	}
	printf("\nfinal tarea:%li",s->dir);

	//indicacion de final:
	s->status=1;//fin
}
