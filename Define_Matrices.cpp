#include <stdio.h>
#include <malloc.h>

//Declaración de matrices. Ver main()

class matrizc
{
public:
	int *mat;
	long size;
	int sizex,sizey;
	matrizc::matrizc(int ix,int iy);
	int *valorout(int *x,int *y);
	int valorout(int x,int y);
	void valorin(int x,int y,int dato);
	void error(char *ch1,int dato=0,char *ch2=NULL);
};


void matrizc::error(char *ch1,int dato,char *ch2)
{
	printf("\nERROR: %s%i",ch1,dato);
	if (ch2!=NULL)
		printf("%s",ch2);
	char c;
	scanf("%c%c",&c,&c);
}

matrizc::matrizc(int ix,int iy)
{
	sizex=ix;
	sizey=iy;
	size=sizex*sizey;
	mat=new int[size];
}

int *matrizc::valorout(int *x,int *y)
{
	int z=(*x)+(*y)*sizex;
	if (z>size)
	{
		error("\nError matriz sobre rango");return(0);
	}
	if (z<0)
	{
		error("\nError matriz bajo rango");return(0);
	}
	return(&mat[z]);
}

int matrizc::valorout(int x,int y)
{
	int z=x+y*sizex;
	if (z>size)
	{
		error("\nError matriz sobre rango");return(0);
	}
	if (z<0)
	{
		error("\nError matriz bajo rango");return(0);
	}
	return(mat[z]);
}

void matrizc::valorin(int x,int y,int dato)
{
	int z=x+y*sizex;
	if (z>size)
	{
		error("\nError matriz sobre rango");
	}
	if (z<0)
	{
		error("\nError matriz bajo rango");
	}
	mat[z]=dato;
}

void main()
{
	typedef int (*matt)[256];
	int (*mat1)[256];
	matt mat2;
	mat1= new int[384][256];
	mat1[10][12]=5;
	printf("\n%i",mat1[10][12]);
	delete[] mat1;

	mat2=(matt) malloc(256*1024*sizeof(int));
	mat2[10][12]=7;
	printf("\n%i",mat2[10][12]);
	free(mat2);

	matrizc f1(300,200);
	f1.valorin(10,20,30);
	int x=10,y=20;
	printf("\n%i",*f1.valorout(&x,&y));
	printf("\n%i",f1.valorout(10,20));
	char c;
	scanf("%c%c",&c,&c);
}

