//Funciona fenómeno!!!
//Probado usando inversa.xls
//Devuelve un valor < dimension si hay una fila que es 
//multiplo de las otras. El valor devuelto es la fila correspondiente 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void imprimematriz(double *x,char s[256],int dimension);


long inversa(double *x2,double *y,long dim)//x es la entrada e y la salida
{
	int i,j,ord;
	double *x=new double[dim*dim];
	//1. Hacemos la matriz y=unidad  y 
	//   copiamos la matriz x[]=x2[]
	for (i=0;i<dim*dim;i++) {y[i]=0.0;x[i]=x2[i];}
	for (i=0;i<dim    ;i++) y[i*dim+i]=1.0;

	double diagon,coef;
	double *ptrx,*ptry,*ptrx2,*ptry2;
	for (ord=0;ord<dim;ord++)
	{
      //2 Hacemos diagonal de x =1
		diagon=x[ord*dim+ord];
	    if (fabs(diagon)<1e-15) 
		{
			long i2;
			for (i2=ord+1;i2<dim;i2++)
			{
				if (fabs(x[ord*dim+i2]>1e-15) break;
			}
			if (i2>=dim)
				return ord;//error
			for (i=0;i<dim;i++)//sumo la linea que no es 0 el de la misma fila de ord
			{
				x[(ord+i)*dim+ord]+=x[(ord+i)*dim+i2];
			}
		}
		ptry=y+dim*ord;
		for (i=0;i<dim;i++)
			*ptry++/=diagon;
		ptrx=x+dim*ord+ord;  
		for (i=ord;i<dim;i++)//para i<ord *ptrx=0,
			*ptrx++/=diagon;      

		//Hacemos '0' la columna ord salvo elemento diagonal:
		for (i=0;i<dim;i++)//Empezamos por primera fila
		{
			if (i==ord) continue;
			coef=x[dim*i+ord];//elemento ha hacer 0 
			if (fabs(coef)<1e-15) continue; //si es cero se evita
			ptry =y+i*dim;
			ptry2=y+ord*dim;
			for (j=0;j<dim;j++)
				*ptry++=*ptry-coef * (*ptry2++);
			ptrx =x+i*dim+ord;
			ptrx2=x+ord*dim+ord;
			for (j=ord;j<dim;j++)
				*ptrx++=*ptrx-coef * (*ptrx2++);
		}
	}//end ord
	//imprimematriz(x," Debe ser matriz UNO",dim);
	delete[] x;
	return dim;
}

//[y]=[[x]]*[b]   : se trata de hallar coeficientes b
void ecuacion_lineal(double *x,double *y,long dimension,double *b)
{
	double *y2=new double[dimension*dimension];
	long i,j;
	i=inversa(x,y2,dimension);
	if (i<dimension)
	{
		printf("ERROR, matriz de determinante 0");
		return;
	}
	for (i=0;i<dimension;i++)
	{
		b[i]=0.0;
		for (j=0;j<dimension;j++)
		{
			b[i]+=y2[i*dimension+j]*y[j];
		}
	}
	delete[] y2;
}

void multiplicamatriz(double *x,double *y,double *z,long dim) //Hace z[]=x[]*y[] de dimensiones dim*dim
{
	long i,j,k;
	for (i=0;i<dim;i++)
	{
		for (j=0;j<dim;j++)
		{
			double *ptr=z+i*dim+j;
			*ptr=0.0;
			for (k=0;k<dim;k++)
			{
				*ptr+=x[j*dim+k]*y[i+k*dim];
			}
		}
	}
}

void imprimematriz(double *x,char s[256],int dimension)
{
   int i,j;

   printf("matriz:%s\n",s);
   for (i=0;i<dimension;i++)
   {
      for (j=0;j<dimension;j++)
         printf(" %-12.5g",x[i*dimension+j]);
      printf("\n");
   }
}


void main()
{
/*
//================================================================
//Test de inversa() . comparar con inversa.xls (segunda hoja)
	int i;
    int dimension=6;
	double x[36]={
					29.90456668, 91.6310734, 95.11969233, 65.89695418, 47.29098506, 48.5516911, 
					68.53960075, 0.422299858, 66.80371547, 25.25666134, 9.968854899, 7.798476342, 
					90.14221218, 29.8817849, 56.30880247, 94.80044559, 36.33781364, 60.68783272, 
					52.73796509, 38.96055445, 26.28223479, 76.75441905, 66.2412811, 31.55942456, 
					61.15573024, 21.5497427, 29.15186, 79.20863651, 92.62377313, 78.06450372, 
					37.58852783, 19.34797432, 15.42594596, 74.81868376, 86.13722492, 93.24559663
				};
	//for (i=0;i<36;i++) x[i]+=5.0*rand()/RAND_MAX;

   char c;

   double x2[36];

   imprimematriz(&x[0]," input",dimension);
   inversa(x,x2,dimension);
   imprimematriz(&x2[0]," inversa",dimension);
   double z[36];
   multiplicamatriz(x,x2,z,dimension);
   imprimematriz(&z[0]," input*inversa",dimension);
*/
//================================================================
//Test de ecuacion_lineal()  ver inversa.xls 
	double data[]={
//		x0	x1	x2	 x3	   x4	x5	 z
		1, 0.561360117, -1.141095618, -2.193980008, 1.367327156, -0.985369311, 7.13640859, 
		1, 0.921574316, -0.078140769, -1.324150619, 1.130865498, -0.37336718, 8.738914997, 
		1, 0.617398977, -0.746849826, -0.599377486, 1.228794264, 0.283368808, 9.703089557, 
		1, 0.112834435, -1.010671318, -1.391801449, 1.886188026, -0.87978309, 7.800543403, 
		1, 0.363886423, -1.124560138, -1.834441794, 1.988738433, 0.479731715, 8.507667583, 
		1, 0.296105163, -0.165377208, -2.721068535, 1.407666805, -0.072639515, 7.882035678, 
	0};

	double x1[36],z1[6],*ptr,*ptrx;
	long i,j;ptr=data;ptrx=x1;
	for (i=0;i<6;i++)
	{
		for (j=0;j<6;j++)
		{
			*ptrx++=*ptr++;
		}
		z1[i]=*ptr++;
	}

	double coef[6];
	ecuacion_lineal(x1,z1,6,coef);
	double coef2[]={10.82,-0.2211,0.33,0.8,-0.41,0.88};
	for (i=0;i<6;i++)
		printf("\nError coef[%li]=%lg",i,coef[i]-coef2[i]);

	i=i;

	char c;
	scanf("%c%c",&c,&c);
}



