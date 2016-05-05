/*
Resolución de ecuaciones o problemas multidimensionales por el método del cubo
Soluciona el efecto frontera 
La funcion principal es ia_cubo_hilo2() que es como ia_cubo() pero HILOS=2 
y ya no calcula esquinas PERO está expuesto a mínimos locales
OJO: ES inutil que bucles sea mayor de 15!!!
Mejoras de V102: Incluye orden[] que indica quien reduce más. 
                 Además copia MIN y MAX y de ese modo no los modifica si hay llamadas sucesivas
Mejoras de V103: Incluye funcion de prediccion y halla_error_total que halla dicho error
Si se desea EVITAR mínimos locales usar ia_cubo()
*/
#include <stdio.h>
#include <math.h>
#include <memory.h>
#define DIM   19 //Se recomienda no pasar de 20 dimensiones
#define HILOS 5   //MINIMO=4. SOLO lo usa ia_cubo()
#define NEU   625//Usado por ia_cubo_hilo2()=HILOS^DIM DIM=4, HILOS/NEU=4/256,5/625,6/1296,7/2401,8/4096,10/10000
#define NEU2  524288//=2^DIM, usado por ia_cubo_hilo2() 
#define RES_P 1e-14 //Resolucion de funcion() en porcentaje:     Se considera que A=B si fabs((A-B)/(A+B))<RESOL_P
#define RES_A 0.0   //Resolucion de funcion() en valor absoluto: Se considera que A=B si fabs(A-B)        <RESOL_A
#define IMPRIME 1	//Si 1 escribe log en out.txt. 
//De rutina prediceStock y halla_error_totalStock:
#define VARS0 19//Coeficientes a multiplicar por valor
#define VARS1 0 //Coeficientes a multiplicar por volumen. VARS0+VARS1=DIM

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

double MIN4[20];
double MAX4[20];
double valor[200]={41.15,40.99,40.51,40.45,40.23,42.08,42.85,43.47,45.97,46.69,47.42,47.46,46.59,45.98,47.61,47.33,47.11,46.10,45.98,45.83,46.61,45.80,46.40,47.11,47.22,47.06,46.13,45.02,45.44,45.42,43.23,43.37,42.99,43.15,44.23,45.35,45.89,45.78,46.55,46.85,47.52,48.37,48.25,48.19,47.67,47.11,47.87,46.21,46.02,46.06,45.34,46.18,46.69,47.45,46.16,45.85,47.06,46.37,46.26,44.54,46.28,44.96,45.84,47.91,48.25,47.45,48.15,49.54,48.69,48.58,49.02,48.1,50.53,50.3,52.2,52.04,53,52.61,53.11,54.02,53.93,53.36,53.32,53.38,53.85,53.45,54.05,54.2,54.02,53.89,53.79,53.64,53.17,53.74,53.68,53.28,53.39,52.89,52.93,53.42,53.58,53.34,52.97,53.01,52.13,52.81,52.22,52.41,52.3,52.16,52.07,51.74,51.86,51.58,51.65,51.72,51.13,51.11,51.56,50.68,50.92,50.2,50.04,50.37,50.71,50.42,50.38,49.77,48.94,48.33,48,48.53,48.1,47.15,46.91,48.19,48.47,48.3,47.37,48.37,49.4,49.77,50.1,49.55,51.01,52.41,52.26,52.1,52.59,52.23,52.2,52.03,52.58,52.1,52.19,52.53,52.14,51.54,52.82,52.28,52.62,52.88,52.26,52.47,51.94,51.49,50.9,50.94,50.9,50.52,49.95,50.09,49.97,49.03,49.08,49.48,49.12,49.23,49.37,49.39,48.97,48.94,50.34,50.6,50.43,49.58,50.19,51.03,50.36,49.89,49.71,49.65,49.82,49.81,49.07,48.68,48.37,47.96,47.79,47.43};
double volumen[200];//No lo tengo :(
void inicia_funcion4(void) { long i;for (i=0;i<20;i++) { MIN4[i]=-1.5;MAX4[i]=1.0; } }
void halla_error_totalStock(double valor[],double volumen[],double ava[],double avu[],long dia,long desde, long dias,double &error_total,double &dif_med);
double funcion4(double a[DIM])
{
	double error_total,dif_med;
	halla_error_totalStock(valor,volumen,a,a+VARS0,90,6,70,error_total,dif_med);//prediccion a 6 días desde dia 100 durante 80 días atrás

	return error_total;
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
	inicia_funcion4();
	double resultado[DIM],orden[DIM];
	long BUCLES=7;

	/*
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

	*/
	if (IMPRIME)
	{
		FILE *out=fopen("out.txt","w");
		if (!out)
		{
			printf("\nERROR\n");
		}
		else 
		{
			for (BUCLES=25;BUCLES<26;BUCLES+=5)
			{
				printf("\nBUCLES:%li",BUCLES);
				ia_cubo_hilo2(funcion4,MIN4,MAX4,resultado,BUCLES,orden);
				fprintf(out,"BUCLES=%li Result:",BUCLES);
				long i;
				for (i=0;i<DIM;i++)
					fprintf(out,"\t%lg",resultado[i]);
				fprintf(out,"\tOrden:");
				for (i=0;i<DIM;i++)
					fprintf(out,"\t%lg",orden[i]);
				fprintf(out,"\n");
			}
			double *a;a=resultado;
			double error_total,dif_med;
			halla_error_totalStock(valor,volumen,a,a+VARS0,100,6,10,error_total,dif_med);//prediccion a 6 días desde dia 90 durante 10 días atrás
			printf("\nERROR_TOTAL=%lg",error_total);
			printf("\nDIF_MED    =%lg",dif_med);
			printf("\nGANANCIA   =%lg",(dif_med-error_total)/dif_med);
			fprintf(out,"\nERROR_TOTAL=%lg",error_total);
			fprintf(out,"\nDIF_MED    =%lg",dif_med);
			fprintf(out,"\nGANANCIA   =%lg",(dif_med-error_total)/dif_med);

			long i;
			fprintf(out,"\na:");
			for (i=0;i<DIM;i++)
				fprintf(out,"\t%lg",a[i]);
			fprintf(out,"\n");

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


//Predice un valor de un valor de bolsa y volumen movido. ava y avu son los coeficientes
//Lo predice en un "dia" y "desde" unos días antes
//Mete el valor predicho en valorP y el error en error
void prediceStock(double valor[],double volumen[],double ava[],double avu[],long dia,long desde, double &valorP, double &error)
{
	valorP=ava[0];
	long i;
	for(i=1;i<VARS0;i++)
	{
		valorP+=ava[i]*valor[dia-desde-i+1];
	}
	for(i=0;i<VARS1;i++)
	{
		valorP+=avu[i]*volumen[dia-desde-i];
	}
	error=fabs(valorP-valor[dia]);//Este valor es valido solo si se conoce valor[dia]
}
//Halla error a reducir modificando ava y avu. dias es el numero de dias anteriores usados para que se usan par hacer el calculo
void halla_error_totalStock(double valor[],double volumen[],double ava[],double avu[],long dia,long desde, long dias,double &error_total,double &dif_med)
{
	error_total=dif_med=0.0;
	double error,valorP;
	long i;
	for(i=0;i<dias;i++)
	{
		prediceStock(valor,volumen,ava,avu,dia-i,desde,valorP,error);
		error_total+=error;
		dif_med+=fabs(valor[dia-i]-valor[dia-i-desde]);
	}
	error_total= 1.0*error_total/dias;
	dif_med=     1.0*dif_med/dias;
}

