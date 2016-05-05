//Como el 101 pero quitando cosas que sobran
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define PI2 6.283185307179586476925286766559


class c_solve
{
public:
	c_solve(long dim_in1,long dim_out1,double *min1,double *max1,double *objetivo1,double error_out1,long neuras1,double neuras_res);
	~c_solve();
private:
	//variables de entrada
	long dim_in,dim_out;
	double *min,*max;//min[dim_in],max[dim_in]
	double *objetivo;//apunta a objetivo1[dim_out]
	double error_out;//Numero 1>err>1e-15
	long neuras;
	double POR;//porcentaje para multiplicar max-min, debe ser 0.9 

	//Contenido de las neuras
	double *nu;//nu[neuras*dim_in]
	double *ne;//ne[neuras*dim_out]  error=max-min, vá reduciéndose poco a poco

	long iteraciones;//cuento iteraciones
	long indexmin0;//index de error minimo
	double Errormax;//Pues eso

	double *err_min,*err_max;//[dim_out]
	void resuelve();//resuelve el asunto
	long hallaerrormin();
};

int main()
{
	c_solve *solve;
	double min1[4]={0,0,0,0};
	double max1[4]={100,200,100,100};
	double obje[4]={-1e-150,-1e-150,-1e-150,-1e-150};
	FILE *strout=fopen("out.txt","w");
	if (!strout)
	{
		printf("\nNo puedo abrir out.txt");getchar();getchar();return -1;
	}
	fprintf(strout,"Neuras1\tNeuras2\titeraciones\tError absoluto");
	fclose(strout);
	/*
	long i,j;
	for (i=100;i<1001;i+=50)
		for (j=0;j<5;j++)
		{
			solve=new c_solve(4,3,min1,max1,obje,1e-7,10000,i);delete solve;
		}
	*/
	solve=new c_solve(4,3,min1,max1,obje,1e-7,10000,450);delete solve;
	solve=new c_solve(4,3,min1,max1,obje,1e-7,10000,500);delete solve;
	solve=new c_solve(4,3,min1,max1,obje,1e-7,10000,550);delete solve;

	printf("\nFIN");
	getchar();getchar();
	return 1;
}
/*
vout[0]=100+10*sin(vin[0]*PI2/100+1)+15*sin(vin[1]*PI2/150+2)+ 8 *sin2(vin[2]*PI2/ 40+3)+31 *sin3(vin[3]*PI2/ 33+2.5);
vout[1]=110+22*sin(vin[0]*PI2/ 90+1)+15*sin(vin[1]*PI2/100+2)+20 *sin2(vin[2]*PI2/50+3)+11 *sin3(vin[3]*PI2/35+2.5);
vout[2]=10 +0.2 *sin(vin[0]*PI2/115+1)+0.15*sin(vin[1]*PI2/ 22+2)+0.2*sin2(vin[2]*PI2/ 40+3)+0.15*sin3(vin[3]*PI2/ 45+2.5);
*/
void funcion(double *vin,double *vout)
{
	vout[0]=100+10 *sin(vin[0]*PI2/100+1)+  15*sin(vin[1]*PI2/150+2)+ 8 *pow(sin(vin[2]*PI2/40+3),2)+31  *pow(sin(vin[3]*PI2/33+2.5),3);
	vout[1]=110+22 *sin(vin[0]*PI2/ 90+1)+  15*sin(vin[1]*PI2/100+2)+20 *pow(sin(vin[2]*PI2/50+3),2)+11  *pow(sin(vin[3]*PI2/35+2.5),3);
	vout[2]=10 +0.2*sin(vin[0]*PI2/115+1)+0.15*sin(vin[1]*PI2/ 22+2)+0.2*pow(sin(vin[2]*PI2/40+3),2)+0.15*pow(sin(vin[3]*PI2/45+2.5),3);
}

c_solve::c_solve(long dim_in1,long dim_out1,double *min1,double *max1,double *objetivo1,double error_out1,long neuras1,double neuras_res)
{
	dim_in=dim_in1;dim_out=dim_out1;
	objetivo=objetivo1;
	error_out=error_out1;if (error_out1<1e-10) error_out=1e-10;
	neuras=neuras1;

	//POR=pow(10,(log10(1.0*neuras_res/neuras1))/dim_in);
	POR=pow(1.0*neuras_res/neuras1,1.0/dim_in);
	//POR=1.0/(pow(1.0*neuras_res,1.0/dim_in)+1.0); //SOLO si elijo neuras_res elecciones

	min=new double[dim_in];
	max=new double[dim_in]; 
	memcpy(min,min1,dim_in*sizeof(double));
	memcpy(max,max1,dim_in*sizeof(double));

	nu=new double[neuras*dim_in ];
	ne=new double[neuras*dim_out];
	iteraciones=0;

	err_min=new double[dim_out];
	err_max=new double[dim_out];

	indexmin0=0;
	//Valor inicial:
	long i;
	do
	{
		resuelve();//Resolución
		printf("\nError:%lg",Errormax);
	}while(Errormax>error_out);
	printf("\nIteraciones:%li",iteraciones);
	printf("\nResultado:");
	for (i=0;i<dim_in;i++)
	{
		printf("\n%2li:%lg   +-%lg",i,0.5*(max[i]+min[i]),0.5*(max[i]-min[i]));
	}
	printf("\nError out:");
	double rr=0.0;
	for (i=0;i<dim_out;i++)
	{
		printf("\n%2li:%lg",i,ne[indexmin0*dim_out+i]);
		rr+=sqrt(ne[indexmin0*dim_out+i]);
	}
	printf("\nSuma de errores absolutos = %lg",rr);
	//Saco en fichero
	FILE *strout=fopen("out.txt","a");
	if (!strout)
	{
		printf("\nNo puedo abrir out.txt");getchar();getchar();return;
	}
	fprintf(strout,"\n%li\t%lg\t%li\t%lg",neuras1,neuras_res,iteraciones,rr);
	fclose(strout);
}

c_solve::~c_solve()
{
	delete[] min,max,nu,ne,err_min,err_max;
}

void c_solve::resuelve()
{
	iteraciones++;
	long i,j;
	for (i=0;i<neuras;i++)
	{
		double *nn=&nu[i*dim_in];
		for (j=0;j<dim_in;j++)
		{
			nn[j]=min[j]+(max[j]-min[j])*rand()/RAND_MAX;
		}
	}
	indexmin0=hallaerrormin();//halla quien tiene el error minimo
	double *nn=&nu[indexmin0*dim_in];
	Errormax=-1e150;
	for (j=0;j<dim_in;j++)
	{
		double err;
		err=(max[j]-min[j])/(max[j]+min[j]);
		if (Errormax<err)
			Errormax=err;
		double delta=POR*(max[j]-min[j])/2;
		if ((nn[j]+delta)<max[j])
			max[j]=nn[j]+delta;
		if ((nn[j]-delta)>min[j])
			min[j]=nn[j]-delta;

	}
}

long c_solve::hallaerrormin()
{
	long i,j;
	//hallo errormin y max
	for (j=0;j<dim_in;j++)
	{
		err_min[j]= 1e250;
		err_max[j]=-1e150;
	}
	for (i=0;i<neuras;i++)
	{
		double r;
		double *nn=&nu[i*dim_in],*ee=&ne[i*dim_out];
		funcion(nn,ee);//hallo la salida y la escribo en el vector error
		for (j=0;j<dim_out;j++)
		{
			r=ee[j]-objetivo[j];r*=r;
			ee[j]=r;//reescribo ahora el vector error
			if (err_min[j]>r)
				err_min[j]=r;
			if (err_max[j]<r)
				err_max[j]=r+1e-150;
		}
	}
	//Ahora busco el minimo
	double error_min_total=1e250;
	long indice_min=-1000;
	for (i=0;i<neuras;i++)
	{
		double err=0;
		double *ee=&ne[i*dim_out];
		for (j=0;j<dim_out;j++)
		{
			err+=(ee[j]-err_min[j])/(err_max[j]-err_min[j]);
		}
		if (error_min_total>err)
		{
			error_min_total=err;
			indice_min=i;
		}
	}
	return indice_min;
}