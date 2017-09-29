/*  transformada3P convierte 
 una coordenada bidimensional: xy1 referida a las coordenadas "coor1" 
 a otra coordenada           : xy2 referida a las coordenadas "coor2" 
 La función trasformada3p_hallacoef() halla el vector de trasformada a[6], devuelve 0 si hay error de división por 0  
 La función transformada3P trasforma el vactor bidimensional xy1[2]={x1,y1} en otro xy2[2]={x2,y2} empleando el vector de trasformada a[6] 

 Las coordenadas coorn[6]={(x0,y0),(x1,y1),(x2,y2)} donde x0,y0=origen de coordenadas
 */


#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

//Halla el vector de trasformada a[6] que trasforma un sistema de coordenadas coor1 en otro coor2
int trasformada3p_hallacoef(__int16 coor1[6],__int16 coor2[6],double a[6]); 
/*  transformada3P usa el vector de trasformada a[6] para trasformar. ES EL MAS RAPIDO, hace casi una trasformada por ciclo de reloj (2.5 giga trasformadas/seg empleando 1 nucleo de 3.2Ghz) 
    la coordenada bidimensional: xy1 referida a las coordenadas "coor1" 
   a otra coordenada           : xy2 referida a las coordenadas "coor2" */
void transformada3P(double a[6],__int16 xy1[2],__int16 xy2[2]);

/*  transformada3P convierte 
 una coordenada bidimensional: xy1 referida a las coordenadas "coor1" 
 a otra coordenada           : xy2 referida a las coordenadas "coor2" 
 La función devuelve 0 si hay error de división por 0  */
int transformada3P(__int16 coor1[6],__int16 coor2[6],__int16 xy1[2],__int16 xy2[2]);
/*  transformada3P convierte 
 una coordenada bidimensional: xy1 referida a las coordenadas "coor1" 
 a otra coordenada           : xy2 referida a las coordenadas "coor2" 
 La función devuelve 0 si hay error de división por 0  
 La velocidad (modo release) es 103 millones de trasformadas/segundo con micro de 3.2Ghz empleando 1 nucleo*/
int transformada3P(double coor1[6],double coor2[6],double xy1[2],double xy2[2]);

//version float:
int trasformada3p_hallacoef(__int16 coor1[6],__int16 coor2[6],float a[6]); 
void transformada3P(float a[6],__int16 xy1[2],__int16 xy2[2]);

long main()
{
	__int16 coor1[6]={-50,100,50,100,0,-50};
	__int16 coor2[6]={-25,50 ,30,50 ,5,-25};
	__int16 xy1[2],xy2[2];
	//inicializo:
	__int16 xy11[100][2],*p1;
	long i;
	for (i=0;i<100;i++)
	{
		xy11[i][0]=(rand() % 200);
		xy11[i][1]=(rand() % 200);
	}

	{
		double tras1[6];//vector de la trasformada
		trasformada3p_hallacoef(coor1,coor2,tras1);

		double tras2[6];//vector de la trasformada inversa
		trasformada3p_hallacoef(coor2,coor1,tras2);

		for (i=0;i<3;i++)
		{	//compruebo que las tres coordenadas coor1 van a las otras tres coordenadas coor2
			//transformada3P(coor1,coor2,coor1+i*2,xy2);printf("\nx1=%lg y1=%lg x2=%lg y2=%lg",coor1[i*2],coor1[i*2+1],xy2[0],xy2[1]);
			xy1[0]=coor1[i*2];xy1[1]=coor1[i*2+1];
			transformada3P(tras1,xy1,xy2);printf("\nx1=%3i y1=%3i x2=%3i y2=%3i",coor1[i*2],coor1[i*2+1],xy2[0],xy2[1]);
		}

		for (i=0;i<3;i++)
		{	//compruebo que las tres coordenadas coor1 van a las otras tres coordenadas coor2
			transformada3P(coor1,coor2,coor1+i*2,xy2);printf("\nx1=%3i y1=%3i x2=%3i y2=%3i",coor1[i*2],coor1[i*2+1],xy2[0],xy2[1]);
		}


		cout<<"\n\n=== Calculus using double ==="<<endl;
		clock_t ini,fin;ini=clock();
		double sumerror1=0.0;
		long NUM=50000000;
		//Calculo el tiempo de calcular rands:
		for (i=0;i<NUM;i++)
		{
			p1=&xy11[i%100][0];
			__int16 xy3[2];
			transformada3P(tras1,p1,xy2);//directa a coor2
			transformada3P(tras2,xy2,xy3);//inversa a coor1 de nuevo

			double x,error;
			x=xy3[0]-p1[0];error= x*x;//comentar para test de velocidad
			x=xy3[1]-p1[1];error+=x*x;//comentar para test de velocidad
			sumerror1+=error;		   //Para test de velocidad sustituir por sumaerror1+=xy3[0] si no evitará el loop entero
		}
		fin=clock();double seconds=1.0*(fin-ini)/CLOCKS_PER_SEC;
		sumerror1=sqrt(sumerror1/NUM);
		printf("Error medio=%lg tiempo=%lg s\n",sumerror1,seconds);
		printf("Megaoperaciones/segundo=%lg\n",1.0e-6*NUM/seconds*2); //se multiplica por dos pues se hace 2 veces
	}

	{	//floats!
		float tras1[6];//vector de la trasformada
		trasformada3p_hallacoef(coor1,coor2,tras1);

		float tras2[6];//vector de la trasformada inversa
		trasformada3p_hallacoef(coor2,coor1,tras2);

		cout<<"\n\n=== Calculus using float  ==="<<endl;
		clock_t ini,fin;ini=clock();
		double sumerror1=0.0;
		long NUM=50000000;
		//Calculo el tiempo de calcular rands:
		for (i=0;i<NUM;i++)
		{
			p1=&xy11[i%100][0];
			__int16 xy3[2];
			transformada3P(tras1,p1,xy2);//directa a coor2
			transformada3P(tras2,xy2,xy3);//inversa a coor1 de nuevo

			double x,error;
			x=xy3[0]-p1[0];error= x*x;//comentar para test de velocidad
			x=xy3[1]-p1[1];error+=x*x;//comentar para test de velocidad 
			sumerror1+= error;		   //Para test de velocidad sustituir por sumaerror1+=xy3[0] si no evitará el loop entero 
		}
		fin=clock();double seconds=1.0*(fin-ini)/CLOCKS_PER_SEC;
		sumerror1=sqrt(sumerror1/NUM);
		printf("Error medio=%lg tiempo=%lg s\n",sumerror1,seconds);
		printf("Megaoperaciones/segundo=%lg \n",1.0e-6*NUM/seconds*2); //se multiplica por dos pues se hace 2 veces
	}

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

//Halla el vector de trasformada a[6]
//En a[6] viajan juntos a[] y b[], siendo: a[6]= {a[0],a[1],a[2], b[0],b[1],b[2]}
int trasformada3p_hallacoef(__int16 coor1[6],__int16 coor2[6],double a[6]) 
{
	double *b=a+3;
	double x10=coor1[2]-coor1[0];
	double x20=coor1[4]-coor1[0];
	double y10=coor1[3]-coor1[1];
	double y20=coor1[5]-coor1[1];
	double x11=coor2[2]-coor2[0];
	double x21=coor2[4]-coor2[0];
	double y11=coor2[3]-coor2[1];
	double y21=coor2[5]-coor2[1];
	double det;det=x10*y20-y10*x20;
	if (det==0) return 0;//fail
	a[0]=coor2[0]+  (  -coor1[0]*x11*y20 + coor1[1]*x11*x20 -coor1[1]*x21*x10 +x21*y10*coor1[0] )/det;					//a[0] se multiplica por 1 para hallar x'
	a[1]=( y20*x11 - y10*x21) /det; //a[1] se multiplica por x para hallar x'
	a[2]=(-x20*x11 + x10*x21) /det; //a[2] se multiplica por y para hallar x'
	b[0]=coor2[1]+  (  -coor1[0]*y11*y20 + coor1[1]*y11*x20 -coor1[1]*y21*x10 +y21*y10*coor1[0] )/det;					//b[0] se multiplica por 1 para hallar y'
	b[1]=( y20*y11 - y10*y21) /det; //b[1] se multiplica por x para hallar y'
	b[2]=(-x20*y11 + x10*y21) /det; //b[2] se multiplica por y para hallar y'
	return 1;
}

//Usa el vector de trasformada a[6] calculado en la funcion anterior
void transformada3P(double a[6],__int16 xy1[2],__int16 xy2[2])
{
	xy2[0]=(__int16) (0.5+a[0]+a[1]*xy1[0]+a[2]*xy1[1]);
	double *b=a+3;                                         //a[6]= {a[0],a[1],a[2], b[0],b[1],b[2]}
	xy2[1]=(__int16) (0.5+b[0]+b[1]*xy1[0]+b[2]*xy1[1]);
}



//float
int trasformada3p_hallacoef(__int16 coor1[6],__int16 coor2[6],float a[6]) 
{
	float *b=a+3;
	float x10=(float) (coor1[2]-coor1[0]);
	float x20=(float) (coor1[4]-coor1[0]);
	float y10=(float) (coor1[3]-coor1[1]);
	float y20=(float) (coor1[5]-coor1[1]);
	float x11=(float) (coor2[2]-coor2[0]);
	float x21=(float) (coor2[4]-coor2[0]);
	float y11=(float) (coor2[3]-coor2[1]);
	float y21=(float) (coor2[5]-coor2[1]);
	float det;det=(float) (x10*y20-y10*x20);
	if (det==0) return 0;//fail
	a[0]=coor2[0]+  (  -coor1[0]*x11*y20 + coor1[1]*x11*x20 -coor1[1]*x21*x10 +x21*y10*coor1[0] )/det;					//a[0] se multiplica por 1 para hallar x'
	a[1]=( y20*x11 - y10*x21) /det; //a[1] se multiplica por x para hallar x'
	a[2]=(-x20*x11 + x10*x21) /det; //a[2] se multiplica por y para hallar x'
	b[0]=coor2[1]+  (  -coor1[0]*y11*y20 + coor1[1]*y11*x20 -coor1[1]*y21*x10 +y21*y10*coor1[0] )/det;					//b[0] se multiplica por 1 para hallar y'
	b[1]=( y20*y11 - y10*y21) /det; //b[1] se multiplica por x para hallar y'
	b[2]=(-x20*y11 + x10*y21) /det; //b[2] se multiplica por y para hallar y'
	return 1;
}

//Usa el vector de trasformada a[6] calculado en la funcion anterior
void transformada3P(float a[6],__int16 xy1[2],__int16 xy2[2])
{
	xy2[0]=(__int16) (0.5+a[0]+a[1]*xy1[0]+a[2]*xy1[1]);
	float *b=a+3;                                         //a[6]= {a[0],a[1],a[2], b[0],b[1],b[2]}
	xy2[1]=(__int16) (0.5+b[0]+b[1]*xy1[0]+b[2]*xy1[1]);
}