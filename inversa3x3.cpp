#include <stdio.h> 
#include <math.h> //fabs()
#include <time.h>//solo para tests de velocidad


//long invierte3x3(__int16 a[3][3],double b[3][3]);
long invierte3x3(__int16 *ax,double *bx);//Hace 25 megainversiones/segundo
//OJO: y sale traspuesta!!
void multiplica3x3(__int16 *ax,double *bx,double *cx);//calcula cx=ax*bx. Multiplica 53millones de pares de matrices por segundo

//Halla el vector de trasformada a[12] que trasforma un sistema de coordenadas coor1 en otro coor2. coor1=coordenadas en 3d de 4 puntos de referencia
int trasformada4p_hallacoef(__int16 coor1[12],__int16 coor2[12],double a[12]); 
//Usa los coeficientes a hallados por trasformada4p_hallacoef() para trasformar el punto xyz1 basado en coor1  en xyz2 basado en coor2
void transformada4P(double a[12],__int16 xyz1[3],__int16 xyz2[3]);


int main()
{
/*
!a00 a10 a20!
!a01 a11 a21!
!a02 a12 a22! */
	__int16 mat1[9]={ -50,100,10,50,100,10, 0,20,5 };
	long i;
	printf("\nMatriz-1=");
	for (i=0;i<9;i++)
	{
		if ( i % 3 == 0 ) printf("\n");printf("%li \t",mat1[i]);
	}
	double mat2[9],mat3[9],mat4[9];
	invierte3x3(mat1,mat3);
	printf("\nMatriz-3=");
	for (i=0;i<9;i++)
	{
		mat2[i]=mat1[i];
		if ( i % 3 == 0 ) printf("\n");printf("%10.4lg \t",mat3[i]);
	}
	multiplica3x3(mat1,mat3,mat4); 
	printf("\nMatriz-4=");
	for (i=0;i<9;i++)
	{
		if ( i % 3 == 0 ) printf("\n");printf("%10.4lg ",mat4[i]);
	}
	printf("\n\nTest de velocidad invierte3x3:");
	clock_t ini,fin;double seconds,kk=0.1;
	long N=10000000L; //10megas
	ini=clock();
	for (i=0;i<N;i++)
	{
		invierte3x3(mat1,mat3);
		kk+=mat3[0];//prevents to optimizer to not avoid doing the for loop
	}
	fin=clock();
	seconds=1.0*(fin-ini)/CLOCKS_PER_SEC;
	printf("\nSegundos=%lg \nMegaoperaciones/segundo=%lg",seconds,1.0e-6*N/seconds);

	printf("\n\nTest de velocidad multiplica3x3:");
	ini=clock();
	for (i=0;i<N;i++)
	{
		multiplica3x3(mat1,mat3,mat4); 
		kk+=mat4[0];//prevents to optimizer to not avoid doing the for loop
	}
	fin=clock();
	seconds=1.0*(fin-ini)/CLOCKS_PER_SEC;
	printf("\nSegundos=%lg \nMegaoperaciones/segundo=%lg",seconds,1.0e-6*N/seconds);

	printf("\n\nTest de velocidad invierte3x3:");
	ini=clock();
	for (i=0;i<N;i++)
	{
		invierte3x3(mat1,mat3);
		kk+=mat3[0];//prevents to optimizer to not avoid doing the for loop
	}
	fin=clock();
	seconds=1.0*(fin-ini)/CLOCKS_PER_SEC;
	printf("\nSegundos=%lg \nMegaoperaciones/segundo=%lg",seconds,1.0e-6*N/seconds);

	printf("\n\n===FIN===");getchar();getchar();
	return 0;
}



long invierte3x3(__int16 *ax,double *bx)
{
	__int16 (*a)[3]= (__int16 (*)[3]) ax;
	double  (*b)[3]= (double  (*)[3]) bx;

	double det =     a[0][0]*(a[1][1]*a[2][2]-a[2][1]*a[1][2])
							-a[0][1]*(a[1][0]*a[2][2]-a[1][2]*a[2][0])
							+a[0][2]*(a[1][0]*a[2][1]-a[1][1]*a[2][0]);
	if (det==0) return 0;
	b[0][0] =  (a[1][1]*a[2][2]-a[2][1]*a[1][2])/det;
	b[0][1] = -(a[0][1]*a[2][2]-a[0][2]*a[2][1])/det;
	b[0][2] =  (a[0][1]*a[1][2]-a[0][2]*a[1][1])/det;
	b[1][0] = -(a[1][0]*a[2][2]-a[1][2]*a[2][0])/det;
	b[1][1] =  (a[0][0]*a[2][2]-a[0][2]*a[2][0])/det;
	b[1][2] = -(a[0][0]*a[1][2]-a[1][0]*a[0][2])/det;
	b[2][0] =  (a[1][0]*a[2][1]-a[2][0]*a[1][1])/det;
	b[2][1] = -(a[0][0]*a[2][1]-a[2][0]*a[0][1])/det;
	b[2][2] =  (a[0][0]*a[1][1]-a[1][0]*a[0][1])/det;
	return 1;
}

void multiplica3x3(__int16 *ax,double *bx,double *cx)//multiplica cx=ax*bx
{
	__int16 (*a)[3]= (__int16 (*)[3]) ax;
	double  (*b)[3]= (double  (*)[3]) bx;
	double  (*c)[3]= (double  (*)[3]) cx;
	c[0][0]=a[0][0]*b[0][0]+a[0][1]*b[1][0]+a[0][2]*b[2][0];
	c[0][1]=a[0][0]*b[0][1]+a[0][1]*b[1][1]+a[0][2]*b[2][1];
	c[0][2]=a[0][0]*b[0][2]+a[0][1]*b[1][2]+a[0][2]*b[2][2];

	c[1][0]=a[1][0]*b[0][0]+a[1][1]*b[1][0]+a[1][2]*b[2][0];
	c[1][1]=a[1][0]*b[0][1]+a[1][1]*b[1][1]+a[1][2]*b[2][1];
	c[1][2]=a[1][0]*b[0][2]+a[1][1]*b[1][2]+a[1][2]*b[2][2];

	c[2][0]=a[2][0]*b[0][0]+a[2][1]*b[1][0]+a[2][2]*b[2][0];
	c[2][1]=a[2][0]*b[0][1]+a[2][1]*b[1][1]+a[2][2]*b[2][1];
	c[2][2]=a[2][0]*b[0][2]+a[2][1]*b[1][2]+a[2][2]*b[2][2];
}





