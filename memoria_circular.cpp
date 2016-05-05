//memoria circular
#include <stdio.h>
#define MAX 40  //Tamaño de la matriz
#define MAX2 80 //2*MAX

class B_C//para entrada de datos. m[im],m[im-1] es entrada última y penúltima de datos
{
public:
	B_C(void) {im=-1;}
	void in(double x) //incrementa el indice y luego mete el dato
	{ 
		im=(im+1) % MAX;
		m[im]=x;
	}
	double out(long i) //si i=0,1,2 se saca dato ult,penult y antepenult
	{ 
		i=(i<=im) ? im-i : MAX+im-i;
		return m[i];
	}
	long im;//indice
private:
	double m[MAX];//memoria
};


void main()
{
	double m[MAX];long im=10;//im=indice de matriz m
	long i;
	for (i=0;i<MAX;i++)
		m[i]=(double) i;
	double x;
	i= 20;x=m[(i+im+MAX2) % MAX];
	i=-20;x=m[(i+im+MAX2) % MAX];
	i=45; x=m[(i+im+MAX2) % MAX];
	i=i;

	//Usamos ahora la clase:
	B_C b1;
	for (i=0;i<30;i++)
		b1.in(-999.0);
	for (i=0;i<MAX;i++)
		b1.in(10000.0+i);
	i=  0;x=b1.out(i);
	i=  1;x=b1.out(i);
	i=  2;x=b1.out(i);
	i= 10;x=b1.out(i);
	i= 20;x=b1.out(i);
	i= 30;x=b1.out(i);
	i= 39;x=b1.out(i);
	i= 40;x=b1.out(i);
	i= 41;x=b1.out(i);
	i=i;
}