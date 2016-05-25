#include <stdlib.h>	 //rand()
#include <iostream>  //cin,cout
#include <algorithm> //sort


using namespace std;

const int SIZE = 200;

// decreciente: > creciente: < 
bool wayToSort(int i, int j) { return i > j; }
double *dato_d;
bool ordenalista(int i, int j) { return dato_d[i] > dato_d[j]; }

int main()
{
    int intArray[SIZE];
	double data[SIZE];

	long i;
	for (i=0;i<SIZE;i++)
	{
		intArray[i]=rand()%256-128;
		data[i]=7000.0*((rand() % 256)-128);
	}

    //Now we call the sort function
    sort(intArray, intArray + SIZE);

	cout << "\n1. Enteros ordenados creciendo:" << endl;
	long errores;
	int iant=-10000;errores=0;
    for (i = 0; i != SIZE; ++i)
	{
        cout << intArray[i] << " ";
		if (intArray[i]<iant) 
		{
			cout << "ERROR\n";errores++;
		}
		iant=intArray[i];
	}
	cout <<"\n=== FIN: errores="<<errores<<endl;

	cout << "\n2. Double ordenados creciendo:" << endl;
    sort(data, data + SIZE);
	errores=0;
	double dant=-1e133;
    for (i = 0; i != SIZE; ++i)
	{
        cout << data[i] << " ";
		if (data[i]<dant) 
		{
			cout << "ERROR\n";errores++;
		}
		dant=data[i];
	}
	cout <<"\n=== FIN: errores="<<errores<<endl;

	cout << "\n3. Enteros ordenados decreciendo:" << endl;
 	for (i=0;i<SIZE;i++)
		intArray[i]=rand()%256-128;
	sort(intArray, intArray + SIZE, wayToSort);
	iant=10000;errores=0;
    for (i = 0; i != SIZE; ++i)
	{
        cout << intArray[i] << " ";
		if (intArray[i]>iant) 
		{
			cout << "ERROR\n";errores++;
		}
		iant=intArray[i];
	}
	cout <<"\n=== FIN: errores="<<errores<<endl;

	cout << "\n4. Lista Double ordenados decreciendo:" << endl;
	for (i=0;i<SIZE;i++)
		data[i]=7000.0*((rand() % 256)-128);
	//Ordeno:
	int lista[SIZE];for (i=0;i<SIZE;i++) lista[i]=i;
	dato_d=data;
    sort(lista, lista + SIZE,ordenalista);

	errores=0; dant=1e133;
    for (i = 0; i != SIZE; ++i)
	{
        cout << data[lista[i]] << " ";
		if (data[lista[i]]>dant) 
		{
			cout << "ERROR\n";errores++;
		}
		dant=data[lista[i]];
	}
	cout <<"\n=== FIN: errores="<<errores<<endl;
	


	getchar();getchar();
    return 0;
}