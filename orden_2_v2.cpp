#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 64  //Maximo numero de variables totales
/*
in.txt:
Primera fila debe contener el numero de variables var
Ejemplo: x,y,z1,z2.    si z1 y z2  son salidas, var=2
Ejemplo: x,y,z1,z2,z3. si z1,z2,z3 son salidas, var=3
y luego mas filas que: (var+1)+var+(var-1)+...1  =  (var^2 + 3*var + 2)/2
Halla los coeficientes c0+c1*x+c1*y+c2*xx +c3*xy+c4*yy
*/
FILE *strin;
void leelin(char *linea);
long inversa(double *x,double *y,long dimension);
long sumarial(long i)
{
	long x,y=0;
	for (x=1;x<=i;x++) y+=x;
	return y;
}

void main()
{
	//1. Inicializacion
	FILE *strout;
	strin=fopen("in.txt","r");
	if (strin==NULL)
	{
		printf("\nNo se puede abrir in.txt");
		char c;scanf("%c%c",&c,&c);return;
	}
	//2. Leo numero de variables (1 o 2)
	char linea[1024];
	leelin(linea);
	long var;
	var=atol(linea);
	if ((var>=MAX)||(var<1))
	{
		printf("\nError, var=%li",var);
		char c;scanf("%c%c",&c,&c);return;
	}
	//3. Cuento numero de filas y columnas:
	long col=-1,i;

	leelin(linea);
	i=strlen(linea);linea[i]=' ';linea[i+1]='\0';
	char *linea2=linea,*linea3;
	do 
	{
		linea3=linea2;
		strtod(&linea2[0],&linea2);
		col++;
	}while (linea3!=linea2);
	long lineas=1;
	while(!feof(strin))
	{
		leelin(linea);
		if (strlen(linea)<3) break;
		lineas++;
	}
	fclose(strin);
	//4. Leo datos de entrada:
	strin=fopen("in.txt","r");
	if (strin==NULL)
	{
		printf("\nNo se puede abrir in.txt por segunda vez");
		char c;scanf("%c%c",&c,&c);return;
	}
	leelin(linea);
	double (*datin)[2*MAX]; //Maximo 64 variables in y 64 out
	double vin[2*MAX]; 
	datin=new double[lineas][2*MAX];
	long j,k,dimen;//dim,en es la dimension de la matriz
	dimen=sumarial(col-var+1);
	if (lineas<dimen)
	{
		printf("\nError: Numero de filas:%li que es menor que:%li",lineas,dimen);
		char c;scanf("%c%c",&c,&c);return;
	}

	for (i=0;i<lineas;i++)
	{
		long pos=0;
		vin[0]=1;
		leelin(linea);linea2=linea-1;
		for (j=1;j<=col;j++)
		{
			vin[j]=strtod(&linea2[1],&linea2);
		}
		long l=0;
		for (j=0;j<(col-var+1);j++)
		{
			for (k=j;k<(col-var+1);k++)
			{
				datin[i][l++]=vin[j]*vin[k];
			}
		}
		for (k=0;k<var;k++)
			datin[i][l++]=vin[col-var+1+k];
	}
	//5. Dimensiono matrices [out]=[MAT]*[COEF]  
	//Entonces               [coef]=inversa-traspuesta[MAT]*[out]
	double  MAT[MAX][MAX];
	double COEF[MAX][MAX];//Solo uso COEF[var][matdim]
	double  OUT[MAX][MAX];//Solo uso OUT[matdim][var]
	i=MAX*MAX*sizeof(double);
	memset(MAT ,0,i);
	memset(COEF,0,i);
	memset(OUT ,0,i);
	//6. Relleno las matrices MAT y OUT:
	for (i=0;i<lineas;i++)
	{
		for (j=0;j<dimen;j++)
		{
			for (k=0;k<dimen;k++)
				MAT[j][k]+=datin[i][j]*datin[i][k];
			for (k=dimen;k<(dimen+var);k++)
				OUT[j][k-dimen]+=datin[i][j]*datin[i][k];
		}
	}
	//7. Hallo la inversa de MAT
	double *MAT1=new double[dimen*dimen];
	i=0;
	for (j=0;j<dimen;j++)
	{
		for (k=0;k<dimen;k++)
			MAT1[i++]=MAT[j][k];
	}
	double *MAT2=new double[dimen*dimen];
	i=inversa(MAT1,MAT2,dimen);
	if (i<dimen)
	{
		printf("\nError: La matriz a invertir es de determinante nulo");
		char c;scanf("%c%c",&c,&c);return;
	}

	//8. Meto la inversa de MAT en MAT:
	i=0;
	for (j=0;j<dimen;j++)
	{
		for (k=0;k<dimen;k++)
			MAT[j][k]=MAT2[i++];
	}
	//9. COEF=traspuesta_inversa(MAT)*OUT
	strout=fopen("out.txt","w");
	if (strout==NULL)
	{
		printf("\nNo se puede abrir out.txt");
		char c;scanf("%c%c",&c,&c);return;
	}
	for (i=0;i<var;i++)
	{
		for (j=0;j<dimen;j++)
		{
			for (k=0;k<dimen;k++)
			{
				COEF[i][j]+=MAT[k][j]*OUT[k][i];
			}
			fprintf(strout,"%lg\t",COEF[i][j]);
		}
		fprintf(strout,"\n");
	}
	fclose(strout);
	//10. Comprobacion de resultados:
	double *error=new double[var];
	memset(error,0,var*sizeof(double));
	for (i=0;i<lineas;i++)
	{
		for (k=0;k<var;k++)
		{
			double err,z=0;
			for (j=0;j<dimen;j++)
			{
				z+=datin[i][j]*COEF[k][j];
			}
			err=z-datin[i][dimen+k];err*=err;
			error[k]+=err;
		}
	}
	for (k=0;k<var;k++)
	{
		error[k]=sqrt(error[k]/lineas);
		printf("\nError RMS en var %li es: %lg",k,error[k]);
	}
	printf("\nFIN");
	char c;scanf("%c%c",&c,&c);
}


void leelin(char *linea)
{
	int i;
	linea[0]='\0';
	char *ptr=linea;
	for (i=0;(i<1024 && !feof(strin)); i++)
	{
		fscanf(strin,"%c",ptr++);
		if (ptr[-1]==10)
			break;
	}
	//fscanf(strin,"%c",linea--);
	if (i>=1)
		ptr[-1]='\0';
	else
		linea[0]='\0';
}

long inversa(double *x,double *y,long dimension)
{
	int i,j,ord;
	double *ptrx,*ptrx0,*ptry,*ptry0,*ptrx00,*ptry00,x0;
	for (ord=0;ord<dimension;ord++)
	{
		//Hacemos elemento diagonal=1
		ptrx0=x+ord*dimension+ord;
		ptry=y+ord*dimension;
		if (!*ptrx0) return ord;
		for (i=0;i<ord;i++)
		 *ptry++/=*ptrx0; //y(ord,i<ord)=y/x(ord,ord)
		*ptry=1./ *ptrx0;   //y(ord,ord)  =1/x(ord,ord)
		ptrx=ptrx0+1;
		for (i=ord+1;i<dimension;i++)
		 *ptrx++ /= *ptrx0; //x(ord,i>ord)=x/x(ord,ord)

		//Hacemos toda la columna "ord" =0 salvo el valor en (ord,ord)
		ptry00=y+dimension*ord;
		ptrx00=x+dimension*ord+ord+1;
		for (j=0;j<dimension;j++)  //todas las filas
		if (j!=ord)          //salvo la ord
		{
			 ptrx=x+j*dimension+ord;x0=*ptrx;
			 ptry=y+j*dimension;ptry0=ptry00;
			 for (i=0;i<ord;i++) //columnas Y desde 0 a ord
				*ptry=(*ptry++)-(*ptry0++)*x0;
			 *ptry=-(*ptry0++)*x0;//columna Y ord;
     
			 ptrx++;ptrx0=ptrx00;
			 for (i=ord+1;i<dimension;i++) //columnas x desde ord a dim
				*ptrx=(*ptrx++)-(*ptrx0++)*x0;
		}
	}//end ord
	return dimension;
}

