#include <stdio.h>
#include <iostream>
using namespace std;//#include <utility>
//std::swap(matriz1m, matriz2m); //Solo en VC11 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#define MAX1 9
#define MAX2 8
#define SWAP(t,a,b) ( (t) = (a), (a) = (b), (b) = (t) ) 


void intercambia_matrices(float **matriz1,float **matriz2,int max1);
void intercambia_matrices2(float **matriz1,float **matriz2,int max1);
//paso de matriz bidimensional:
void imprime_matriz2d(float **matriz,int max2,int max1);
//idem indicando solo el segundo indice:
void imprime_matriz2d(float *matriz[MAX2],int max1);

int main()
{
	float *matriz1_m=new float[MAX1*MAX2];
	float *matriz2_m=new float[MAX1*MAX2];
	float *matriz1m[MAX1];
	float *matriz2m[MAX1];
	long i,j;
	for (i=0;i<MAX2;i++)//asi ocupa menos!!!
	{
		matriz1m[i]=&matriz1_m[MAX1*i];
		matriz2m[i]=&matriz2_m[MAX1*i];
	}
	//SIN emplear for:!!!!!!!!!!!!!!!!!!!!!!!!!!
	float *matriz3_m=new float[MAX1*MAX2];
	float (*matriz3m)[MAX1]=(float (*)[MAX1]) &matriz3_m[0];
	
	for (i=0;i<MAX2;i++)
	{
		for(j=0;j<MAX1;j++)
		{
			matriz1m[i][j]=100.0f*(i+1)+j;
			matriz2m[i][j]=200.0f*(i+1)+j;
		}
	}

	//std::swap(matriz1m, matriz2m); //Solo en VC11 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	imprime_matriz2d(matriz1m,MAX2,MAX1);
	imprime_matriz2d(matriz2m,MAX2,MAX1);
	intercambia_matrices(matriz1m,matriz2m,MAX2);
	imprime_matriz2d(matriz1m,MAX2,MAX1);
	imprime_matriz2d(matriz2m,MAX2,MAX1);
	i++;
	intercambia_matrices(matriz1m,matriz2m,MAX2);
	i++;
	intercambia_matrices2(matriz1m,matriz2m,MAX2);
	i++;
	intercambia_matrices2(matriz1m,matriz2m,MAX2);
	i++;

	//Compruebo tamaño
	printf("\nSize of matriz1m:");
	printf("\nsizeof 1D  =%li",sizeof(matriz1_m));
	printf("\nsizeof 2D  =%li",sizeof(matriz1m));
	long calc=sizeof(float)*MAX1*MAX2;
	printf("\ncalculated =%li",calc);
	calc= (sizeof(float) + (long) (&matriz1m[MAX2-1][MAX1-1]) ) - (long) &matriz1m[0][0];
	printf("\nsize real  =%li",calc);

	printf("\n\nSize of matriz3m:");
	calc= (sizeof(float) + (long) (&matriz3m[MAX2-1][MAX1-1]) ) - (long) &matriz3m[0][0];
	printf("\nsize real  =%li",calc);

	float matriz4m[MAX2][MAX1];
	printf("\n\nSize of matriz4m:");
	calc= (sizeof(float) + (long) (&matriz4m[MAX2-1][MAX1-1]) ) - (long) &matriz4m[0][0];
	printf("\nsize real  =%li",calc);


	//Tal como se crearon se borran del tiron:
	delete matriz1_m;
	delete matriz2_m;
	delete matriz3_m;matriz3m=NULL;//Muerte total :) !!!!!!!!!!!!!
	printf("\n\n===FIN===");getchar();getchar();
	return 1;
}

void intercambia_matrices(float **matriz1,float **matriz2,int max1)
{
	float *temp;
	int i;
	for (i=0;i<max1;i++)
	{
		temp=matriz1[i];
		matriz1[i]=matriz2[i];
		matriz2[i]=temp;
	}
}

void intercambia_matrices2(float **matriz1,float **matriz2,int max1)
{
	float *temp;
	int i;
	for (i=0;i<max1;i++)
		SWAP(temp,matriz1[i],matriz2[i]);
}

//Prueba de paso de matriz 2d
void imprime_matriz2d(float *matriz[MAX2],int max1)
{
	cout<<"==============================================================================\n";
	long i,j;
	for (i=0;i<MAX2;i++)
	{
		for (j=0;j<max1;j++)
		{
			cout << matriz[i][j] <<'\t';
		}
		cout <<endl;
	}
	cout<<"==============================================================================\n";
}

void imprime_matriz2d(float **matriz,int max2,int max1)
{
	cout<<"==============================================================================\n";
	long i,j;
	for (i=0;i<max2;i++)
	{
		for (j=0;j<max1;j++)
		{
			cout << matriz[i][j] <<'\t';
		}
		cout <<endl;
	}
	cout<<"==============================================================================\n";
}

