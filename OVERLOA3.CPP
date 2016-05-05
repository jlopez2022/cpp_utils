class Complex
   {
   double re,im;
   public:
   Complex(double,double);
   inline Complex operator +(Complex &);
   };


Complex::Complex(double x,double y){re=x;im=y;}

inline Complex Complex::operator +(Complex &c2)
   {
   return Complex(re+c2.re,im+c2.im) ;
   }

void main()
{
Complex a=Complex(100,100);
Complex b=Complex(1,3);
Complex c=Complex(0,0);
c=a+b;
}