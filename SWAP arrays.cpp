#include <iostream>

using namespace std;


void main()
{
	double *a = new double[7];
	double *b = new double[7];
	long i;
	for (i = 0; i < 7; i++)
	{
		a[i] = i + 100;
		b[i] = i + 300;
	}

	double **ptr1 = &a,**ptr2=&b,**ptrx;
	cout << "\nSTEP 1: a= ";
	for (i = 0; i < 7; i++) cout << (*ptr1)[i] << " ";
	cout << " b= ";
	for (i = 0; i < 7; i++) cout << (*ptr2)[i] << " ";

	ptrx = ptr1; ptr1 = ptr2; ptr2 = ptrx;
	cout << "\nSTEP 2: b= ";
	for (i = 0; i < 7; i++) cout << (*ptr1)[i] << " ";
	cout << " b= ";
	for (i = 0; i < 7; i++) cout << (*ptr2)[i] << " ";

	ptrx = ptr1; ptr1 = ptr2; ptr2 = ptrx;
	cout << "\nSTEP 3: a= ";
	for (i = 0; i < 7; i++) cout << (*ptr1)[i] << " ";
	cout << " b= ";
	for (i = 0; i < 7; i++) cout << (*ptr2)[i] << " ";

	ptrx = ptr1; ptr1 = ptr2; ptr2 = ptrx;
	cout << "\nSTEP 4: a= ";
	for (i = 0; i < 7; i++) cout << (*ptr1)[i] << " ";
	cout << " b= ";
	for (i = 0; i < 7; i++) cout << (*ptr2)[i] << " ";

	cout << "\n\n======end========\n"; getchar(); getchar();
}

