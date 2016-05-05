#include <stdio.h>
#include <math.h>
#define PIK 40.743665431525205956834243423364 //  128/PI

void main()
{
	//Se pasa de un sistema cartesiano x,y a uno polar r,f (f es el angulo)
	//siendo x,y,f de -127..+128. 
	//r=0..256 y se guarda como char de -127..+128 
	char r[256][256],f[256][256],x[256][256],y[256][256],c;
	int i,j,k;
	double x1=-127.9,y1;
	for(i=0;i<256;i++)
	{
		x1++;y1=-127.9;//empiezo por x1=-127.1
		for(j=0;j<256;j++)
		{
			y1++;//empiezo por -127
			r[i][j]=(char) (sqrt(x1*x1+y1*y1)-127.5);//i=x+127.5
			f[i][j]=(char) (PIK*atan(y1/x1)-0.5);    //j=y+127.5
			if (x1<0)
			{
				if (y1<0) 
				{
					f[i][j]=f[i][j]-127;
				}
				else f[i][j]=128+f[i][j];
			}// OJO: r real es r[][]+127.5
			else if (y1>0) f[i][j]++;

			x[i][j]=((int) ((x1+127.5)*cos(y1/PIK)));//i=r+127.5, r real=r+127 
			y[i][j]=((int) ((x1+127.5)*sin(y1/PIK)));//j=f+127.5
		}
	}

	double error[4],xx;
	for (i=0;i<4;i++) error[i]=0;
	int r2,f2,x2,y2;
	int r3,f3,x3,y3;
	for(i=-89;i<89;i++)
	{
		for(j=-89;j<89;j++)
		{
			r2=r[i+127][j+127];
			f2=f[i+127][j+127];
			x2=x[r2+127][f2+127];xx=0.0+x2-i;error[0]+=xx*xx;
			y2=y[r2+127][f2+127];xx=0.0+y2-j;error[1]+=xx*xx;
			r3=r[x2+127][y2+127];
			f3=f[x2+127][y2+127];
			x3=x[r3+127][f3+127];xx=0.0+x3-i;error[2]+=xx*xx;
			y3=y[r3+127][f3+127];xx=0.0+y3-j;error[3]+=xx*xx;
		}
	}
	k=89*89*4;
	for (i=0;i<4;i++) error[i]=sqrt(error[i])/k;
	for (i=0;i<4;i++) printf("\nError[%i] = %g",i,error[i]);
	printf("\nFin de conversion");
	scanf("%c%c",&c,&c);
}