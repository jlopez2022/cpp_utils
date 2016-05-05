#include <stdio.h>


class Complex
{
public:
   Complex( double re, double im ){real=re;imag=im;};
   Complex operator+( Complex &other );
   friend Complex operator+( int first, Complex &second );
private:
   double real, imag;
};

// Operator overloaded using a member function
Complex Complex::operator+( Complex &other )
{
return Complex( real + other.real, imag + other.imag );
};

// Operator overloaded using a friend function
Complex operator+( int first, Complex &second )
{
return Complex( first + second.real, second.imag );
}
  

void main()
{
/*
Complex *a,*b,*c;
a=new Complex(10.,11.);
b=new Complex(20.,22.);
c=new Complex(50.,55.);

*c=*a+*b;
*/

Complex a(10.,11.);
Complex b(20.,21.);
Complex c(50.,51.);
c=a+b;
}
