#include <iostream>  //cin,cout
#include <stdlib.h> //rand

using namespace std;



#define RANS_SIZE 131072 //must be <=131072


class c_rans_float
{
public:
	c_rans_float()
	{
		matriz_float = new float[RANS_SIZE];
		index = 0; long i; for (i = 0; i<RANS_SIZE; i++) { matriz_float[i] = 1.0f*i / RANS_SIZE; }; //valor mas cerca de 1= 131071/131072
		desordena_float();
	}
	float rans(void){ index = (index + 1) % RANS_SIZE; return matriz_float[index]; } //devuelve 0 a 1
	~c_rans_float() { delete matriz_float; }
private:
	long index;
	float *matriz_float;
	//k desordena 17 veces:
	void desordena_float() { float v0; for (long k = 0; k<17; k++) for (long i = 0; i<RANS_SIZE; i++) 	{ v0 = matriz_float[i]; long j = rand(); j = ((j << 15) + rand()) % RANS_SIZE; 	matriz_float[i] = matriz_float[j]; matriz_float[j] = v0; } }
}ranf;
//USAGE:   float x=ransf.rans();

class c_rans_double
{
public:
	c_rans_double()
	{
	matriz_double = new double[RANS_SIZE];
	index = 0; long i; for (i = 0; i<RANS_SIZE; i++) { matriz_double[i] = 1.0f*i / RANS_SIZE; }; //valor mas cerca de 1= 131071/131072
	desordena_double();
	}
	double rans(void){ index = (index + 1) % RANS_SIZE; return matriz_double[index]; } //devuelve 0 a 1
	~c_rans_double() { delete matriz_double; }
private:
	long index;
	double *matriz_double;
	//k desordena 17 veces:
	void desordena_double() { double v0; for (long k = 0; k<17; k++) for (long i = 0; i<RANS_SIZE; i++) 	{ v0 = matriz_double[i]; long j = rand(); j = ((j << 15) + rand()) % RANS_SIZE; 	matriz_double[i] = matriz_double[j]; matriz_double[j] = v0; } }
}randf;
//USAGE:   double x=randf.rans();



int main()
{
	long i;
	const long vector_size=RANS_SIZE;

	long *casos = new long[vector_size];
	{
		memset(casos, 0, vector_size*sizeof(long));
		for (i = 0; i < vector_size; i++)
		{
			long ix = (long)(RANS_SIZE*ranf.rans());
			if (ix >= RANS_SIZE)
				cout << "ERROR ix=" << ix << endl;
			casos[ix]++;
		}
		long errores = 0;
		for (i = 0; i < vector_size; i++)
		{
			if (casos[i] != 1)
			{
				cout << "error en indice long=" << i << endl;
				errores++;
			}
		}
		cout << "=======================\nerrores double totales=" << errores << endl;
	}

	{
		memset(casos, 0, vector_size*sizeof(long));
		for (i = 0; i < vector_size; i++)
		{
			long ix = (long)(RANS_SIZE*ranf.rans());
			if (ix >= RANS_SIZE)
				cout << "ERROR ix=" << ix << endl;
			casos[ix]++;
		}
		long errores = 0;
		for (i = 0; i < vector_size; i++)
		{
			if (casos[i] != 1)
			{
				cout << "error en indice long=" << i << endl;
				errores++;
			}
		}
		cout << "=======================\nerrores double totales=" << errores << endl;
	}


//	for (i=0;i<500;i++) printf("%10.0f",vector[i]);

	delete casos;
	cout <<"\n=== FIN ===="<<endl; getchar();getchar();
    return 0;
}

