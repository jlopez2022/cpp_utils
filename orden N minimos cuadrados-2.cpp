/*
Coge una serie de vectores vin (que empiezan en vin[1])
y halla el valor esperado para cada v(i) tomando como referencia v(j)
siendo j<i.
Tambien da vin-valor esperado(vin)
*/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define VARS 5  //variables menos una
#define DIMSUM VARS*(VARS+1)/2

void leelin(FILE *strin,char *linea);
//[a]=[[x]]*[b]   : se trata de hallar coeficientes b
void ecuacion_lineal(double *x,double *a,long dimension,double *b);

class min_squarec
{
public:
	void ini(); 
	void metevector(double *vin);//OJO vin[0]=1;
	void hallacoefs(); //Halla coef[][] usando suma[][]
	void hallavector(double *vin,double *vout); //da el valor esperado de vin
	void halladesv(double *vin,double *vout);//da la desviacion entre vin y el valos esperado de vin

	double coef[DIMSUM][DIMSUM];
private:
	double suma[DIMSUM][DIMSUM];
};

void min_squarec::ini()
{
	long size;
	size=DIMSUM*DIMSUM*sizeof(double);
	memset(suma,0,size);
	memset(coef,0,size);
}

void min_squarec::metevector(double *vin)//OJO vin[0]=1;
{
	long i,j;
	for (i=0;i<VARS;i++)
		for (j=i;j<VARS;j++)
			suma[i][j]+=vin[i]*vin[j];
}

void min_squarec::hallacoefs() //Halla coef[][] usando suma[][]
{
	long i,j,k;

	for (i=0;i<VARS;i++)
		for (j=i+1;j<VARS;j++)
			suma[j][i]=suma[i][j];

	double mat[VARS*VARS];
	double vec[VARS];
	coef[0][0]=suma[0][1]/suma[0][0];
	for (i=1;i<VARS;i++)
	{
		long i2=i+1;
		for (j=0;j<i2;j++)
		{
			for (k=0;k<i2;k++)
			{
				mat[j*i2+k]=suma[j][k];
			}
			vec[j]=suma[j][i+1];
		}
		ecuacion_lineal(mat,vec,i2,coef[i]);
	}
}

void min_squarec::hallavector(double *vin,double *vout)//da el valor esparado para vin
{
	long i,j;
	for (i=1;i<VARS;i++)
		vout[i]=0;
	vout[0]=coef[0][0];
	vin--;//ojo
	for (i=1;i<VARS;i++)
	{
		vout[i]=coef[i][0];
		for (j=1;j<i;j++)
		{
			vout[i]+=coef[i][1]*vin[j];
		}
	}
}

void min_squarec::halladesv(double *vin,double *vout)//da la desviacion entre vin y el valos esperado de vin
{
	long i,j;
	for (i=1;i<VARS;i++)
		vout[i]=0;
	vout[0]=vin[0]-coef[0][0];
	vin--;//ojo
	for (i=1;i<VARS-1;i++)
	{
		vout[i]=coef[i][0];
		for (j=1;j<i;j++)
		{
			vout[i]+=coef[i][1]*vin[j];
		}
		vout[i]=vin[i]-vout[i];
	}
}


void main()
{
	FILE *strin=fopen("in.txt","r");
	double u[8000][VARS-1];
	long i,j;
	char linea[1024];
	for (i=0;i<8000;i++)
	{
		leelin(strin,linea);char *ptr=linea;
		strtod(ptr,&ptr);
		for (j=0;j<VARS-1;j++)
		{
			u[i][j]=strtod(ptr+1,&ptr);
		}
	}

	min_squarec stat;
	stat.ini();
	double vin[VARS];
	vin[0]=1.0;
	for (i=0;i<8000;i++)
	{
		for (j=1;j<VARS;j++)
			vin[j]=u[i][j-1];
		stat.metevector(vin);
	}
	stat.hallacoefs();
	double vout[VARS];
	for (i=0;i<100;i++)
	{
		stat.halladesv(u[i],vout);
	}
	fclose(strin);
}




void leelin(FILE *strin,char *linea)
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






int inversa(double *x,double *y,long dimension);

//[a]=[[x]]*[b]   : se trata de hallar coeficientes b
void ecuacion_lineal(double *x,double *a,long dimension,double *b)
{
	double *y=new double[dimension*dimension];
	long i,j;
	i=inversa(x,y,dimension);
	if (i<dimension)
	{
		printf("ERROR, matriz de determinante 0");
		return;
	}
	for (i=0;i<dimension;i++)
	{
		b[i]=0;
		for (j=0;j<dimension;j++)
		{
			b[i]+=y[i*dimension+j]*a[j];
		}
	}
}


int inversa(double *x,double *y,long dimension)//x es la entrada e y la salida
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
      //imprimematriz(x,dim);
      //imprimematriz(y,dim);
   }//end ord
   return dimension;
}

