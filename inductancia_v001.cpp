//Halla inductancia con un error muy pequeño:
#include <stdio.h>
#include <math.h>
#define PI 3.1415926535897932384626433832795 
#define MU 12.566370614359172953850573533118e-7
#define SIZE 1000 //numero de elementos
//Aplicado a un rectángulo


double distancia(double x1,double y1,double z1,double x2,double y2,double z2)
{
	double d,xx;
	xx=x1-x2;d=xx*xx;
	xx=y1-y2;d+=xx*xx;
	xx=z1-z2;d+=xx*xx;
	d=sqrt(d);
	if (d==0.0) d=1e199;
	return d;
}

double distancia(double x,double y,double z)
{
	double d;
	d= x*x;
	d+=y*y;
	d+=z*z;
	d=sqrt(d);
	return d;
}



int main()
{
	double L=1e-7,S,V;
	double xm=1.0,ym=0.1,zm=0.01;
	double ix,iy,iz;
	double dx,dy,dz,d;
	double nx,ny,nz;
	double inx,iny,inz;
	dx=xm/SIZE;dy=ym/SIZE;dz=zm/SIZE;
	long ii=SIZE;
	nx=2.0*SIZE;inx=0;
	double kk=0.678364;
	for (ix=kk*dx;ix<xm;ix+=dx)
	{
		printf("\n%li",ii);ii-=1;
		ny=SIZE*2.0;iny=0;
		for (iy=kk*dy;iy<ym;iy+=dy)
		{
			nz=SIZE*2.0;inz=0;
			for (iz=kk*dz;iz<zm;iz+=dz)
			{
				d=distancia(ix,iy,iz);
				if (d>0) inz+=nz/d;
				nz-=2;
			}
			iny+=ny*inz;ny-=2;
		}
		inx+=nx*iny;nx-=2;
	}
	double integral=inx;
	S=ym*zm;V=dx*dy*dz;
	L=L*integral/S/S*V*V;
	printf("\nL=%lg",L);getchar();getchar();
	return 1;
}