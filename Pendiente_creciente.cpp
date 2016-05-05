//Mira si la funcion lograda el error crece o por el contrario tiene minimos locales. A mayor valor pues mejor
//También mira si es decreciente en cuyo caso a mas negativo pues mejor 
#include <stdio.h>
#include <math.h> //fabs()
#define NUM 101 //usado en tamaño de matriz de pruebas

//funciones de escalabilidad. Max=deltaY/N. Tiende a 0 si detecta minimos locales
//Funciona en 1 dimension cuando deltax=1 (m[]={error[x=0],,error[x=1],error[x=2],...}:
double escalabilidad_f(double *m,long N);
//meter en x=distancia sin signo desde el centro, y=error relativo
double escalabilidad_f(double *x,double *y,long N);
//se mete distancia al objetivo y error. El error debe disminuir con la distancia
#define COEF_ESCALA 3.0  //coeficiente que se le mete al error. si un elemento está a menos distancia de otro y el error es mayor, éste se multiplica por COEF
double escalabilidad2_f(double *distancia,double *error,long N);

void main()
{
	double z[NUM],x[NUM];
	long i,j;
	double ex,delta=4.0;//error en cada punto y delta
	for (j=0;j<NUM;j++) x[j]=j; //deltax=1


	for (i=0;i<12;i++) //12 niveles de error
	{
		ex=0.1*delta*i;
		for (j=0;j<NUM;j++)
		{
			z[j]=delta*j;
			if (j&1) z[j]+=ex;
			else     z[j]-=ex;
		}
		double u1,u2;
		u1=escalabilidad_f(z,NUM);
		u2=escalabilidad_f(x,z,NUM);

		double u3;
		double err[NUM];
		for (j=0;j<NUM;j++)
		{
			err[j]=delta*(NUM-j);
			if (j&1) err[j]+=ex;
			else     err[j]-=ex;
		}
		u3=escalabilidad2_f(x,z,NUM);
		printf("\nDelta=%lg \tError=+-%lg \tescala0=%lg \tescala1=%lg \tescala1=%lg",delta,ex,u1,u2,u3);
	}
	printf("\n\n===FIN===");getchar();getchar();
}

double escalabilidad_f(double *m,long N)
{
	if (N<3) return 0;
	double dif=m[N-1]-m[0],dif2=0;;
	long i;
	for (i=2;i<N;i++)
		dif2+=fabs(m[i-2]+m[i]-2*m[i-1]);
	if (dif>0)
		return (  dif/(-1.0+N) - dif2/2.0/(-2.0+N) );
	else
		return (  dif/(-1.0+N) + dif2/2.0/(-2.0+N) );
}


double escalabilidad_f(double *x,double *y,long N)
{
	if (N<3) return 0;
	double sx=0.0,sy=0.0,sxx=0.0,sxy=0.0,p,a;
	long i;
	for (i=0;i<N;i++)
	{
		sx+=x[i];sy+=y[i];sxy+=x[i]*y[i];sxx+=x[i]*x[i];
	}
	p=(N*sxy-sx*sy)/(1e-199+N*sxx-sx*sx);//pendiente
	a=(sy-p*sx)/N; //offset
	double escalabilidad,y1,ymin=1e199,ymax=-1e199;
	for (i=0;i<N;i++)
	{
		y1=a+p*x[i];
		if (ymin>y1) ymin=y1;
		if (ymax<y1) ymax=y1;
	}
	escalabilidad=ymax-ymin;

	double error=0.0;
	for (i=0;i<N;i++)
	{
		y1=a+p*x[i];error+=fabs(y1-y[i]);
	}
	if (p>0)	return (escalabilidad-error)/(-1.0+N);
	else		return (escalabilidad+error)/(-1.0+N);
}

double escalabilidad2_f(double *distancia,double *error,long N)
{
	if (N<2) return 0;
	double escalabilidad=0.0,x;
	long i;
	for (i=1;i<N;i++)
	{
		x=distancia[i]-distancia[i-1]; if (fabs(x)<1e-5) continue;
		x=(error[i]-error[i-1])/x;
		if (x>0) escalabilidad+=x;
		else escalabilidad+=x*COEF_ESCALA;
	}
	return escalabilidad/(-1.0+N);
}
