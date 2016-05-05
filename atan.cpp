#include <stdio.h>
#include <math.h>

const double PI(3.1415926535897932384626433832795);
const double rad2deg(180.0 / PI);

double arcotangente(double x,double y)
{
	double r;
	r=atan(y/(1.0e-299+x));
	if (x<0)
		r=PI+r;
	return r;
}


int main()
{
	double x,y,x2,y2,r,error,d;

	printf("x\ty\tx2\ty2\terror\n");

	x=1.0;y=0.5;r=arcotangente(x,y);
	d=sqrt(x*x+y*y);x2=d*cos(r);y2=d*sin(r);
	error=fabs(x-x2)+fabs(y-y2);
	printf("%lg\t%lg\t%lg\t%lg\t%lg\t\n",x,y,x2,y2,error);

	x=-1.0;y=0.5;r=arcotangente(x,y);
	d=sqrt(x*x+y*y);x2=d*cos(r);y2=d*sin(r);
	error=fabs(x-x2)+fabs(y-y2);
	printf("%lg\t%lg\t%lg\t%lg\t%lg\t\n",x,y,x2,y2,error);

	x=1.0;y=-0.5;r=arcotangente(x,y);
	d=sqrt(x*x+y*y);x2=d*cos(r);y2=d*sin(r);
	error=fabs(x-x2)+fabs(y-y2);
	printf("%lg\t%lg\t%lg\t%lg\t%lg\t\n",x,y,x2,y2,error);

	x=-1.0;y=-0.5;r=arcotangente(x,y);
	d=sqrt(x*x+y*y);x2=d*cos(r);y2=d*sin(r);
	error=fabs(x-x2)+fabs(y-y2);
	printf("%lg\t%lg\t%lg\t%lg\t%lg\t\n",x,y,x2,y2,error);

	printf("\nFIN");getchar();getchar();
	return 1;
}