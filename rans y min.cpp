/* frexp example */
#include <stdio.h>      /* printf */
#include <stdlib.h> //rand
#define SWAP(t,a,b) ( (t) = (a), (a) = (b), (b) = (t) ) 
#define MAX 25

double a[MAX];

#define RANS_MAX 131072
class c_rand
{
public:
	c_rand(long seed);
	~c_rand(){ delete rans_m; }
	double rans() { rans_index=(rans_index+1)% RANS_MAX;  return rans_m[rans_index]; }
	//__int16 rans(__int16 max) {	return ( (__int16) (max*rans()) ); } //as rans() but generates integers between 0 and max-1
private:
	long rans_index;
	double *rans_m;
	//generates random number 0 <= rans() < 1
};



int main ()
{
	c_rand crand(7);
	long i,j;
	for (j=0;j<4;j++)
	{
		for (i=0;i<MAX;i++)
		{
			a[i]=20*crand.rans();
			printf("%2li:%lg\n",i,a[i]);
		}
		long imin=0;
		for (i=1;i<MAX;i++)
		{
			imin=(a[i]<a[imin]) ? i : imin ;
		}
		printf("imin=%2li a[imin]=%lg\n\n",imin,a[imin]);
	}
	printf("\n\nFIN\n");getchar();getchar();
	return 0;
}

c_rand::c_rand(long seed=0)
{
	rans_m=new double[RANS_MAX];
	rans_index=-1;
	srand(seed);
	seed=seed%(1024L*1024L);//limited to 1Meg
	long i,k,l=0;double temp;
	for (i=0;i<RANS_MAX;i++) 
		rans_m[i]=1.0*i/RANS_MAX;
	for (i=0;i<(8L*1024L*1024L);i++)
	{
		k=i % RANS_MAX;l=(k+rand()) % RANS_MAX;
		SWAP(temp,rans_m[k],rans_m[l]);
		//temp=rans_m[k];rans_m[k]=rans_m[l];rans_m[l]=temp;
	}
	for (i=0;i<(seed % RANS_MAX);i++) //seed is applied, but not longer than 128k times
		rans();
}
