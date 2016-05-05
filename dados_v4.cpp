//ATENCION: se suma al que gana - el valor del que pierde
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define INIMAX 51 

void main()
{
	long veces;
	long sumam[INIMAX*3+1],*suma=sumam+INIMAX*2;
	printf("\nVeces se juega (>1000000):");scanf("%li",&veces);
	long lanzamientos;
	
	FILE *stream=fopen("out.txt","w");
	printf(        "\nSe suma al que gana - lo que queda al que pierde");
	fprintf(stream,"\nSe suma al que gana - lo que queda al que pierde");

	long INI;
	for (INI=6;INI<INIMAX;INI++)
	{
		memset(sumam,0,(INIMAX*3+1)*sizeof(long));
		//la matriz suma[i]=veces que la diferencia es i

		lanzamientos=0;
		for (long i=0;i<veces;i++)
		{
			if (i % 10000 == 0) printf("\n%li %li",INI,i);
			long v1=INI,v2=INI;// valores iniciales desde donde se resta
			while((v1>0))
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
			if (v2<-2*INI)
				v2=-2*INI;
			suma[v2]++;
		}

		double suma_m[INIMAX*3+1],*suma4=suma_m+2*INIMAX;//suma3[i]= Prob dif sea <= i
		for (i=-INI*2;i<=INI;i++)
		{
			suma4[i]=1e-10;
			for (long j=i;j<=INI;j++)
				suma4[i]+=suma[j];
		}

		printf(        "\n");
		fprintf(stream,"\n");
		printf(        "\nINICIAL=%li puntos \nNum medio de Lanzamientos=%lg",INI,1.0*lanzamientos/veces);
		fprintf(stream,"\nINICIAL=%li puntos \nNum medio de Lanzamientos=%lg",INI,1.0*lanzamientos/veces);
		printf(        "\nDif\tveces\t    Prob\tProb>=Dif\tProb<Dif");
		fprintf(stream,"\nDif\tveces\t    Prob\tProb>=Dif\tProb<Dif");
		for (i=-INI*2;i<=INI;i++)
		{
			printf(        "\n%li\t%li\t%8.2lf\t%8.2lf\t%8.2lf",i,suma[i],100.0*suma[i]/suma4[-2*INI],100.0*suma4[i]/suma4[-2*INI],100.0*(suma4[-2*INI]-suma4[i])/suma4[-2*INI]);
			fprintf(stream,"\n%li\t%li\t%8.2lf\t%8.2lf\t%8.2lf",i,suma[i],100.0*suma[i]/suma4[-2*INI],100.0*suma4[i]/suma4[-2*INI],100.0*(suma4[-2*INI]-suma4[i])/suma4[-2*INI]);
		}
	}
	fclose(stream);
	getchar();
	getchar();
}