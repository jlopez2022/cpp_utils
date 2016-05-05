#include <stdio.h>
#include <stdlib.h>
#define RANDMAX2 32768  // es RAND_MAX+1 OJO!!!


//Escoge valor (pos0,pos1,...pos_dim) entre (min0...) y (max0...)

//No incluye el valor máximo
void escoge_random(double *min,double *max,double *pos,long dim);
void escoge_random(long *min,long *max,long *pos,long dim);
//Incluye el valor máximo
void escoge_random_e(long *min,long *max,long *pos,long dim);

double random(void); //Da de 0 a 1 sin llegar a 1 nunca

void main()
{
	long i,j;
	{
		printf("\nHallo random entre min y max double, excluyendo max\n");
		double min[4]={100,200,500,1000};
		double max[4]={900,800,700,2000};
		double x[4];
		double min2[4]={1e99,1e99,1e99,1e99};
		double max2[4]={-1e99,-1e99,-1e99,-1e99};
		for (i=0;i<500000;i++)
		{
			escoge_random(min,max,x,4);
			for (j=0;j<4;j++)
			{
				if (i<10)
					printf("%lg\t",x[j]);
				if (min2[j]>x[j])
					min2[j]=x[j];
				if (max2[j]<x[j])
					max2[j]=x[j];
			}
			if (i<10)
				printf("\n");
		}
		printf("\n======================\nValores minimos:\n");
		for (j=0;j<4;j++)
			printf("%lg\t",min2[j]);
		printf("\nValores maximos:\n");
		for (j=0;j<4;j++)
			printf("%lg\t",max2[j]);
		printf("\n========================\n");
	}

	{
		printf("\nHallo random entre min y max long incluyendo max\n");
		//=========long	
		long min3[4]={ 2147483647, 2147483647, 2147483647, 2147483647};
		long max3[4]={-2147483647,-2147483647,-2147483647,-2147483647};

		long min4[4]={100,200,500,1000};
		long max4[4]={900,800,700,2000};
		long m[4];
		long i,j;
		for (i=0;i<500000;i++)
		{
			escoge_random_e(min4,max4,m,4);
			for (j=0;j<4;j++)
			{
				if (i<10)
					printf("%li\t",m[j]);
				if (min3[j]>m[j])
					min3[j]=m[j];
				if (max3[j]<m[j])
					max3[j]=m[j];
			}
			if (i<10)
				printf("\n");
		}
		printf("\n======================\nValores minimos:\n");
		for (j=0;j<4;j++)
			printf("%li\t",min3[j]);
		printf("\nValores maximos:\n");
		for (j=0;j<4;j++)
			printf("%li\t",max3[j]);
		printf("\n========================\n");
	}

	{
		printf("\nHallo random entre min y max long excluyendo max\n");
		//=========long	
		long min3[4]={ 2147483647, 2147483647, 2147483647, 2147483647};
		long max3[4]={-2147483647,-2147483647,-2147483647,-2147483647};

		long min4[4]={100,200,500,1000};
		long max4[4]={900,800,700,2000};
		long m[4];
		long i,j;
		for (i=0;i<500000;i++)
		{
			escoge_random(min4,max4,m,4);
			for (j=0;j<4;j++)
			{
				if (i<10)
					printf("%li\t",m[j]);
				if (min3[j]>m[j])
					min3[j]=m[j];
				if (max3[j]<m[j])
					max3[j]=m[j];
			}
			if (i<10)
				printf("\n");
		}
		printf("\n======================\nValores minimos:\n");
		for (j=0;j<4;j++)
			printf("%li\t",min3[j]);
		printf("\nValores maximos:\n");
		for (j=0;j<4;j++)
			printf("%li\t",max3[j]);
	}

	{
		printf("\nHallo random entre 0 y 1 double sin llegar a 1\n");
		double min=1e99,max=-1e99;
		for (i=0;i<500000;i++)
		{
			double x;
			x=random();
			if (i<10)
				printf("%lg\n",x);
			if (min>x)
				min=x;
			if (max<x)
				max=x;
		}
		printf("\n======================\nValor minimo:\n");
		printf("%lg\t",min);
		printf("\nValor maximo:\n");
		printf("%lg\t",max);
		printf("\n========================\n");
	}


	printf("\nFIN");getchar();getchar();
}


void escoge_random(double *min,double *max,double *pos,long dim)
{
	long i;
	for (i=0;i<dim;i++)
	{
		pos[i]=min[i]+1.0*(max[i]-min[i])*rand()/RANDMAX2;
	}
}

void escoge_random(long *min,long *max,long *pos,long dim)
{
	long i;
	for (i=0;i<dim;i++)
	{
		pos[i]=min[i]+((max[i]-min[i])*rand())/RANDMAX2;
	}
}

void escoge_random_e(long *min,long *max,long *pos,long dim)
{
	long i;
	for (i=0;i<dim;i++)
	{
		pos[i]=min[i]+(long) ( 0.5+1.0*(max[i]-min[i])*rand()/RAND_MAX );
	}
}

double random(void)
{
	return(1.0*rand()/RANDMAX2);
}

