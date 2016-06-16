/*c++ functions modf remainder frexp fdim hypot
c++11 solo
 modf rompe un numero decimal en parte la division en parte entera y fraccional de una sola vez!!
 remainder rounds the int part to nearest of the frac part
 significand= frexp(x,&exponent); obtain significand and exponent in the ecuation: x = significand * 2^exponent . CAUTION: significand between 0 and 1.
fdim(a,b) returns possitive difference of (a-b)
*/

#include <iostream>
#include <math.h>       /* modf */
using namespace std;



int main()
{
	double param, fractpart, intpart;//float aso
	param = 3.9900;
	fractpart = modf(param, &intpart);
	cout << "modf: \n param=" << param << " int part=" << intpart << " frac part=" << fractpart << endl;
	fractpart = remainder(param, 1.0);
	cout << "remainder: \n param=" << param << "=" << fractpart << endl;

	int n;
	double significand, x = 0.933*8.0;
	significand = frexp(x, &n);
	cout << "frexp:\n x=0.933*8=" << x << " =" << significand << " *2 to " << n << endl;

	double a = 10.33, b = 10.0;
	cout << "fdim:\n a=" << a << " b=" << b << " fdim(a,b)=" << fdim(a, b) << " fdim(b,a)=" << fdim(b, a) << endl;

	cout << "hypot:\n a=" << a << " b=" << b << " hypot(a,b)=" << hypot(a, b) << endl;


	cout << "=== FIN ===" << endl; getchar(); getchar();
	return 1;
}