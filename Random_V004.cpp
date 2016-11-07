#include <iostream>  //cin,cout
#include <stdlib.h> //rand

using namespace std;



#define RANS_SIZE 131072 //<131072
class c_rans
{
public:
	c_rans()
	{ 
		matriz_long=new long[RANS_SIZE];matriz_float=new float[RANS_SIZE];
		index=0;long i;for (i=0;i<RANS_SIZE;i++) {matriz_long[i]= i;matriz_float[i]=1.0f*i/RANS_SIZE;}; //valor mas cerca de 1= 131071/131072
		desordena_long();desordena_float();
	}
	long rans_long(void){ index=(index+1)%RANS_SIZE; return matriz_long[index];}   //devuelve 0 a (131072-1)
	float rans_float(void){ index=(index+1)%RANS_SIZE;return matriz_float[index];} //devuelve 0 a 1
	~c_rans() { delete matriz_long;delete matriz_float;}
private:
	long index;
	long *matriz_long;
	float *matriz_float;
	//k desordena 17 veces
	void desordena_float() { float v0; for (long k = 0; k<17; k++) for (long i = 0; i<RANS_SIZE; i++) 	{ v0 = matriz_float[i]; long j = rand(); j = ((j << 15) + rand()) % RANS_SIZE; 	matriz_float[i] = matriz_float[j]; matriz_float[j] = v0; } }
	void desordena_long();
};


int main()
{
	long i;
	const long vector_size=RANS_SIZE;
	c_rans rans;

	long *casos=new long[vector_size];
	memset(casos,0,vector_size*sizeof(long));
	for (i=0;i<vector_size;i++)
	{
		long ix=rans.rans_long();
		if (ix>=RANS_SIZE)
			cout << "ERROR ix="<<ix<<endl;
		casos[ix]++;
	}
	long errores=0;
	for (i=0;i<vector_size;i++)
	{
		if (casos[i]!=1)
		{
			cout << "error en indice long=" <<i<<endl;
			errores++;
		}
	}
	cout << "=======================\nerrores long totales=" <<errores<<endl;


	memset(casos,0,vector_size*sizeof(long));
	for (i=0;i<vector_size;i++)
	{
		long ix;
		ix=(long) (RANS_SIZE*rans.rans_float());
		if (ix>=RANS_SIZE)
			cout << "ERROR ix="<<ix<<endl;
		casos[ix]++;
	}
	errores=0;
	for (i=0;i<vector_size;i++)
	{
		if (casos[i]!=1)
		{
			cout << "error en indice float=" <<i<<endl;
			errores++;
		}
	}
	cout << "=======================\nerrores float totales=" <<errores<<endl;


//	for (i=0;i<500;i++) printf("%10.0f",vector[i]);

	delete casos;
	cout <<"\n=== FIN ===="<<endl; getchar();getchar();
    return 0;
}

void c_rans::desordena_long()
{
	long v0;
	long i, j, k;
	for (k = 0; k<17; k++)//desordena 17 veces
		for (i = 0; i<RANS_SIZE; i++)
		{
			v0 = matriz_long[i];
			j = rand(); j = ((j << 15) + rand()) % RANS_SIZE; //hasta 32 bits!!
			matriz_long[i] = matriz_long[j]; matriz_long[j] = v0;
		}
}