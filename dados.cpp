#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define INI 8 // valores iniciales desde donde se resta

void main()
{
	long veces;
	long sumam[INI*2+1],*suma=sumam+INI;
	printf("\nVeces se juega (>1000000):");scanf("%li",&veces);
	long lanzamientos;

	memset(sumam,0,(INI*2+1)*sizeof(long));
	//la matriz suma[i]=veces que la diferencia es i

	lanzamientos=0;
	for (long i=0;i<veces;i++)
	{
		if (i % 1000 == 0) printf("\n%li",i);
		long v1=INI,v2=INI;// valores iniciales desde donde se resta
		while((v1>0) && (v2>0))
		{
			lanzamientos++;
			long d1=(long) (6*rand()/RAND_MAX);//dado
			long d2=(long) (6*rand()/RAND_MAX);//dado
			long dif=d1-d2;
			if (dif>0)
				v2=v2-dif;
			else
				v1=v1+dif;
		}
		if (v2>v1)
			suma[v2]++;
		else suma[v1]++;
	}

	FILE *stream=fopen("out.txt","w");
	double suma3[INI+2];//suma3[i]= Prob dif sea >= i
	for (i=0;i<=INI;i++)
	{
		suma3[i]=0.0;
		for (long j=i;j<=INI;j++)
			suma3[i]+=suma[j];
	}
	suma3[INI+1]=0;


	printf(        "\nINICIAL=%li puntos \nNum medio de Lanzamientos=%lg",INI,1.0*lanzamientos/veces);
	fprintf(stream,"\nINICIAL=%li puntos \nNum medio de Lanzamientos=%lg",INI,1.0*lanzamientos/veces);
	printf(        "\nDif\tveces\t    Prob\tProb>=Dif\tProb>=-Dif");
	fprintf(stream,"\nDif\tveces\t    Prob\tProb>=Dif\tProb>=-Dif");
	for (i=0;i<=INI;i++)
	{
		printf(        "\n%li\t%li\t%8.2lf\t%8.2lf\t%8.2lf",i,suma[i],100.0*suma[i]/suma3[0],100.0*suma3[i]/(2*suma3[0]),100.0*(2*suma3[0]-suma3[i+1])/(2*suma3[0]));
		fprintf(stream,"\n%li\t%li\t%8.2lf\t%8.2lf\t%8.2lf",i,suma[i],100.0*suma[i]/suma3[0],100.0*suma3[i]/(2*suma3[0]),100.0*(2*suma3[0]-suma3[i+1])/(2*suma3[0]));
	}
	fclose(stream);
	getchar();
	getchar();
}