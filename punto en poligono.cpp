#include <stdio.h>
#include <string.h>
#include <math.h>

//Dá >0, si p esta a la derecha de la línea p1-p2. Da 0 si está dentro y dá <0 si está a la izquierda
// fAB(x,y) = (y-y1)(x2-x1) - (x-x1)(y2-y1) 
//double derecha(double p1[2],double p2[2],double p[2]);

//Mira si punto está en el poligono. dentro=1, fuera=0, en línea=0 o 1
//Ojo, el último punto no tiene que coincidir con el primero
bool dentro(double (*poligon)[2],long polySides,double punto[2]);



int main()
{
	double (*poligon)[2];
	poligon=new double[10][2];
	
	double datain[22]={
		2,2, 
		0,3, 
		-1,-1, 
		-3,2, 
		-4,-1, 
		-2,-4, 
		0,-2, 
		2,-3, 
		4,-1, 
		3,4};
	memcpy(poligon,datain,20*sizeof(double));

	double puntos_out[9][2]={4,3, 1,3, -1,1, -4,1, -4,0, -4,-3, 0,-3, 4,-2, 5,0};
	double puntos_in[ 9][2]={3,3.99, 1,2, 0,2,  -3,1, -3,0, -2,-1, 0,-1, 3,-1, 3,1};

	long i;
	printf("\nMirando puntos fuera:");
	for (i=0;i<9;i++)
	{
		printf("\n%li:%li",i,dentro(poligon,10,puntos_out[i]));
	}
	printf("\nMirando puntos dentro:");
	for (i=0;i<9;i++)
	{
		printf("\n%li:%li",i,dentro(poligon,10,puntos_in[i]));
	}
	getchar();getchar();

	return 0;
}


bool dentro(double (*poligon)[2],long polySides,double punto[2])
{
  int      i, j=polySides-1 ;
  bool  oddNodes=false      ;

  for (i=0; i<polySides; i++) 
  {
    if (poligon[i][1]<punto[1] && poligon[j][1]>=punto[1]
    ||  poligon[j][1]<punto[1] && poligon[i][1]>=punto[1]) 
	{
      if (poligon[i][0]+(punto[1]-poligon[i][1])/(poligon[j][1]-poligon[i][1])*(poligon[j][0]-poligon[i][0])<punto[0]) 
	  {
        oddNodes=!oddNodes; 
	  }
	}
    j=i; 
  }

  return oddNodes; 
}


/*
long dentro(double (*poligon)[2],long long_poligon,double punto[2])
{
	long i;
	double der,signo;
	der=derecha(poligon[0],poligon[1],punto);
	if (fabs(der)<1e-12)
		return 0;
	if (der<0) signo=-1.0;
	else       signo=1.0;

	for (i=2;i<long_poligon;i++)
	{
		der=derecha(poligon[i-1],poligon[i],punto);
		if (fabs(der)<1e-12)
			return 0;
		if ((signo*der)<0)
			return -1;
	}
	der=derecha(poligon[i-1],poligon[0],punto);
	if (fabs(der)<1e-12)
		return 0;
	if ((signo*der)<0)
		return -1;
	else return 1;
	
}

double derecha(double p1[2],double p2[2],double p[2])
{//Dá >0, si p esta a la derecha de la línea p1-p2. Da 0 si está dentro y dá <0 si está a la izquierda
// fAB(x,y) = (y-y1)(x2-x1) - (x-x1)(y2-y1) 
	double r;
	r=(p[1]-p1[1])*(p2[0]-p1[0])-(p[0]-p1[0])*(p2[1]-p1[1]);
	return r;
}
*/