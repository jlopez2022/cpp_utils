#define VS2008
#ifdef VS2008
	#include "stdafx.h"
#else 
	#include <stdio.h>
#endif

#include <math.h>
#define PI 3.1415926535897932384626433832795
#define N 10000 //number of iteractions

//10.0 === Functions ===================
//Calculates multilayer coil inductance C=layers T=turns in one layer, D=inner diameter
//t=sheet thick t2=separation between layers, . Note:t2=t+d, d=dielectric thick
double Multilayer_L(double Length,long C,long T,double D,double t,double t2);
//Spiral long T=turns, D=inner diameter t=sheet thick t2=separation between layers, . Note:t2=t+d, d=dielectric thick
double Spiral_Long_L(double Length,long T,double D,double t,double t2); 
//Calculus of magnetic field due a current loop at any point in x direction
//a=loop radius,x,y=distance from center of the loop to the point of interest.
//Loop is in the yz plane
double Bxcalc(double a,double x,double y,double current);
//Calculus of magnetic field due a current loop at any point in r direction
//a=loop radius,x,y=distance from center of the loop to the point of interest.
//Loop is in the yz plane
double Brcalc(double a,double x,double y,double current);
/*
Inductance of a solenoid by Maxwell’s method,using elliptic integrals
n=turns, h=length,r=radius,b=0,d=wire diameter
*/
double Maxwell_L(int n,double h,double r,double b,double d);

//11.0 === Auxiliar Functions ==========
/*
Complete elliptic integrals of first and second classes - AGM method.
Doesn’t require more than 7 iterations for c between 0 and 0.9999999999.
Reference: Pi and the AGM, J. Borwein and P. Borwein, John Wiley & Sons.
*/
void K_E_calc(double c,double &Kk,double &Ek);
//Mutual inductance between coaxial coils radius r1,r2 at a distance d between them
double M12calc(double r1,double r2,double d);

//12.0 === Other functions =============
//Complete elliptic integral of the 1st kind K(k)
double Kcalc(double k);//-1<=k<=1   IS BETTER using K_E_calc()
//Complete elliptic integral of the 2nd kind E(k)
double Ecalc(double k);//-1<=k<=1	IS BETTER using K_E_calc()
//Calculus when point of interest is on axis
//a=loop radius,x=distance from center of the loop to the point of interest.y=0
//Loop is in the yz plane
double Bxcalc(double a,double x,double current);






int main() 
{
	{
		//=== 20.0 Check of the elliptic integral, second order:
		double k=0.3,K1,Kweb,error;
		double Ek,Kk;
		printf("\n======= Check of the elliptic integral, second order ========");
		k=0.3  ;K1=Kcalc(k);Kweb=1.608048619930512801267;error=fabs(Kweb-K1);printf("\nK(%lg)=%lg teor=%lg error=%.2lg",k,K1,Kweb,error);
		k=0.7  ;K1=Kcalc(k);Kweb=1.845693998374723517587;error=fabs(Kweb-K1);printf("\nK(%lg)=%lg teor=%lg error=%.2lg",k,K1,Kweb,error);
		k=-0.4 ;K1=Kcalc(k);Kweb=1.639999865864511206865;error=fabs(Kweb-K1);printf("\nK(%lg)=%lg teor=%lg error=%.2lg",k,K1,Kweb,error);
		k=0    ;K1=Kcalc(k);Kweb=1.5707963267948966192313216916398;error=fabs(Kweb-K1);printf("\nK(%lg)=%lg teor=%lg error=%.2lg",k,K1,Kweb,error);
		k= 1.0 ;K1=Kcalc(k);Kweb=1e300;error=fabs(Kweb-K1);printf("\nK(%lg)=%lg teor=%lg error=%lg",k,K1,Kweb,error);

		//=== 21.0 Check of the elliptic integral, first order:
		printf("\n======= Check of the elliptic integral, first order ========");
		k= 1.0 ;K1=Ecalc(k);Kweb=1.0;error=fabs(Kweb-K1);printf("\nE(%lg)=%lg teor=%lg error=%lg",k,K1,Kweb,error);
		k=0.3  ;K1=Ecalc(k);Kweb=1.534833464923249041645;error=fabs(Kweb-K1);error=fabs(Kweb-K1);printf("\nE(%lg)=%lg teor=%lg error=%lg",k,K1,Kweb,error);
		k=0.7  ;K1=Ecalc(k);Kweb=1.355661135571955464315;error=fabs(Kweb-K1);printf("\nE(%lg)=%lg teor=%lg error=%.2lg",k,K1,Kweb,error);
		k=-0.4 ;K1=Ecalc(k);Kweb=1.505941612360040352112;error=fabs(Kweb-K1);printf("\nE(%lg)=%lg teor=%lg error=%.2lg",k,K1,Kweb,error);
		k=0    ;K1=Ecalc(k);Kweb=1.5707963267948966192313216916398;error=fabs(Kweb-K1);printf("\nE(%lg)=%lg teor=%lg error=%.2lg",k,K1,Kweb,error);

		//=== 22.0 Check using AGM method
		printf("\n======= Check of the elliptic integral, first and second order using AGM method========");
		k=0.3;
		K_E_calc(k,Kk,Ek);//printf("\nEk=%lg Fk=%lg",Ek,Fk);
		K1=Kcalc(k);error=fabs(Kk-K1);printf("\nK(%lg)=%lg AGM=%lg error=%.2lg",k,K1,Kk,error);
		K1=Ecalc(k);error=fabs(Ek-K1);printf("\nE(%lg)=%lg AGM=%lg error=%.2lg",k,K1,Ek,error);
		k=0.7;
		K_E_calc(k,Kk,Ek);//printf("\nEk=%lg Fk=%lg",Ek,Fk);
		K1=Kcalc(k);error=fabs(Kk-K1);printf("\nK(%lg)=%lg AGM=%lg error=%.2lg",k,K1,Kk,error);
		K1=Ecalc(k);error=fabs(Ek-K1);printf("\nE(%lg)=%lg AGM=%lg error=%.2lg",k,K1,Ek,error);
	}

	{	//=== 24.0 Check of the Bx magnetic field formula (partial, on axis only)
		double Baxis,Bx,a,x,y=0.0,I=1.0,error;printf("\n======= Check of the Bx magnetic field formula ON axis========");
		a=0.1;x=0.00 ;Bx=Bxcalc(a,x,y,I);Baxis=Bxcalc(a,x,I);error=fabs(Bx-Baxis);printf("\na,x=%lg %lg\t Bx=%lg\t Baxis=%lg\t error=%.2lg",a,x,Bx,Baxis,error);
		a=0.1;x=0.05 ;Bx=Bxcalc(a,x,y,I);Baxis=Bxcalc(a,x,I);error=fabs(Bx-Baxis);printf("\na,x=%lg %lg\t Bx=%lg\t Baxis=%lg\t error=%.2lg",a,x,Bx,Baxis,error);
		a=0.1;x=0.025;Bx=Bxcalc(a,x,y,I);Baxis=Bxcalc(a,x,I);error=fabs(Bx-Baxis);printf("\na,x=%lg %lg\t Bx=%lg\t Baxis=%lg\t error=%.2lg",a,x,Bx,Baxis,error);
	}
	{	//=== 25.0 Check of the Bx magnetic field formula (off axis)
		double Bxweb,Brweb,Bx,Br,a,x,y=0.0,I=1.0,errx,errr;printf("\n======= Check of the Bx magnetic field formula OFF axis ========");
		a=0.1;x=0.04; y=0.02  ;Bx=Bxcalc(a,x,y,I);Br=Brcalc(a,x,y,I);Bxweb=0.0000051531655243364406;Brweb=0.000001444738742769228; errx=fabs(Bx-Bxweb);errr=fabs(Br-Brweb);printf("\na,x=%lg %lg\tBx=%.4lg\t Bweb=%.4lg\t error=%.4lg",a,x,Bx,Bxweb,errx);printf("\n\t\tBr=%.4lg\t Bweb=%.4lg\t error=%.4lg",Br,Brweb,errr);
		a=0.1;x=0.05; y=0.03  ;Bx=Bxcalc(a,x,y,I);Br=Brcalc(a,x,y,I);Bxweb=0.000004199996982982701; Brweb=0.0000019858710535584647;errx=fabs(Bx-Bxweb);errr=fabs(Br-Brweb);printf("\na,x=%lg %lg\tBx=%.4lg\t Bweb=%.4lg\t error=%.4lg",a,x,Bx,Bxweb,errx);printf("\n\t\tBr=%.4lg\t Bweb=%.4lg\t error=%.4lg",Br,Brweb,errr);
		a=0.1;x=0.025; y=0.04 ;Bx=Bxcalc(a,x,y,I);Br=Brcalc(a,x,y,I);Bxweb=0.0000064004584862657536;Brweb=0.0000013712851763575188;errx=fabs(Bx-Bxweb);errr=fabs(Br-Brweb);printf("\na,x=%lg %lg\tBx=%.4lg\t Bweb=%.4lg\t error=%.4lg",a,x,Bx,Bxweb,errx);printf("\n\t\tBr=%.4lg\t Bweb=%.4lg\t error=%.4lg",Br,Brweb,errr);
	}
	{	//=== 26.0 Check the Maxwell inductance
		printf("\n======= Check the Maxwell inductance ========");
		int n=12;double length=0.12,coil_r=0.1,wire_r=1e-3,L,Lweb,error;
		n=12;length=0.15; coil_r=0.1; wire_r=1e-3;L=Maxwell_L(n,length,coil_r,0,wire_r);Lweb=0.0261554312e-3;error=fabs(Lweb-L);printf("\nL=%lg teor=%lg error=%.2lg",L,Lweb,error);
		n=6 ;length=12e-3;coil_r=3e-3;wire_r=1e-3;L=Maxwell_L(n,length,coil_r,0,wire_r);Lweb=0.0000852880e-3;error=fabs(Lweb-L);printf("\nL=%lg teor=%lg error=%.2lg",L,Lweb,error);
		n=14;length=32e-3;coil_r=4e-3;wire_r=2e-3;L=Maxwell_L(n,length,coil_r,0,wire_r);Lweb=0.0003102485e-3;error=fabs(Lweb-L);printf("\nL=%lg teor=%lg error=%.2lg",L,Lweb,error);
	}

	printf("\n==========END=============   ");getchar();
	return 0;
}



//10.0 === Functions ===================
//Calculates multilayer coil inductance L=length, C=layers T=turns in one layer, D=inner diameter
//t=wire diameter t2=separation between layers, . Note:t2=t+d, d=dielectric thick
//round with maximum packaging t2=t1*0.866
double Multilayer_L(double Length,long C,long T,double D,double t,double t2)
{
	long Jmax=C, Imax=T,  i1,j1,i2,j2;
	double L=0.0, RM;
	RM=t/2*exp(-0.25); //{g. m. d.}
	double z1,z2,r1,r2;
	for (i1=0;i1<Imax;i1++)
	{
		r1=0.5*(D + t) +t2*i1; 
		for (j1=0;j1<Jmax;j1++)
		{
			z1=j1*Length/Jmax;
			for (i2=i1;i2<Imax;i2++)
			{
				r2=0.5*(D + t) +t2*i2; 
				for (j2=0;j2<Jmax;j2++)
				{
					z2=j2*Length/Jmax;
				}
			}
		}
		double d=(z2-z1-RM);
		double m; m= M12calc(r1,r2,d);
		if ((i1!=i2)||(j1!=j2)) 
			m=2*m;
		L+=m;
	}
	return L;
}

//Calculates inductance of a Spiral long coil, see document Spiral long coil.doc
//T=turns, D=inner diameter t=sheet thick t2=separation between layers, . Note:t2=t+d, d=dielectric thick
double Spiral_Long_L(double Length,long T,double D,double t,double t2)
{
	long Jmax=(long) (0.5+Length/t), Imax=T,i1,j1,i2,j2;
	double L=0.0;
	double z1,z2,r1,r2;
	for (i1=0;i1<Imax;i1++)
	{
		r1=0.5*(D + t) +t2*i1; 
		for (j1=0;j1<Jmax;j1++)
		{
			z1=j1*t;
			for (i2=i1;i2<Imax;i2++)
			{
				r2=0.5*(D + t) +t2*i2; 
				for (j2=0;j2<Jmax;j2++)
				{
					z2=j2*t;
				}
			}
		}
		double d=(z2-z1);
		double m; m= M12calc(r1,r2,d);
		if ((i1!=i2)||(j1!=j2)) 
			m=2*m;
		L+=m;
	}
	L=1.0*L/Jmax;return L;
}

//Calculus of magnetic field due a current loop at any point in x direction
//a=loop radius,x,y=distance from center of the loop to the point of interest.
//Loop is in the yz plane
double Bxcalc(double a,double x,double y,double current)
{
	double B0,a1,b1,g1,Q,k,r,B;
	r=sqrt(y*y+x*x);
	B0=4e-7*PI*current/2.0/a;
	a1=r/a;b1=x/a;g1=x/r;//alphs, beta and gamma
	Q=(1.0+a1)*(1.0+a1)+b1*b1;
	k=sqrt(4*a1/Q);
	B=B0/PI/sqrt(Q)*( Ecalc(k)*(1-a1*a1-b1*b1)/(Q-4*a1)+Kcalc(k) );
	return B;
}
//Calculus of magnetic field due a current loop at any point in r direction
//a=loop radius,x,y=distance from center of the loop to the point of interest.
//Loop is in the yz plane
double Brcalc(double a,double x,double y,double current)
{
	double B0,a1,b1,g1,Q,k,r,B;
	r=sqrt(y*y+x*x);
	B0=4e-7*PI*current/2.0/a;
	a1=r/a;b1=x/a;g1=x/r;//alphs, beta and gamma
	Q=(1.0+a1)*(1.0+a1)+b1*b1;
	k=sqrt(4*a1/Q);
	B=B0*g1/PI/sqrt(Q)*( Ecalc(k)*(1+a1*a1+b1*b1)/(Q-4*a1)-Kcalc(k) );
	return B;
}
/*
Inductance of a solenoid by Maxwell’s method,using elliptic integrals
n=turns, h=length,r=radius,b=0,d=wire diameter
*/
double Maxwell_L(int n,double h,double r,double b,double d)
{
	double a1,c,b1b2,RM,z1,z2,z10,soma,turn1,turn2;
	int v;
	RM=d/2*exp(-0.25); //{g. m. d.}
	a1=h/n;
	b1b2=RM;
	z10=b+a1/2;
	z1=z10;
	z2=z10;
	for (v=1;v<=n;v++)
	{
		c=2*r/sqrt((4*r*r)+(z1-z2-b1b2)*(z1-z2-b1b2));
		double Kk,Ek;
		K_E_calc(c,Kk,Ek);
		turn1=-r*((c-2/c)*Kk+(2/c)*Ek);
		if (v==1) 
			soma=n*turn1;
		else 
		{
			c=2*r/sqrt((4*r*r)+(z1-z2+b1b2)*(z1-z2+b1b2));
			K_E_calc(c,Kk,Ek);
			turn2=-r*((c-2/c)*Kk+(2/c)*Ek);
			soma=soma+(n-(v-1))*(turn1+turn2);
		}
		z1=z1+a1;
	}
	return 4e-7*PI*soma;
} 


//11.0 === Auxiliar Functions ==========
/*
Complete elliptic integrals of first and second classes - AGM method.
Doesn’t require more than 7 iterations for c between 0 and 0.9999999999.
Reference: Pi and the AGM, J. Borwein and P. Borwein, John Wiley & Sons.
*/
void K_E_calc(double c,double &Kk,double &Ek)
{
	double a,b,a1,b1,E,i;
	a=1;
	b=sqrt(1-c*c);
	E=1-c*c/2;
	i=1;
	do
	{
		a1=(a+b)/2;
		b1=sqrt(a*b);
		E=E-i*((a-b)/2)*((a-b)/2);
		i=2*i;
		a=a1;
		b=b1;
	}
	while (fabs(a-b)>1e-15);
	Kk=PI/(2*a);
	Ek=E*Kk;
} 

//Mutual inductance between coaxial coils radius r1,r2 at a distance d between them
double M12calc(double r1,double r2,double d)
{
	double k;k=2*sqrt(r1*r2)/sqrt( (r1+r2)*(r1*r2)+d*d );
	double Kk,Ek,m;
	K_E_calc(k,Kk,Ek);
	m=-4e-7*PI*( (k-2.0/k)*Kk+2.0*Ek/k );
	return m;
}


//Complete elliptic integral of the 1st kind K(k)
double Kcalc(double k)//-1<=k<=1
{
	double sum=0.0,x,delta;long i;
	k*=k;//k squared
	if (k==1) return (1.0/(1-k));
	delta=0.5*PI/N;
	for (i=0;i<=N;i++)
	{
		x=sin(i*delta);
		sum+=1.0/sqrt(1-k*x*x);
	}
	sum=sum-0.5*(1.0/sqrt(1-k*x*x) + 1.0);
	sum=sum*delta;
	return sum;
}

//Complete elliptic integral of the 2nd kind E(k)
double Ecalc(double k)//-1<=k<=1
{
	double sum=0.0,x,delta;long i;
	k*=k;//k squared
	delta=0.5*PI/N;
	for (i=0;i<=N;i++)
	{
		x=sin(i*delta);
		sum+=sqrt(1.0-k*x*x);
	}
	sum=sum-0.5*(sqrt(1.0-k*x*x)+1.0);
	sum=sum*delta;
	return sum;
}

//Calculus when point of interest is on axis
//a=loop radius,x=distance from center of the loop to the point of interest.y=0
//Loop is in the yz plane
double Bxcalc(double a,double x,double current)
{
	double B;
	B=4e-7*PI*current/2.0*a*a/pow(x*x+a*a,1.5);
	return B;
}
