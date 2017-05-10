//Test of const in finction parameter
#include <iostream>

#pragma warning(disable:4996) 
typedef unsigned char uchar;
using namespace std;

void f(const int &);
void f2(const int *);
void f3(const char *);
void fun1(const double a[], const double b[], double c[], long num);



void main()
{
	int i = 10;
	f(i);
	i = 3;

	double a[100], b[100], c[100];

	for (long i = 0; i < 100; i++)
	{
		a[i] = 100000 * (i + 1);
		b[i] = 10.0*i;
	}
	fun1(a, b, c, 100L);
	cout << endl << endl << "=== end ===" << endl; getchar();
}



void f(const int &i)
{
	int j;
	j = i;
	// i=7000;  error
}


void f2(const int *i)
{
	int j;
	j = *i;
	// *i=7000;    error const.
}

void f3(const char *c)
{
	char c1;
	c1 = *c;
	//*c=0;
}

void fun1(const double a[], const double b[], double c[], long num)
{
	for (; num >= 0; --num)
	{
		c[num] = a[num] + b[num];
	}
	//a[1] = 7;  // wrong!!
}