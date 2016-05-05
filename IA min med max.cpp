#include <stdio.h>
#include <math.h>


double fmmm0(double x,double min,double med,double max);//exp
double fmmm1(double x,double min,double med,double max);//if-1
double fmmm2(double x,double xx[4],double yy[4]);//if-2

int main()
{
	double x;
	for (x=0.0;x<=1.01;x+=0.05)
	{
		double y0,y1,y2;
		y0=fmmm0(x,10,32.5,100);
		y1=fmmm1(x,10,32.5,100);
		double xx[4]={0,0.9,0.9,1.0};
		double yy[4]={10,50,50,100};
		y2=fmmm2(x,xx,yy);
		printf("%3lf\t%lf\t%lf\t%lf\n",x,y0,y1,y2);
	}
		printf("\nFIN\n");getchar();getchar();
	return 1;
}

double fmmm0(double x,double min,double med,double max)//exp
{
	double ex,y;
	ex=log(1e-99+fabs((med-min)/(max-min+1e-99)))/log(0.5);

	y=min+(max-min)*pow(x,ex);
	return y;
}

double fmmm1(double x,double min,double med,double max)//if-1
{
	if (x<0.5)
		return min+(med-min)*2.0*x;
	else
		return med+(max-med)*(2.0*x-1.0);
}

double fmmm2(double x,double xx[4],double yy[4])//if-2
{
	if (x<xx[1])
		return (x-xx[0])/(xx[1]-xx[0])*(yy[1]-yy[0]+1.0e-199) + yy[0];
	else if (x<xx[2])
		return (x-xx[1])/(xx[2]-xx[1])*(yy[2]-yy[1]+1.0e-199) + yy[1];
	else
		return (x-xx[2])/(xx[3]-xx[2])*(yy[3]-yy[2]+1.0e-199) + yy[2];
}

