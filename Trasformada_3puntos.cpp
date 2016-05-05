/*  transformada3P convierte 
 una coordenada bidimensional: xy1 referida a las coordenadas "coor1" 
 a otra coordenada           : xy2 referida a las coordenadas "coor2" 
 La función devuelve 0 si hay error de división por 0  
 La velocidad (modo release) es 103 millones de trasformadas/segundo con micro de 3.2Ghz empleando 1 nucleo
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*  transformada3P convierte 
 una coordenada bidimensional: xy1 referida a las coordenadas "coor1" 
 a otra coordenada           : xy2 referida a las coordenadas "coor2" 
 La función devuelve 0 si hay error de división por 0  */
int transformada3P(__int16 coor1[6],__int16 coor2[6],__int16 xy1[2],__int16 xy2[2]);
/*  transformada3P convierte 
 una coordenada bidimensional: xy1 referida a las coordenadas "coor1" 
 a otra coordenada           : xy2 referida a las coordenadas "coor2" 
 La función devuelve 0 si hay error de división por 0  */
int transformada3P(double coor1[6],double coor2[6],double xy1[2],double xy2[2]);


long main()
{
	double coor1[6]={-50,100,50,100,0,-50};
	double coor2[6]={-25,50 ,25,50 ,0,-25};
	double xy1[2],xy2[2];

	long i;
	for (i=0;i<3;i++)
	{	//compruebo que las tres coordenadas coor1 van a las otras tres coordenadas coor2
		transformada3P(coor1,coor2,coor1+i*2,xy2);printf("\nx1=%lg y1=%lg x2=%lg y2=%lg",coor1[i*2],coor1[i*2+1],xy2[0],xy2[1]);
	}

	clock_t ini,fin;ini=clock();
	double sumerror=0.0;
	long NUM=10000000;
	xy1[0]=1.0* (rand() % 200);
	xy1[1]=1.0* (rand() % 200);
	for (i=0;i<NUM;i++)
	{
		xy1[0]=1.0* (rand() % 200);//comentar para test de velocidad
		xy1[1]=1.0* (rand() % 200);//comentar para test de velocidad
		transformada3P(coor1,coor2,xy1,xy2);
		double xy3[3];
		transformada3P(coor2,coor1,xy2,xy3);
		double x,error;
		x=xy1[0]-xy3[0];error= x*x;//comentar para test de velocidad
		x=xy1[1]-xy3[1];error+=x*x;
		sumerror+=error;
	}
	fin=clock();double seconds=1.0*(fin-ini)/CLOCKS_PER_SEC;
	sumerror=sqrt(sumerror/NUM);
	printf("\nError medio=%lg segundos=%lg",sumerror,seconds);
	printf("\nMegaoperaciones/segundo=%lg",1.0e-6*NUM/seconds*2); //se multiplica por dos pues se hace 2 veces

	printf("\n\n===FIN===");getchar();getchar();
	return 1;
}

//coor[6]=ojo izq (x,y), ojo derecho (x,y) y boca (x,y). Retorna 0 si fail
/*  transformada3P convierte 
 una coordenada bidimensional: xy1 referida a grupo de 3 puntos  "coor1" 
 a otra coordenada           : xy2 referida a otros    3 puntos  "coor2" 
 La función devuelve 0 si hay error de división por 0  */
int transformada3P(__int16 coor1[6],__int16 coor2[6],__int16 xy1[2],__int16 xy2[2])
{
	long x10=coor1[2]-coor1[0];
	long x20=coor1[4]-coor1[0];
	long x30=xy1[0]  -coor1[0]; 
	long y10=coor1[3]-coor1[1];
	long y20=coor1[5]-coor1[1];
	long y30=xy1[1]  -coor1[1]; 
	double det;det=x10*y20-y10*x20;
	if (det==0) return 0;//fail
	double k1;k1=1.0*(x30*y20-x20*y30)/det;
	double k2;k2=1.0*(x10*y30-y10*x30)/det;
	       //x0         x1       x0            x2       x0   
	xy2[0]=(__int16) (0.5+coor2[0]+k1*(coor2[2]-coor2[0])+k2*(coor2[4]-coor2[0]));
	xy2[1]=(__int16) (0.5+coor2[1]+k1*(coor2[3]-coor2[1])+k2*(coor2[5]-coor2[1]));
	return 1;//ok
}

//coor[6]=ojo izq (x,y), ojo derecho (x,y) y boca (x,y). Retorna 0 si fail
/*  transformada3P convierte 
 una coordenada bidimensional: xy1 referida a las coordenadas "coor1" 
 a otra coordenada           : xy2 referida a las coordenadas "coor2" 
 La función devuelve 0 si hay error de división por 0  */
int transformada3P(double coor1[6],double coor2[6],double xy1[2],double xy2[2])
{
	double x10=coor1[2]-coor1[0];
	double x20=coor1[4]-coor1[0];
	double x30=xy1[0]  -coor1[0]; 
	double y10=coor1[3]-coor1[1];
	double y20=coor1[5]-coor1[1];
	double y30=xy1[1]  -coor1[1]; 
	double det;det=x10*y20-y10*x20;
	if (det==0) return 0;//fail
	double k1;k1=1.0*(x30*y20-x20*y30)/det;
	double k2;k2=1.0*(x10*y30-y10*x30)/det;
	       //x0         x1       x0            x2       x0   
	xy2[0]=coor2[0]+k1*(coor2[2]-coor2[0])+k2*(coor2[4]-coor2[0]);
	xy2[1]=coor2[1]+k1*(coor2[3]-coor2[1])+k2*(coor2[5]-coor2[1]);
	return 1;//ok
}


