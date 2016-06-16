#include <iostream>
#include <math.h>

using namespace std;

//A=punto donde se calcula la distancia contra la recta que pasa por punto B en direccion D
float distancia_punto_recta_3d(float A[3],float B[3],float d[3])
{
	float ab[3],ab1[3],x;
	ab[0]=A[0]-B[0];ab[1]=A[1]-B[1];ab[2]=A[2]-B[2];
	ab1[0]= ab[1]*d[2]-d[1]*ab[2];
	ab1[1]=-ab[0]*d[2]+d[0]*ab[2];
	ab1[2]= ab[0]*d[1]-d[0]*ab[1];
	x=( ab1[0]*ab1[0] + ab1[1]*ab1[1] + ab1[2]*ab1[2] )/(d[0]*d[0]+d[1]*d[1]+d[2]*d[2]);
	//float x1; x1=ab1[0]*ab1[0] + ab1[1]*ab1[1] + ab1[2]*ab1[2]; x1=sqrt(x1);
	//x1=A[0]*A[0]+A[1]*A[1]+A[2]*A[2]; 	x1=sqrt(x1);
	x=sqrt(x);
	return x;
}
float distancia_punto_punto_3d(float A[3],float B[3])
{
	float ab[3],x;
	ab[0]=A[0]-B[0];ab[1]=A[1]-B[1];ab[2]=A[2]-B[2];
	x= ab[0]*ab[0] + ab[1]*ab[1] + ab[2]*ab[2];
	x=sqrt(x);
	return x;
}

 
int main()
{
	float x;
	{
		float punto[3]= { 1,-1,-1};
		float punto2[3]={ 2,2,2};//la recta pasa por punto2 y tiene la direccion dir[]
		float dir[3]=   { 1,2,2};
		x=distancia_punto_recta_3d(punto,punto2,dir);
		cout << "x=" << x << " debe ser 0.471404521\n";
	}
	{
		float punto[3]= { 1,1,0};
		float punto2[3]={ 0,1,0};//la recta pasa por punto2 y tiene la direccion dir[]
		float dir[3]=   { 1,1,0};
		x=distancia_punto_recta_3d(punto,punto2,dir);
		cout << "x=" << x << " debe ser 0.707106781\n";
	}
	{
		float punto[3]= { 10,17,11};
		float punto2[3]={ 15,20,33};//la recta pasa por punto2 y tiene la direccion dir[]
		float dir[3]=   { -5,41,13};
		x=distancia_punto_recta_3d(punto,punto2,dir);
		cout << "x=" << x << " debe ser 20.96084\n";
		x=distancia_punto_punto_3d(punto,punto2);
		cout << "x=" << x << " debe ser 22.75961\n";
	}
 
	cout <<"\n\n===FIN===" << endl;getchar();getchar();
	return 1;
}


