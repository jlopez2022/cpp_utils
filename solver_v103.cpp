#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define PI2 6.283185307179586476925286766559

double COEF0=0.33;


class c_solve
{
public:
	c_solve(long dim_in1,long dim_out1,double *min1,double *max1,double *objetivo1,double error_out1,long neuras1,long neuras_sel1);
	~c_solve();
private:
	//variables de entrada
	long dim_in,dim_out;
	double *min,*max;//min[dim_in],max[dim_in]
	double *objetivo;//apunta a objetivo1[dim_out]
	double error_out;//Numero 1>err>1e-15
	long neuras,neuras_sel;

	double POR;//porcentaje para multiplicar max-min, debe ser 0.9 
	long indexmin0;//indice de la neurona mas cercana a la solucion
	long neuras_sel_max;
	double *delta;//delta[dim_in]

	//Contenido de las neuras
	double *nu;//nu[neuras*dim_in]
	double *ne;//ne[neuras*dim_out]  error=max-min, vá reduciéndose poco a poco
	double *net;//net[neuras]  suma de errores
	double *nc;//nc[neuras_sel*dim_in] contiene los vectores de menor error

	long   iteraciones;//cuento iteraciones
	double Errormax;//Pues eso

	double *err_min,*err_max;//[dim_out]
	void elige_rand(long neurona_sel_index);//halla vectores alrededor de un centro nc y los crea en el bloque indicado por: neurona_sel_index=0..neuras_sel
	void hallaerror();//halla el error
};

int main()
{
	c_solve *solve;
	double min1[4]={0.0,0.0,0.0,0.0};
	double max1[4]={100.0,200.0,100.0,100.0};
	double obje[4]={-1e-150,-1e-150,-1e-150,-1e-150};
	FILE *strout=fopen("out.txt","w");
	if (!strout)
	{
		printf("\nNo puedo abrir out.txt");getchar();getchar();return -1;
	}
	fprintf(strout,"Neuras1\tNeuras2\tCOEF0\titeraciones\tError absoluto");
	fclose(strout);
	/*
	long i,j;
	for (i=100;i<1001;i+=50)
		for (j=0;j<5;j++)
		{
			solve=new c_solve(4,3,min1,max1,obje,1e-7,10000,i);delete solve;
		}
	*/
	solve=new c_solve(4,3,min1,max1,obje,1e-7,1022,8);delete solve;
	COEF0=0.5;
	solve=new c_solve(4,3,min1,max1,obje,1e-7,1024,8);delete solve;
	solve=new c_solve(4,3,min1,max1,obje,1e-7,1024,8);delete solve;
	solve=new c_solve(4,3,min1,max1,obje,1e-7,1024,8);delete solve;
	solve=new c_solve(4,3,min1,max1,obje,1e-7,1024,8);delete solve;
	COEF0=0.33;
	solve=new c_solve(4,3,min1,max1,obje,1e-7,1024,8);delete solve;
	solve=new c_solve(4,3,min1,max1,obje,1e-7,1024,8);delete solve;
	solve=new c_solve(4,3,min1,max1,obje,1e-7,1024,8);delete solve;
	solve=new c_solve(4,3,min1,max1,obje,1e-7,1024,8);delete solve;
	solve=new c_solve(4,3,min1,max1,obje,1e-7,1024,8);delete solve;

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

c_solve::c_solve(long dim_in1,long dim_out1,double *min1,double *max1,double *objetivo1,double error_out1,long neuras1,long neuras_sel1)
{
	//1. Inicializo variables
	dim_in=dim_in1;dim_out=dim_out1;
	objetivo=objetivo1;
	error_out=error_out1;if (error_out1<1e-10) error_out=1e-10;
	neuras=neuras1;neuras_sel=neuras_sel1;
	if (neuras % neuras_sel)
	{
		neuras=neuras_sel* (long) (1.0*neuras/neuras_sel+0.5);
	}
	neuras_sel_max=neuras/neuras_sel;//vectores en cada subneurona

	//POR=pow(10,(log10(1.0*neuras_res/neuras1))/dim_in);
	//POR=pow(1.0*neuras_res/neuras1,1.0/dim_in);
	POR=1.0/(pow(COEF0*neuras_sel,1.0/dim_in)+1.0); //SOLO si elijo neuras_res elecciones

	min=min1;
	max=max1;

	nu= new double[neuras*dim_in ];
	ne= new double[neuras*dim_out];
	net=new double[neuras];//suma de errores
	nc= new double[neuras_sel*dim_in];//vectores de menor error
	iteraciones=0;

	err_min=new double[dim_out];
	err_max=new double[dim_out];

	delta=new double[dim_in];


	//2. //Inicialización de vectores
	//2.1. Delta:
	long i,j;
	for (j=0;j<dim_in;j++)
	{
		delta[j]=(max[j]-min[j])*(1.0+1e-7);
	}
	//2.2. Creo centros iniciales, todos en medio:
	for (i=0;i<neuras_sel;i++)
	{
		for (j=0;j<dim_in;j++)
		{
			nc[i*dim_in+j]=0.5*(min[j]+max[j]);
		}
		elige_rand(i);
	}
	Errormax=1e200;

	//Hago la búsqueda
	while(Errormax>error_out)
	{
		//Hallo el error de todos los vectores
		hallaerror();
		iteraciones++;
		//hallo los centros
		for (i=0;i<neuras_sel;i++)
		{
			long k,kindex=-1;
			double emin=1e200;
			for (k=0;k<neuras;k++)
			{
				if (emin>net[k])
				{
					emin=net[k];
					kindex=k;
				}
			}
			net[kindex]=1e200;//Quito de enmedio el centro elegido
			memcpy(nc+i*dim_in,nu+kindex*dim_in,dim_in*sizeof(double));
			if (i==0)
				indexmin0=kindex;
		}
		//Hallo delta
		//hallo Errormax 
		Errormax=-1e200;
		double r;
		for (j=0;j<dim_in;j++)
		{
			r=delta[j]/(1e-150+nc[j]);
			if (Errormax<r)
				Errormax=r;
			delta[j]*=POR;
		}
		//Elijo nuevos vectores alrededor de cada centro
		for (i=0;i<neuras_sel;i++)
		{
			elige_rand(i);
		}
	}//FIN
	printf("\nIteraciones:%li",iteraciones);
	printf("\nResultado:");
	for (i=0;i<dim_in;i++)
	{
		printf("\n%2li:%lg   +-%lg",i,nc[i],delta[i]);
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
	fprintf(strout,"\n%li\t%li\t%lg\t%li\t%lg",neuras1,neuras_sel,COEF0,iteraciones,rr);
	fclose(strout);
}

c_solve::~c_solve()
{
	delete[] nu,ne,net,nc,err_min,err_max,delta;
}

void c_solve::elige_rand(long neurona_sel_index)//halla vectores alrededor de un centro nc y los crea en el bloque indicado por: neurona_sel_index=0..neuras_sel
{
	double *nc1=nc+neurona_sel_index*dim_in;
	double *nn1=nu+neurona_sel_index*neuras_sel_max*dim_in;
	long i,j;
	for (i=0;i<neuras_sel_max;i++)
	{
		double *nn2=nn1+i*dim_in;
		for (j=0;j<dim_in;j++)
		{
			double r;
			r=((1.0*rand()/RAND_MAX)-0.5)*delta[j];
			r+=nc1[j];
			if (r<min[j])
				r=min[j];
			else if (r>max[j])
				r=max[j];
			nn2[j]=r;
		}
	}
}

void c_solve::hallaerror()
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
			if (err_max[j]<-1e90)
				err_max[j]=err_max[j];
		}
	}
	//Ahora hallo el error total 
	for (i=0;i<neuras;i++)
	{
		double err=0;
		double *ee=&ne[i*dim_out];
		for (j=0;j<dim_out;j++)
		{
			err+=(ee[j]-err_min[j])/(err_max[j]-err_min[j]);
		}
		net[i]=err;//Meto el error total 
	}
}