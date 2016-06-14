/*¡¡CAUTION!!: project->setting->C/C++,code generation, use runtime libray: multithreating dll*/ 
#include <stdio.h>
#include <process.h>    /* _beginthread, _endthread */
#include <stdlib.h>
#include <windows.h>


void funcion(void *ppp);//tareas
struct funcion_s		//estructura de datos da las tareas
{
	char status;//0,1 0=iniciado,1=finalizado
	//variables de entrada en la tarea (cambiarlas)
	long dir;
	long delay;
	//variables de salida (cambiarlas)
	double x;
	char c;
};



int main()
{
	//ejemplo de uso de las tareas:
	funcion_s s1,s2,s3;
	s1.dir=100;s2.dir=101;s3.dir=102;
	s1.delay=2000;s2.delay=4000;s3.delay=3000;
	 _beginthread( funcion, 0, (void *) (&s1)  );
	 _beginthread( funcion, 0, (void *) (&s2)  );
	 _beginthread( funcion, 0, (void *) (&s3)  );

	 do
	 {
	 }while((s1.status+s2.status+s3.status)<3);

	 printf("\nFIN");getchar();getchar();

	return 1;
}



void funcion(void *ppp)
{
	funcion_s *s;
	s=(funcion_s *) ppp;

	//inicio de la funcion, cambiar todo el codigo de abajo
	s->x=1.0*rand()/RAND_MAX;
	s->c=(char) (s->x*256);
	s->status=0;//inicio
	printf("\ninicio tarea:%li",s->dir);
	DWORD xx=(DWORD) s->delay;
	Sleep(xx);
	s->status=1;//fin
	printf("\nfinal tarea:%li",s->dir);
}
