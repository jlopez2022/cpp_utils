#include <stdio.h>
#include <stdlib.h>//rand() used
#include <time.h> //initialization

//Definitions, constants and functions used:
#define SWAP(t,a,b) ( (t) = (a), (a) = (b), (b) = (t) )    //use: SWAP(dtemp, d1, d2);
#define RANS_MAX 131072
double rans_m[RANS_MAX];
double rans();//generates random number 0 <= rans() < 1
__int16 rans(__int16 max) {	return ( (__int16) (max*rans()) ); } //as rans() but generates number between 0 and max-1
void  srans(long seed); //Must be run one time before using rans()


long main()
{
	srans(time (NULL));//initializes rands_m[]
	long sum[101];
	long i,max=100,NUM=10000000L;
	for (i=0;i<100+1;i++) sum[i]=0;

	for (i=0;i<NUM;i++)
	{
		sum[rans(max)]++; 
	}
	long min=LONG_MAX,max1=-1;
	for (i=0;i<max;i++) 
	{
		if (min>sum[i]) min=sum[i];
		if (max1<sum[i]) max1=sum[i];
	}
	printf("\nMinimum repeatings=%li",min);
	printf("\nMaximum repeatings=%li",max1);
	printf("\nMaximum-minimums  =%li (less is better)",max1-min);

	printf("\nRelative error    =%lg ./.",100.0*max*(max1-min)/NUM ) ;
	if (sum[max]!=0) printf("\nFAILS maximum value reached one time every %lg", (double) (1.0*NUM/sum[max]));
	printf("\n\n===FIN===");getchar();getchar();
	return 1;
}



void  srans(long seed=0)
{
	seed=seed%(1024L*1024L);//limited to 1Meg
	long i,k,l=0;double temp;
	for (i=0;i<RANS_MAX;i++) rans_m[i]=1.0*i/RANS_MAX;
	for (i=0;i<(8L*1024L*1024L);i++)
	{
		k=i % RANS_MAX;l=(k+rand()) % RANS_MAX;
		SWAP(temp,rans_m[k],rans_m[l]);
		//temp=rans_m[k];rans_m[k]=rans_m[l];rans_m[l]=temp;
	}
	for (i=0;i<(seed % RANS_MAX);i++) //seed is applied, but not longer than 128k times
		rans();
}

double rans()
{
	static int index=-1;
	index=(index+1)% RANS_MAX; //index must be < RANS_MAX
	return rans_m[index];
}

