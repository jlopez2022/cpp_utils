//gcc  -std=c++11 -lstdc++ -o prue define_timing.cpp
//see also #define.cpp file

/*
LINUX AMD 1Ghz:
#define         = 10.06 nanoseconds/operation
function        = 14.28 nanoseconds/operation
inline function = 13.20 nanoseconds/operation

Windows7 Intel 3.5Ghz
Release mode:
#define         = 1.009 nanoseconds/operation
function        = 0.997 nanoseconds/operation
inline function = 1.031 nanoseconds/operation

Debug mode:
#define         = 3.467 nanoseconds/operation
function        = 11.09 nanoseconds/operation
inline function = 11.81 nanoseconds/operation

*/


#include <iostream>
#include <chrono>

using namespace std;

#define INLIMIT2(x,xmin,xmax) ( (x)<(xmin) ? (xmin) : ((x)<(xmax) ? (x) : ((xmax)))) 
double inlimit2(double x, double xmin, double xmax)
{
	if (x < xmin)
		return xmin;
	else if (x >= xmax)
		return xmax;
	return x;
}


inline double inlimit3(double x, double xmin, double xmax)
{
	if (x < xmin)
		return xmin;
	else if (x >= xmax)
		return xmax;
	return x;
}

int main()
{
	const int top=1000000000;
	double *x=new double[top];
	int i;
	for (i = 0; i < top; i++) x[i] = 1.01*i;
	time_t ini, fin;
	double x2 = 0.0;

	cout << "Test using #define:" << endl; x2 = 0.0;
	ini = clock();
	for (i = 0; i < top; i++) x2 += INLIMIT2(x[i], 10.0, 100.0);
	fin = clock();
	cout << "Time/op=" << 1e9 / top*(1.0*fin - ini) / CLOCKS_PER_SEC << " nanoseconds/operation" << endl;
	cout << "Result=" << x2 << endl;

	cout << "Test using function:" << endl; x2 = 0.0;
	ini = clock();
	for (i = 0; i < top; i++) x2 += inlimit2(x[i], 10.0, 100.0);
	fin = clock();
	cout << "Time/op=" << 1e9 / top*(1.0*fin - ini) / CLOCKS_PER_SEC << " nanoseconds/operation" << endl;
	cout << "Result=" << x2 << endl;

	cout << "Test using inline function:" << endl; x2 = 0.0;
	ini = clock();
	for (i = 0; i < top; i++) x2 += inlimit3(x[i], 10.0, 100.0);
	fin = clock();
	cout << "Time/op=" << 1e9 / top*(1.0*fin - ini) / CLOCKS_PER_SEC << " nanoseconds/operation" << endl;
	cout << "Result=" << x2 << endl;

	delete x;
	cout << "=== END ===" << endl; getchar();
	return 1;
}
