//Resolución de ecuaciones o problemas multidimensionales por el método del cubo
//Soluciona el efecto frontera 
//Como IA_cubo_V102 pero HILOS=2 y ya no calcula esquinas PERO está expuesto a mínimos locales
//OJO: ES inutil que bucles sea mayor de 15!!!
//Mejoras de V102: Incluye orden[] que indica quien reduce más. 
//                 Además copia MIN y MAX y de ese modo no los modifica si hay llamadas sucesivas
//La funcion principal es ia_cubo_hilo2()
//Si se desea EVITAR mínimos locales usar ia_cubo()
#include <stdio.h>
#include <math.h>
#include <memory.h>
#define DIM   4 //Se recomienda no pasar de 20 dimensiones
#define HILOS 5   //MINIMO=4. SOLO lo usa ia_cubo()
#define NEU   625//Usado por ia_cubo_hilo2()=HILOS^DIM DIM=4, HILOS/NEU=4/256,5/625,6/1296,7/2401,8/4096,10/10000
#define NEU2  16//=2^DIM, usado por ia_cubo_hilo2() 
#define RES_P 1e-14 //Resolucion de funcion() en porcentaje:     Se considera que A=B si fabs((A-B)/(A+B))<RESOL_P
#define RES_A 0.0   //Resolucion de funcion() en valor absoluto: Se considera que A=B si fabs(A-B)        <RESOL_A
#define IMPRIME 1	//Si 1 escribe log en out.txt. 


/*
Resultado:
Buc.ia_cubo	ia_cubo_hilo2
2	22.92%	66.67%
3	2.08%	53.33%
4	1.09%	20.05%
5	3.22%	16.41%
6	0.37%	8.64%
7	0.00%	6.42%
8	0.05%	3.89%
9	0.23%	2.44%
10	0.13%	1.68%
11	0.06%	1.09%
12	0.03%	0.74%
13	0.01%	0.50%
14	0.01%	0.33%
15	0.00%	0.22%
*/

typedef double (*FUNCT)(double[DIM]);
//Esta no la uso, sirve para modificar el centro:
double fmmm1(double x,double min,double med,double max);//if-1

//===Definicion de la funcion y sus limites===
//minimo y maximo absolutos
double MIN1[4]={-11.0,-11.0,-5.0,-0.0};
double MAX1[4]={ 11.0, 11.0, 5.0,0.04};
double funcion1(double x[DIM]) //funcion a hallar el minimo, debe ser: 10, 3, -0.1, 0.035
{
	double f=0.0;
	f =1.0e6 /(1.0+pow((fabs(x[0]-10.0)),5.0 ));
	f+=1.0e3 /(1.0+pow((fabs(x[1]- 3.0)),12.0));
	f+=1.0e-1/(1.0+pow((fabs(x[2]+0.1 )),8.0 ));
	f+=1.0e-3*sin((x[3]-0.005)*2.0*3.1416/.04);
	return -f;
}

double MIN2[4]={-10.0,-20.0,-5.0,-1.0};
double MAX2[4]={ 10.0, 20.0, 5.0, 1.0};
double funcion2(double x[DIM]) //funcion a hallar el minimo, debe ser: -5,10,-5,1.0
{
	double f=0.0;
	f =1.0e6 /(1.0+pow((fabs(x[0]+ 5.0 )),5 ));
	f+=1.0e4 /(1.0+pow((fabs(x[1]- 10.0)),4));
	f+=1.0e3 /(1.0+pow((fabs(x[2]+ 5.0 )),4 ));
	f+=1.0e2 /(1.0+pow((fabs(x[3]- 1.0 )),3 ));
	return -f;
}

double MIN3[4]={-10.0,-20.0,-5.0,-1.0};
double MAX3[4]={ 10.0, 20.0, 5.0, 1.0};
double funcion3(double x[DIM]) //funcion a hallar el minimo, debe ser: -9.9,19.3,-1.1,0.9
{
	double f=0.0;
	f =1.0e6 /(1.0+pow((fabs(x[0]+ 9.9 )),5 ));
	f+=1.0e4 /(1.0+pow((fabs(x[1]- 19.3)),4));
	f+=1.0e3 /(1.0+pow((fabs(x[2]+ 1.1 )),4 ));
	f+=1.0e2 /(1.0+pow((fabs(x[3]- 0.9 )),3 ));
	return -f;
}



//===

//Rutina principal. bucles es el número de veces que se aplica y debe ser<85
//orden es el orden de mejor a peor en cada dimension
void ia_cubo_hilo2(FUNCT fun,double MIN[DIM],double MAX[DIM],double resultado[DIM],long bucles,double orden[DIM]);

//Rutina principal. bucles es el número de veces que se aplica y debe ser=15
//orden es el orden de mejor a peor en cada dimension
void ia_cubo(FUNCT fun,double MIN[DIM],double MAX[DIM],double resultado[DIM],long bucles,double orden[DIM]);
//Rutinas que emplea:
void hallacoor2(double MIN[DIM],double MAX[DIM],long *ix,double *x);
void hallaindice(long i,long ix[DIM]);//halla los indices segun i=0..hilos^dim y los mete en ix
void hallaindice1D(long ix[DIM],long &i);//Al reves que hallaindice():halla indice total segun índices ix[] y lo mete en i



int main()
{
	if (pow(2,DIM)!=NEU2)
	{
		printf("\nERROR en definicion de NEU2,no usar ia_cubo_hilo2()\n");getchar();getchar();
	}
	if (pow(HILOS,DIM)!=NEU)
	{
		printf("\nERROR en definicion de NEU,no usar ia_cubo()\n");getchar();getchar();
	}

	double resultado[DIM],orden[DIM];
	long BUCLES=7;
	ia_cubo_hilo2(funcion3,MIN3,MAX3,resultado,1,orden);
	ia_cubo_hilo2(funcion3,MIN3,MAX3,resultado,2,orden);
	ia_cubo_hilo2(funcion3,MIN3,MAX3,resultado,3,orden);
	ia_cubo_hilo2(funcion3,MIN3,MAX3,resultado,4,orden);
	ia_cubo_hilo2(funcion3,MIN3,MAX3,resultado,5,orden);
	ia_cubo_hilo2(funcion3,MIN3,MAX3,resultado,6,orden);
	ia_cubo_hilo2(funcion3,MIN3,MAX3,resultado,7,orden);
	ia_cubo_hilo2(funcion3,MIN3,MAX3,resultado,8,orden);
	ia_cubo_hilo2(funcion3,MIN3,MAX3,resultado,9,orden);
	ia_cubo_hilo2(funcion3,MIN3,MAX3,resultado,10,orden);
	ia_cubo_hilo2(funcion3,MIN3,MAX3,resultado,BUCLES,orden);
	ia_cubo_hilo2(funcion3,MIN3,MAX3,resultado,BUCLES+10,orden);

	if (IMPRIME)
	{
		FILE *out=fopen("out.txt","w");
		if (!out)
		{
			printf("\nERROR\n");
		}
		else 
		{
			for (BUCLES=1;BUCLES<20;BUCLES++)
			{
				ia_cubo_hilo2(funcion3,MIN3,MAX3,resultado,BUCLES,orden);
				fprintf(out,"BUCLES=%li Result:",BUCLES);
				long i;
				for (i=0;i<DIM;i++)
					fprintf(out,"\t%lg",resultado[i]);
				fprintf(out,"\tOrden:");
				for (i=0;i<DIM;i++)
					fprintf(out,"\t%lg",orden[i]);
				fprintf(out,"\n");
			}

			fclose(out);
		}
	}//IMPRIME

	printf("\nFIN\n");getchar();getchar();
	return 1;
}


double fmmm1(double x,double min,double med,double max)//if-1
{
	if (x<0.5)
		return min+(med-min)*2.0*x;
	else
		return med+(max-med)*(2.0*x-1.0);
}


void ia_cubo_hilo2(FUNCT fun,double MIN1[DIM],double MAX1[DIM],double resultado[DIM],long bucles,double orden[DIM])
{
	long bucle,dim;
	memset(orden,0,DIM*sizeof(double));
	double MIN[DIM],MAX[DIM];
	memcpy(MIN,MIN1,DIM*sizeof(double));
	memcpy(MAX,MAX1,DIM*sizeof(double));
	for (bucle=0;bucle<bucles;bucle++)
	{
		double x[DIM],x0[DIM],x1[DIM];//x0=min*.66+max*.66 y x1=min*.33+max*.66
		double f[NEU2],fmin=1.0e299;
		long imin;
		for (dim=0;dim<DIM;dim++)
		{
			x0[dim]=(2.0*MIN[dim]+    MAX[dim])/3.0;
			x1[dim]=(    MIN[dim]+2.0*MAX[dim])/3.0;
		}
		long ix;//indice
		for (ix=0;ix<NEU2;ix++)//hallo la funcion en todos los puntos
		{
			for (dim=0;dim<DIM;dim++)
			{
				if (ix&(1<<dim))
					x[dim]=x1[dim];
				else
					x[dim]=x0[dim];
			}
			f[ix]=fun(x);
			if (fmin>f[ix])//Busco el minimo
			{
				fmin=f[ix];
				imin=ix;
			}
		}
		//Veo si hay reduccion para así recalcular MIN y MAX:
		for (dim=0;dim<DIM;dim++)
		{
			double ff;
			long i1=imin|(1<<dim);
			ff=f[i1]-f[imin&(~(1<<dim))];
			double ff1=fabs(ff);
			orden[dim]+=ff1;
			if ( (fabs(ff/fmin)>RES_P) || (ff1>RES_A))
			{
				if (imin==i1)//Veo si el minimo está más cerca de MAX
					MIN[dim]=x0[dim];//Si es así, reduzco por la izquierda siendo el minimo el punto de la izquierda
				else
					MAX[dim]=x1[dim];//Si no, el máximo se reduce ahora por la derecha
			}
		}
	}//bucle
	double sum=0.0;
	for (dim=0;dim<DIM;dim++)
	{
		resultado[dim]=0.5*(MIN[dim]+MAX[dim]);
		sum+=orden[dim];
	}
	for (dim=0;dim<DIM;dim++)
		orden[dim]/=sum;
}

void ia_cubo(FUNCT fun,double MIN1[DIM],double MAX1[DIM],double resultado[DIM],long bucles,double orden[DIM])
{
	long bucle,j;
	long ix_min1[DIM];
	memset(orden,0,DIM*sizeof(double));
	double MIN[DIM],MAX[DIM];
	memcpy(MIN,MIN1,DIM*sizeof(double));
	memcpy(MAX,MAX1,DIM*sizeof(double));
	for (bucle=0;bucle<bucles;bucle++)
	{
		if (bucle==9)
			bucle=bucle;
		long ix[DIM+1],i,j;//ix[] son los indices de las neuras en cada dimension: ix[DIM-1],...ix[3],ix[2],ix[1],ix[0]
		for (i=0;i<DIM;i++) ix[i]=0;
		ix[0]=-1;
		double f[NEU],fmin=1.0e299;
		long i_min;
		//1.0 inicio el bucle
		for (i=0;i<NEU;i++)
		{	//1.1. Hallo el indice aqui pues es más rápido que usar hallaindice()
			ix[0]++;
			for (j=0;j<DIM;j++)
			{
				if (ix[j] < HILOS)
					break;
				//else
				ix[j]=0;
				ix[j+1]++;//Por eso he hecho ix[DIM+1] en vez de ix[DIM]
			}
			//2.0 Ya tengo el indice, ahora saco la coordenada:
			double x[DIM];
			hallacoor2(MIN,MAX,ix,x);
			//3.0 Hallo el resultado y lo meto en f:
			f[i]=fun(x);
			if (fmin>f[i])
			{
				fmin=f[i];
				i_min=i;
			}
		}

		//4.0 Cambio MIN de cada dimension para reducir el cerco en caso de que sea necesario:
		long *ix_min=ix_min1;
		hallaindice(i_min,ix_min);
		long delta=1;
		for (j=0;j<DIM;j++)
		{
			double delta2;
			delta2=(MAX[j]-MIN[j])/(HILOS-1.0); 
			long i0,k;
			double ff;
			i0=ix_min[j];
			//5.0 Reduzco por la izquierda subiendo el MIN:
			for (k=1;k<=i0;k++)
			{
				ff=(f[i_min-delta*k]-fmin);
				double ff1=ff/fabs(fmin);
				if ( (ff1>RES_P) || (fabs(ff)>RES_A))
				{
					orden[j]+=ff1;
					MIN[j]=MIN[j]+(i0-k)*delta2;
					break;
				}
			}
			//6.0 Reduzco por la derecha bajando MAX
			for (k=1;k<(HILOS-i0);k++)
			{
				ff=fabs(f[i_min+delta*k]-fmin);//i0+delta*k esta MAL pues es lo mismo que i0-delta*k cuando k=0
				double ff1=ff/fabs(fmin);
				if (  (ff1>RES_P)  ||  (ff>RES_A)  )
				{
					orden[j]+=ff1;
					MAX[j]=MAX[j]-(HILOS-i0-k-1)*delta2;
					break;
				}
			}
			delta*=HILOS;//siguiente dimension
		}
		hallacoor2(MIN,MAX,ix_min,resultado);//QUITAR
	}
	hallacoor2(MIN,MAX,ix_min1,resultado);
	for (j=0;j<DIM;j++)
		resultado[j]=0.5*(MIN[j]+MAX[j]);
	j=j;
}


void hallacoor2(double MIN[DIM],double MAX[DIM],long *ix,double *x)
{
	long i;
	for (i=0;i<DIM;i++)
	{
		x[i]=MIN[i]+(0.0+ix[i])*(MAX[i]-MIN[i])/(HILOS-1.0);
	}
}

void hallaindice(long i,long ix[DIM])//halla los indices segun i=0..hilos^dim y los mete en ix
{
	long j;
	for (j=0;j<DIM;j++)
	{
		ix[j]=i % HILOS;
		i/=HILOS;
	}
}

void hallaindice1D(long ix[DIM],long &i)//Al reves que hallaindice():halla el indice total segun los índices ix[]
{
	long j;i=0;
	for (j=DIM-1;j>=0;j--)
	{
		i=i*HILOS+ix[j];
	}
}
