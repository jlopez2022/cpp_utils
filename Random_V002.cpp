#include <iostream>  //cin,cout
#include <stdlib.h> //rand

using namespace std;

void desordena(float vector[],long vector_size)
{
	float v0;
	long i,j,k;
	for (k=0;k<17;k++)
	for (i=0;i<vector_size;i++)
	{
		v0=vector[i];
		j=rand(); j=((j<<15)+rand()) % vector_size; //hasta 32 bits!!
		vector[i]=vector[j];vector[j]=v0;
	}
}

void desordena(long vector[],long vector_size)
{
	long v0;
	long i,j,k;
	for (k=0;k<17;k++)
	for (i=0;i<vector_size;i++)
	{
		v0=vector[i];
		j=rand(); j=((j<<15)+rand()) % vector_size; //hasta 32 bits!!
		vector[i]=vector[j];vector[j]=v0;
	}
}

int main()
{
	long i;
	const long vector_lon=23000;
	float vector[vector_lon];
	for (i=0;i<vector_lon;i++) vector[i]=(float) i;
	desordena(vector,vector_lon);
	
	for (i=0;i<500;i++) printf("%10.0f",vector[i]);


	cout <<"\n=== FIN ===="<<endl; getchar();getchar();
    return 0;
}