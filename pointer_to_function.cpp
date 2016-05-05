#include <stdio.h>

double f1(double x,double y)
{
	return(x*y);
}

double f2(double x,double y)
{
	return(x+y);
}

double f3(double x,double y)
{
	return(x+100);
}

void main()
{
	typedef double (*FUNCT)(double,double);
	FUNCT fun[]={f1,f2,f3};
	FUNCT funx;
	double x;

	x=(*fun[0])(10,20);printf("\nFun1=%g",x);
	x=(*fun[1])(10,20);printf("\nFun1=%g",x);
	x=(*fun[2])(10,20);printf("\nFun1=%g",x);
	funx=f1;
	x=(*funx)(10,20);printf("\nFun1=%g",x);
	char c;
	scanf("%c%c",&c,&c);
}