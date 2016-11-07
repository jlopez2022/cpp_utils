#include <iostream>

using namespace std;

double *a;
double *b;

class c_class { public: double x; } ;


void main()
{
	//1. Initialize of the array:
	a = new double[7];
	b = new double[7];
	long i;
	for (i = 0; i < 7; i++)
	{
		a[i] = i + 100;
		b[i] = i + 300;
	}

	//2. We need three pointers:
	double **ptr1 = &a,**ptr2=&b,**ptrx;

	//3. Printing initial array values:
	cout << "=== SWAPPING ARRAYS ===" << endl;
	cout << "STEP 1: ptr1= " << endl;
	for (i = 0; i < 7; i++) cout << (*ptr1)[i] << " ";
	cout << " ptr2= ";
	for (i = 0; i < 7; i++) cout << (*ptr2)[i] << " ";
	cout << endl;

	//4. Swapping the arrays in only 3 pointer operations:
	cout << " Swapping the arrays" << endl;
	ptrx = ptr1; ptr1 = ptr2; ptr2 = ptrx;
	//5. Printing the arrays after swapping:
	cout << "STEP 2: ptr1= ";
	for (i = 0; i < 7; i++) cout << (*ptr1)[i] << " ";
	cout << " ptr2= ";
	for (i = 0; i < 7; i++) cout << (*ptr2)[i] << " ";
	cout << endl;

	//6. Swapping again the arrays in only 3 pointer operations:
	cout << " Swapping the arrays" << endl;
	ptrx = ptr1; ptr1 = ptr2; ptr2 = ptrx;
	//7. Printing the arrays after swapping: results must be the same than initial ones:
	cout << "STEP 3: ptr1= ";
	for (i = 0; i < 7; i++) cout << (*ptr1)[i] << " ";
	cout << " ptr2= ";
	for (i = 0; i < 7; i++) cout << (*ptr2)[i] << " ";
	cout << endl;

	cout << "\n\n=== SWAPPING CLASSES ==="<<endl;
	c_class clas1, clas2;
	clas1.x = 1000.1;
	clas2.x = 5000.5;
	//10. Declaration of the pointers:
	c_class *pc1, *pc2,*pcx;
	//11. Initial value of the pointers:
	pc1 = &clas1; pc2 = &clas2;
	//12. Printing initial classes values:
	cout << "Class 1 and 2 x value: " << pc1->x << " "<<pc2->x<<endl;
	//13. Swapping the classes in only 3 steps:
	cout << " Swapping the classes " << endl;
	pcx = pc1; pc1 = pc2; pc2 = pcx;
	cout << "Class 1 and 2 x value: " << pc1->x << " " << pc2->x << endl;


	cout << "\n\n======end========\n"; getchar(); getchar();
}

