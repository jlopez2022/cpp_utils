/*
   Settings:
1. Meter en Project->settings->linker: pthreadVC2.lib wsock32.lib 
2. Ademas deben estar los pthread.h y sched.h en el directorio y pthreadVC2.dll y .lib
3. Project->setting->C/C++,code generation, use runtime libray: multithreating dll
4. EN PROJECT->SETTING->LINK->OUTPUT en RESERVE poner: 0x6400000  (=100Mb)

5. Bajar pthtread: .h,dll y .lib de: ftp://sourceware.org/pub/pthreads-win32/dll-latest/
8. Cambiar los include <xxx.h> por "xxx.h" 
9. POR ultimo: si no linca shed.h hay que meterlo en el arbol del proyecto 
   (en ventanita de la derecha) colgando de Header files
*/

#include <windows.h> //DWORD, Sleep
#include <conio.h>  //_kbhit
#include <stdio.h>
#include <string.h> //strlen,memcpy
#include <stdlib.h> //rand()
#include "pthread.h"//libreria de hilos 
#define D_TIMER 500.0 //Espera maxima en milisegundos
#define D_BUFFER_SIZE 32 //Muy importante para no copiar de mas
#define D_TAREAS 100


struct s_control
{
	char line_in[D_BUFFER_SIZE];
	char line_out[D_BUFFER_SIZE];
	__int16 delay;
	volatile __int16 estado;//0=empty,1=full,2=filling
}*control;


static void* F_pull(void* vv)//=pull_one_curl() 
{
	s_control* cc = (s_control* ) vv;
	long lon=strlen(cc->line_in);
	if (lon>(D_BUFFER_SIZE-2))
		lon=D_BUFFER_SIZE-2;//Importantisimo para memcpy no copie infinitos datos
	memcpy(cc->line_out,cc->line_in,lon);
	cc->line_out[lon]=(char) '/0';//Limito el string
	Sleep((DWORD) cc->delay);
	cc->estado=1;				//ESTADO LLENO
	return NULL;
}


void main()
{
	//Llenado de los line1
	control=new s_control[D_TAREAS];
	long i,i2;
	for (i2=0;i2<D_TAREAS;i2++)
	{ 
		control[i2].delay = (__int16) (D_TIMER*rand()/RAND_MAX);
		control[i2].estado=1;				//INICIALMENTE ESTADO LLENO PARA QUE LO INICIEN
	}

	//Llamada a las tareas
	pthread_t *tid=new pthread_t[D_TAREAS];
	int error;
	do
	{
		Sleep((DWORD) 100);
		for (i2=0;i2<D_TAREAS;i2++)
		{
			long estado1=control[i2].estado;		//Acceso a ESTADO
			if (estado1==0)
			{
				printf("\nTAREA#%li:iniciada",i2);
				control[i2].estado=2;				//ESTADO LLENANDO
				error = pthread_create(&tid[i2],NULL,F_pull,(void *) &control[i2]);
				printf(" Error=%i",error);
			}
			else if (estado1==1)
			{
				strcpy(control[i2].line_out,"xxxxxxxxxxxxxxxxxxxxxxxxxx");
				for (i=0;i<D_BUFFER_SIZE-1;i++)
					control[i2].line_in[i]=(char) ('a'+i2);
				control[i2].line_in[i]='\0';
				printf("\nTAREA#%li:vacio",i2);
				control[i2].estado=0;				//ESTADO VACIO
			}
			else 
			{
				//printf("\nTAREA#%li:llenando",i2);
			}
		}
	}while(!_kbhit());
	//Acabando
	printf("\nEspera inicial de %li ms",(long) D_TIMER);
	Sleep((DWORD) (D_TIMER));
	long bloq;
	printf("\nCerrando tareas");
	for(bloq=0; bloq< D_TAREAS; bloq++) 
	{
		int error;
		error = pthread_join(tid[bloq], NULL);
		printf("\nThread %d terminated Error=%i", bloq,error);
	}
	i2=i2;
	delete control;
	i2=i2;
	printf("\n\n === FIN ===");getchar();getchar();
}