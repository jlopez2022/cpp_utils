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

	cout << "\nArrays before:     a= ";
	for (i = 0; i < 7; i++) cout << a[i] << " ";
	cout << " b= ";
	for (i = 0; i < 7; i++) cout << b[i] << " ";

	cout << "\nArrays after swap: a= ";
	double *ptrx=a;a=b;b=ptrx;//swap allowed only with pointers
	for (i = 0; i < 7; i++) cout << a[i] << " ";
	cout << " b= ";
	for (i = 0; i < 7; i++) cout << b[i] << " ";


	int c[3]={100,101,102};
	int d[3]={200,201,202};
	//Not works: int *x1=&c[0];c=d;d=x1;
	cout << "\nArrays before:     c= ";	for (i = 0; i < 3; i++) cout << c[i] << " ";
	cout << " d= ";						for (i = 0; i < 3; i++) cout << d[i] << " ";
	int *c1=c,*d1=d,*x1;//pointers are needed.
	x1=c1;c1=d1;d1=x1;//swap using pointers only
	cout << "\nArrays after swap: c= ";	for (i = 0; i < 3; i++) cout << c1[i] << " ";
	cout << " d= ";						for (i = 0; i < 3; i++) cout << d1[i] << " ";


	cout << "\n\n======end========\n"; getchar(); 
	delete a;
	delete b;
}

