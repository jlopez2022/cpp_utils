#include <stdio.h>
#include <iostream>

#define SWAP(t,a,b) ( (t) = (a), (a) = (b), (b) = (t) )
using namespace std;

int main()
{
	double dtemp, d1 = 11.1e222, d2 = 22.2e109;
	cout << "d1 d2 double before: " << d1 << " " << d2 << endl;
	SWAP(dtemp, d1, d2);
	cout << "d1 d2 double after:  " << d1 << " " << d2 << endl;

	float ftemp, f1 = 1.11111e6f, f2 = 2.22222e29f;
	cout << "f1 f2 float  before: " << f1 << " " << f2 << endl;
	SWAP(ftemp, f1, f2);
	cout << "f1 f2 float  after:  " << f1 << " " << f2 << endl;

	int itemp, i1 = 3113, i2 = 3939;
	cout << "i1 i2 int    before: " << i1 << " " << i2 << endl;
	SWAP(itemp, i1, i2);
	cout << "i1 i2 int    after:  " << i1 << " " << i2 << endl;

	long ltemp, l1 = 10001220L, l2 = 99999999L;
	cout << "l1 l2 long   before: " << l1 << " " << l2 << endl;
	SWAP(ltemp, l1, l2);
	cout << "l1 l2 long   after:  " << l1 << " " << l2 << endl;


	long ii; 
	ii = sizeof(double);
	cout << "double: " << ii << endl;
	ii = sizeof(long double);
	cout << "long double: " << ii << endl;

	getchar(); getchar();
}