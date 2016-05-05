//Shows 3 different ways to create, pass to functions and delete 2d-arrays
#include <stdio.h>
#include <iostream>
using namespace std;//#include <utility>
//std::swap(matriz1m, matriz2m); //The best way but VC11 only!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define SWAP(t,a,b) ( (t) = (a), (a) = (b), (b) = (t) ) 

#define YMAX 6
#define XMAX 4


void print_data2d(float *matriz[XMAX],int max1,char *method);
void print_data2d(float (*matriz)[XMAX],int max1,char *method);

void print_adress(float (*matriz)[XMAX],int ymax,char *method);   
void print_adress(float *matriz[XMAX],int ymax,char *method);   

//This print method only works for method 1 & 2:
void print_data2d(float *matriz,int ymax,int xmax,char *method); 
//This print method only works for method 3:
void print_data2d(float **matriz,int ymax,int xmax,char *method); 



int main()
{
	int x,y;

	//The three methods to create the arrays:

	//1. First method: one-step "new" and one-step adress assign:
	//1.1. Buffer memory reservation:
	float *matriz1_m=new float[XMAX*YMAX];//Buffer
	//1.2. Address assign:
	float (*matriz1)[XMAX]=(float (*)[XMAX]) &matriz1_m[0];//Assign


	//2. Second method: No buffer needed. Only one-step "new" and one-step adress assign:
	float (*matriz2)[XMAX]=new float[YMAX][XMAX];//array definition   [XMAX], caution!!


	//3. The clasical method: by using for loop for "new" and adress assign:
	//3.1. Array declaration:
	float *matriz3[YMAX];   // [YMAX] caution!!
	//3.2. Address assign:
	for (y=0;y<YMAX;y++)
		matriz3[y]=new float[XMAX];

	//Using the three methods:
	for (y=0;y<YMAX;y++)
		for (x=0;x<XMAX;x++)
		{
			matriz1[y][x]=matriz2[y][x]=matriz3[y][x]=(y+1)*1000.0f+x;
		}
	
	
	print_data2d(&matriz1[0][0],YMAX,XMAX,"Values 1st method");
	print_data2d(&matriz2[0][0],YMAX,XMAX,"Values 2st method");
	//This only works for 3rd method:
	print_data2d(matriz3,YMAX,XMAX,"Values 3st method");

	print_data2d(matriz1,YMAX,"Values 1st method");
	print_data2d(matriz2,YMAX,"Values 2nd method");
	print_data2d(matriz3,YMAX,"Values 3rd method");

	print_adress( matriz1,XMAX,"Adress 1st method");
	print_adress( matriz2,XMAX,"Adress 2nd method");
	print_adress( matriz3,XMAX,"Adress 3rd method");



	//Array size
	//Minimum array size:
	long size=sizeof(float)*XMAX*YMAX;
	printf("\nArray size:");
	printf("\nMinimum    =%li",size);
	size= (sizeof(float) + (long) (&matriz1[YMAX-1][XMAX-1]) ) - (long) &matriz1[0][0];
	printf("\nArray 1    =%li",size);
	size= (sizeof(float) + (long) (&matriz2[YMAX-1][XMAX-1]) ) - (long) &matriz2[0][0];
	printf("\nArray 2    =%li",size);
	size= (sizeof(float) + (long) (&matriz3[YMAX-1][XMAX-1]) ) - (long) &matriz3[0][0];
	printf("\nArray 3    =%li",size);
	printf("\n");


	//Memory free for the three methods:
	//1.3. For the first creation method only one delete is used as long as one "new" was used:
	delete matriz1_m;
	//2.3. For the second creation method also only one delete is used as long as one "new" was used:
	delete[] matriz2;
	//3.3. For the third method as long as a loop was used for "new" commands, a for loop is needed for delete commands:
	for (int y=0;y<YMAX;y++)
		delete matriz3[y];

	float (*matriz4)[XMAX]=new float[YMAX][XMAX];//array definition   [XMAX], caution!!
	float (*matriz5)[XMAX]=new float[YMAX][XMAX];//array definition   [XMAX], caution!!
	float (*temp)[XMAX]=new float[YMAX][XMAX];//array definition   [XMAX], caution!!
	for (y=0;y<YMAX;y++)
		for (x=0;x<XMAX;x++)
		{
			matriz4[y][x]=(y+1)*4000.0f+x;
			matriz5[y][x]=(y+1)*5000.0f+x;
		}
		//swap:
	SWAP(temp,matriz4,matriz5);
	temp=matriz4;matriz4=matriz5;matriz5=temp;

	printf("\n\n=== END ===");getchar();getchar();
	return 1;
}

void print_adress(float (*matriz)[XMAX],int xmax,char *method)   
{
	cout << "\n============= INI DIR "<< method << "=============\n";
	int x,y;
	for (y=0;y<YMAX;y++)
	{
		for (x=0;x<xmax;x++)
			cout << ((long) (&matriz[y][x]) - (long) (&matriz[0][0])) << '\t';
		cout <<endl;
	}
	cout << "\n============= END DIR "<< method << "=============\n";
}

void print_adress(float *matriz[XMAX],int xmax,char *method)   
{
	cout << "\n============= INI DIR "<< method << "=============\n";
	int x,y;
	for (y=0;y<YMAX;y++)
	{
		for (x=0;x<xmax;x++)
			cout << ((long) (&matriz[y][x]) - (long) (&matriz[0][0])) << '\t';
		cout <<endl;
	}
	cout << "\n============= END DIR "<< method << "=============\n";
}

//Prueba de paso de matriz 2d
void print_data2d(float *matriz[XMAX],int maxy,char *method)
{
	cout << "\n============= INI VAL "<< method << "=============\n";	
	long y,x;
	for (y=0;y<maxy;y++)
	{
		for (x=0;x<XMAX;x++)
		{
			cout << matriz[y][x] <<'\t';
		}
		cout <<endl;
	}
	cout << "============= FIN VAL "<< method << "=============\n";	
}
void print_data2d(float (*matriz)[XMAX],int maxy,char *method)
{
	cout << "\n============= INI VAL "<< method << "=============\n";	
	long y,x;
	for (y=0;y<maxy;y++)
	{
		for (x=0;x<XMAX;x++)
		{
			cout << matriz[y][x] <<'\t';
		}
		cout <<endl;
	}
	cout << "============= FIN VAL "<< method << "=============\n";	
}


void print_data2d(float **matriz3,int ymax,int xmax,char *method) 
{
	cout << "\n============= INI VAL "<< method << "=============\n";	
	long y,x;
	for (y=0;y<ymax;y++)
	{
		for (x=0;x<xmax;x++)
		{
			cout << matriz3[y][x] <<'\t';
		}
		cout <<endl;
	}
	cout << "============= FIN VAL "<< method << "=============\n";	
}


void print_data2d(float *matriz1,int ymax,int xmax,char *method) 
{
	cout << "\n============= INI VAL "<< method << "=============\n";	
	long y,x;
	for (y=0;y<ymax;y++)
	{
		for (x=0;x<xmax;x++)
		{
			cout << matriz1[y*xmax+x] <<'\t';
		}
		cout <<endl;
	}
	cout << "============= FIN VAL "<< method << "=============\n";	
}