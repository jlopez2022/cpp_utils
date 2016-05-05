#include <stdio.h> 
#include <math.h> //fabs()
#include <time.h>//solo para tests de velocidad
#define REDONDEO 0.5 //usado en funcion trasformada4p_hallacoef() para que luego transformada4P() redondee mejor a __int16 


//long invierte3x3(__int16 a[3][3],double b[3][3]);
long invierte3x3(__int16 *ax,double *bx);//Hace 25 megainversiones/segundo
long invierte3x3(double  *ax,double *bx);//Hace 25 megainversiones/segundo
//OJO: y sale traspuesta!!
void multiplica3x3(__int16 *ax,double *bx,double *cx);//calcula cx=ax*bx. Multiplica 53millones de pares de matrices por segundo

//Halla el vector de trasformada coef[12] que trasforma un sistema de coordenadas coor1 en otro coor2. coor1=coordenadas en 3d de 4 puntos de referencia
//Su velocidad es de 13 millones de ejecuciones/segundo
int trasformada4p_hallacoef(__int16 coor1[12],__int16 coor2[12],double coef[12]); 
//Usa los coeficientes coef hallados por trasformada4p_hallacoef() para trasformar el punto xyz1 basado en coor1  en xyz2 basado en coor2
//Su velocidad es de 118 millones de ejecuciones/segundo
void trasformada4P(double coef[12],__int16 xyz1[3],__int16 xyz2[3]);


int main()
{
/*
!a00 a10 a20!
!a01 a11 a21!
!a02 a12 a22! */
	__int16 mat1[12]={ -50,100,10,55,100,50, 15,-20,28, 66,45,-25 };
	__int16 mat2[12]={ -33,38, 55,95,-45,33, 12, 22,48, 23,45, 45 };
	double coef[12];
	double mat3[9];
	long i;
	trasformada4p_hallacoef(mat1,mat2,coef);

	printf("\n\nTest de trasformada4P");
	for (i=0;i<4;i++)//pruebo trasformando los cuatro puntos
	{
		__int16 *a,*b,c[3];
		a=mat1+3*i;
		b=mat2+3*i;
		trasformada4P(coef,a,c);
		int j;
		for (j=0;j<3;j++)
			printf("\ntrasformada de %i debe ser %i y es %i",a[j],b[j],c[j]); 
	}

	clock_t ini,fin;double seconds,kk=0.1;long N=10000000L; //10megas
	printf("\n\nTest de velocidad trasformada4p_hallacoef:");
	ini=clock();N=10000000L; //10megas
	for (i=0;i<N;i++)
	{
		trasformada4p_hallacoef(mat1,mat2,coef);
		kk+=coef[0];//prevents to optimizer to not avoid doing the for loop
	}
	fin=clock();
	seconds=1.0*(fin-ini)/CLOCKS_PER_SEC;
	printf("\nSegundos=%lg \nMegaoperaciones/segundo=%lg",seconds,1.0e-6*N/seconds);

	printf("\n\nTest de velocidad trasformada4P:");
	ini=clock();N=100000000L; //100megas
	for (i=0;i<N;i++)
	{
		__int16 c[3],*a=mat1;
		trasformada4P(coef,a,c);
		kk-=c[0];a[0]+=1e-199;//prevents to optimizer to not avoid doing the for loop
	}
	fin=clock();
	seconds=1.0*(fin-ini)/CLOCKS_PER_SEC;
	printf("\nSegundos=%lg \nMegaoperaciones/segundo=%lg",seconds,1.0e-6*N/seconds);

	printf("\n\nTest de velocidad invierte3x3:");
	ini=clock();N=10000000L; //10megas
	for (i=0;i<N;i++)
	{
		invierte3x3(mat1,mat3);
		kk+=mat3[0];//prevents to optimizer to not avoid doing the for loop
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

long invierte3x3(double *ax,double *bx)
{
	double (*a)[3]= (double (*)[3]) ax;
	double (*b)[3]= (double (*)[3]) bx;

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
void multiplica3x3(double *ax,double *bx,double *cx)//multiplica cx=ax*bx
{
	double (*a)[3]= (double (*)[3]) ax;
	double (*b)[3]= (double (*)[3]) bx;
	double (*c)[3]= (double (*)[3]) cx;
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

//Halla el vector de trasformada a[12] que trasforma un sistema de coordenadas coor1 en otro coor2. coor1=coordenadas en 3d de 4 puntos de referencia
int trasformada4p_hallacoef(__int16 coor1[12],__int16 coor2[12],double coef[12])
{
	double a[9],b[9],ia[9];//ia=inversa de a[]
	long i;
	for (i=0;i<9;i++) a[i]=coor1[i+3]-coor1[i % 3];//resto a los tres puntos de referencia el 0 que es el origen de coordenadas
	for (i=0;i<9;i++) b[i]=coor2[i+3]-coor2[i % 3];//tambien en coor2
	invierte3x3(a,ia);
	multiplica3x3(ia,b,coef);//ojo, solo relleno coef[0-8] conteniendo los coefs a multiplicar por x,y,z. Loas terminos constantes estan en coef[9-11]
	//Nota: [a]*[coef]=[b]  funciona bien, comprobado
	coef[ 9]=coor2[0]-(coor1[0]*coef[0]+coor1[1]*coef[3]+coor1[2]*coef[6])+REDONDEO;
	coef[10]=coor2[1]-(coor1[0]*coef[1]+coor1[1]*coef[4]+coor1[2]*coef[7])+REDONDEO;
	coef[11]=coor2[2]-(coor1[0]*coef[2]+coor1[1]*coef[5]+coor1[2]*coef[8])+REDONDEO;
	return 1;
}
//Usa los coeficientes a hallados por trasformada4p_hallacoef() para trasformar el punto xyz1 basado en coor1  en xyz2 basado en coor2
void trasformada4P(double coef[12],__int16 xyz1[3],__int16 xyz2[3])
{
	xyz2[0]= (__int16) (xyz1[0]*coef[0]+ xyz1[1]*coef[3]+ xyz1[2]*coef[6] + coef[ 9]);
	xyz2[1]= (__int16) (xyz1[0]*coef[1]+ xyz1[1]*coef[4]+ xyz1[2]*coef[7] + coef[10]);
	xyz2[2]= (__int16) (xyz1[0]*coef[2]+ xyz1[1]*coef[5]+ xyz1[2]*coef[8] + coef[11]);
}




