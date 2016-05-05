#include <stdio.h>
#include <math.h>

class pruc
{
public:
	int r,g,b;
	pruc *sig;
};

double square(double x,double y)
{
	return(x*x+y*y);
}

void main()
{
	int *bitsn,bitmatriz[2050];;
	bitsn=&bitmatriz[1024];bitsn[-1]=1;bitsn[0]=0;bitsn[1]=1;double log2; log2=log(2.0);
	for (int i=2;i<1025;i++)//halla log(2*E/Emin)/log2 
	{bitsn[i]=(int) (log(2.0*i)/log2);bitsn[-i]=bitsn[i];}

	pruc pru[512];
	for (i=0;i<512;i++)
	{
		pru[i].r=i % 256;
		pru[i].g=i % 256;
		pru[i].b=i % 256;
	}

	// 1. con punteros:
	int deltap,x;
	pruc *ptr1,*ptr2;
	ptr1=&pru[10];
	ptr2=&pru[27];
	deltap=ptr2-ptr1;
	x=0;
	for (i=0;i<3;i++)
	{
		x+=bitsn[ptr1->r-(ptr1+deltap)->r];
		x+=bitsn[ptr1->g-(ptr1+deltap)->g];
		x+=bitsn[ptr1->b-(ptr1+deltap)->b];
		ptr1++;
	}
	printf("\nx=%i",x);

	// 2. con matrices:
	int p1,p2;
	p1=10;p2=27;
	deltap=p2-p1;
	x=0;
	for (i=0;i<3;i++)
	{
		x+=bitsn[ pru[p1].r-pru[p1+deltap].r ];
		x+=bitsn[ pru[p1].g-pru[p1+deltap].g ];
		x+=bitsn[ pru[p1].b-pru[p1+deltap].b ];
		p1++;
	}
	printf("\nx=%i",x);
	char c;
	scanf("%c%c",&c,&c);
}