/*
Expande y contrae matrices de acuerdo a unos filtros filtro_fil[] y filtr_col[]
en filtro_fil se pone 0 para filas a eliminar y se deja a 1 las que no se eliminan
Lo mismo ocurre con filtro_col[] para eliminar columnas


*/
#include <stdio.h>

//Ambas admioten que mat1==mat2:
void contrae(double *mat1,double *mat2,long *filtro_fil,long *filtro_col,long *fils1,long *cols1);
void expande(double *mat1,double *mat2,long *filtro_fil,long *filtro_col,long *fils1,long *cols1,double datorelleno);

//Esta no permite que mat1==mat2:
void expande2(double *mat1,double *mat2,long *filtro_fil,long *filtro_col,long *fils1,long *cols1,double datorelleno);

int main()
{
	double mat1[4*5]={
		9 , 1, 2, 3, 4,
		10,11,12,13,14,
		20,21,22,23,24,
		30,31,32,33,34
	};
	double mat2[5*6],mat3[5*6];

	long cols=5,fils=4;
	long filtro_col[5]={1,0,1,0,1};
	long filtro_fil[4]={1,0,1,1};

	contrae(mat1,mat1,filtro_fil,filtro_col,&fils,&cols);
	expande(mat1,mat2,filtro_fil,filtro_col,&fils,&cols,-7);
	fils=fils-1;cols=cols-2;
	expande2(mat1,mat3,filtro_fil,filtro_col,&fils,&cols,-7);
	return 1;
}

void contrae(double *mat1,double *mat2,long *filtro_fil,long *filtro_col,long *fils1,long *cols1)
{//Puede hacerse contrae(mat1,mat1,...) siendo mat2=mat1
	long cols=0,fils=0,col,fil;
	double *ptr1=mat1,*ptr2=mat2;

	for (fil=0;fil<*fils1;fil++)
	{
		if (!filtro_fil[fil])
		{
			ptr1+=*cols1;
		}
		else
		{
			for (col=0;col<*cols1;col++)
			{
				if (!filtro_col[col])
					ptr1++;
				else
					*ptr2++=*ptr1++;
			}
			fils++;
		}
	}
	//calculo de cols
	for (col=0;col<*cols1;col++)
		if (filtro_col[col])
			cols++;

	*fils1=fils;*cols1=cols;
}

void expande2(double *mat1,double *mat2,long *filtro_fil,long *filtro_col,long *fils1,long *cols1,double datorelleno)
{
	if (mat1==mat2)
	{
		printf("\nERROR en contrae() mat1==mat2");
		getchar();getchar();
		*fils1=*cols1=0;
		return;
	}
	long col,fil;
	double *ptr1=mat1,*ptr2=mat2;
	for (col=0;col<*cols1;col++)
		if (!filtro_col[col])
			*cols1=*cols1+1;
	for (fil=0;fil<*fils1;fil++)
		if (!filtro_fil[fil])
			*fils1=*fils1+1;

	for (fil=0;fil<*fils1;fil++)
	{
		for (col=0;col<*cols1;col++)
		{
			if (filtro_col[col] && filtro_fil[fil])
				*ptr2++=*ptr1++;
			else
			{
				*ptr2++=datorelleno;
			}
		}
	}

}

void expande(double *mat1,double *mat2,long *filtro_fil,long *filtro_col,long *fils1,long *cols1,double datorelleno)
{
	double *ptr1=mat1+(*fils1)*(*cols1)-1;
	long col,fil;
	for (col=0;col<*cols1;col++)
		if (!filtro_col[col])
			*cols1=*cols1+1;
	for (fil=0;fil<*fils1;fil++)
		if (!filtro_fil[fil])
			*fils1=*fils1+1;

	long cols=*cols1,fils=*fils1;
	double *ptr2=mat2+fils*cols-1;
	for (fil=fils-1;fil>=0;fil--)
	{
		for (col=cols-1;col>=0;col--)
		{
			if (filtro_col[col] && filtro_fil[fil])
				*ptr2--=*ptr1--;
			else
			{
				*ptr2--=datorelleno;
			}
		}
	}

}
