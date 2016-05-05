#include <stdio.h>
#include <math.h>
#define PIK 40.743665431525205956834243423364 //  128/PI

void main()
{
	//Se pasa de un sistema cartesiano x,y a uno polar r,f (f es el angulo)
	//siendo x,y,f de -127..+128. 
	//r=0..256 y se guarda como char de -127..+128 
	char rm[257][256],fm[257][256],xm[257][256],ym[257][256],c;
	char (*r)[256]   ,(*f)[256]   ,(*x)[256]   ,(*y)[256];
        r=&rm[128];   f=&fm[128];  x=&xm[128];  y=&ym[128];    
	int i,j,k;
	for(i=-127;i<+127;i++)
	{
		for(j=-127;j<+127;j++)
		{
			/*if ((i==-89) && (j==-89))
				c=0;*/
			r[i][j]=(char) (-127.5+sqrt(i*i+j*j));//r real = r+127
			f[i][j]=(char) (PIK*atan(j/(i+1e-80))-0.5);    
			if (i<0)
			{
				if (j<0) 
				{
					f[i][j]=f[i][j]-127;
				}
				else f[i][j]=128+f[i][j];
			}// OJO: r real es r[][]+127.5
			else if (j>0) f[i][j]++;

			x[i][j]=((int) ((127.5+i)*cos(j/PIK)));
			y[i][j]=((int) ((127.5+i)*sin(j/PIK)));
			//x[r[i][j]][f[i][j]]=i;
			//y[r[i][j]][f[i][j]]=j;
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
			r2=r[i][j];
			f2=f[i][j];
			x2=x[r2][f2];xx=0.0+x2-i;error[0]+=xx*xx;
			y2=y[r2][f2];xx=0.0+y2-j;error[1]+=xx*xx;
			r3=r[x2][y2];
			f3=f[x2][y2];
			x3=x[r3][f3];xx=0.0+x3-i;error[2]+=xx*xx;
			y3=y[r3][f3];xx=0.0+y3-j;error[3]+=xx*xx;
			if ((error[0]+error[1]+error[2]+error[3])>0)
				xx=1;
		}
	}
	k=89*89*4;
	for (i=0;i<4;i++) error[i]=sqrt(error[i])/k;
	for (i=0;i<4;i++) printf("\nError[%i] = %g",i,error[i]);
	printf("\nFin de conversion");
	scanf("%c%c",&c,&c);
}