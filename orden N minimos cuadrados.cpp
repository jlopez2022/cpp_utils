/* 

  FUNCIONA FENOMENO HASTA 2 salidas y orden=4
  El fichero "conversion.txt" esta puesto abajo del todo

Sean 2 entradas x,y y dos salidas u,v

este programa halla coeficientes que multiplicados por:

  1 x y xx xy yy xxx xxy xyy yyy  ->orden=4
  sale u o v

Si orden=3 los coefs se multiplican por:

  1 x y xx xy yy

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

long inversa(double *x,double *y,long dimension);//x es la entrada e y la salida
void ecuacion_lineal(double *x,double *a,long dimension,double *b);
void leelin(FILE *strin,char *linea);

class ordenc
{
public:
	ordenc(long datosout,long orden);
	void mete(double *din,double *dout);
	void interpola(double *din,double *dout);
	void resuelve();
private:
	long datosout,orden;
	double *vin;long vinsize;
	double *sumain ;long sumainsize;
	double *sumaout;long sumaoutsize;
	double *coef;

	long sumarial(long in) {long suma=0;for (long i=1;i<=in;i++) suma+=i;return(suma);}
	~ordenc(){delete[] vin,sumain,sumaout,coef;}
};

ordenc::ordenc(long datosout,long orden)
{
	this->datosout=datosout;this->orden=orden;
	vinsize=sumarial(orden);   vin=new double[vinsize];vin[0]=1.0; //ojo
	sumainsize=vinsize*vinsize;sumain =new double[sumainsize];
	sumaoutsize=datosout*vinsize;sumaout=new double[sumaoutsize];
	coef=new double[vinsize*datosout];
	long i;
	for (i=0;i<sumainsize ;i++)  sumain[i]=0.0;
	for (i=0;i<sumaoutsize;i++) sumaout[i]=0.0;
}

void ordenc::mete(double *din,double *dout)
{
	//1. Hallo vin= 1,x,y,xx,xy,yy,xxx,xxy,xyy,yyy  orden=4
	long i,l=1,l0=0,l1,ord;
	for (ord=1;ord<orden;ord++)//ord=1 implica que vin=1 como ya es
	{
		l1=l;vin[l++]=vin[l0]*din[0];
		for (i=l0;i<l1;i++)
		{
			vin[l++]=vin[i]*din[1];
		}
		l0=l1;
	}
/*	if (l!=vinsize)
	{
		printf("\nError en calculo vin");
		char c;scanf("%c%c",&c,&c);
	}
*/	//2. Hallo sumas
	long j,k;
	for (i=0;i<vinsize;i++)
	{
		k=i*vinsize;
		for (j=i;j<vinsize;j++)
		{
			sumain[k+j]+=vin[i]*vin[j];
		}
		for (j=0;j<datosout;j++)
		{
			sumaout[j*vinsize+i]+=vin[i]*dout[j];
		}
	}
}

void ordenc::interpola(double *din,double *dout)
{
	//1. Hallo vin= 1,x,y,xx,xy,yy,xxx,xxy,xyy,yyy  orden=4
	long i,l=1,l0=0,l1,ord;
	for (ord=1;ord<orden;ord++)//ord=1 implica que vin=1 como ya es
	{
		l1=l;vin[l++]=vin[l0]*din[0];
		for (i=l0;i<l1;i++)
		{
			vin[l++]=vin[i]*din[1];
		}
		l0=l1;
	}
	for (i=0;i<datosout;i++)
	{
		dout[i]=0.0;
		for (long j=0;j<vinsize;j++)
		{
			dout[i]+=vin[j]*coef[i*vinsize+j];
		}
	}
}

void ordenc::resuelve()
{
	long i,j;
	for (i=0;i<vinsize;i++)
		for (j=i+1;j<vinsize;j++)
			sumain[j*vinsize+i]=sumain[i*vinsize+j];//sumain[i][j]=sumain[j][i]
	//Hallo coeficientes
//	double *x=new double[vinsize*vinsize];
	double *x2=new double[vinsize*vinsize];
	long result=inversa(sumain,x2,vinsize);
	if (result<vinsize)
	{
		printf("\nError en datos de entrada: determinante nulo");
		return;
	}
	double *y=new double[vinsize];
	for (long k=0;k<datosout;k++)
	{
		for (i=0;i<vinsize;i++) y[i]=sumaout[i+k*vinsize];

		double *coef2=coef+k*vinsize;
		for(i=0;i<vinsize;i++)
		{
			coef2[i]=0.0;
			for(j=0;j<vinsize;j++)
				coef2[i]+=x2[j*vinsize+i]*y[j];
		}
	}
	delete[] x2,y;
}

void main()
{
	ordenc *orden; orden=new ordenc(2,3);//2 datos de salida. Hasta yy
	double in[2],out[2];
	FILE *strin=fopen("conversion.txt","r");
	char linea[1024];
	leelin(strin,linea);
	double in_mat[32][2],out_mat[32][2];
	long i,j;
	for (i=0;i<17;i++)
	{
		leelin(strin,linea);
		char *ptr=linea;
		in[0]=strtod(ptr,&ptr);
		in[1]=strtod(ptr+1,&ptr);
		out[0]=strtod(ptr+1,&ptr);
		out[1]=strtod(ptr+1,&ptr);
		orden->mete(in,out);
		for (j=0;j<2;j++)
			in_mat[i][j]=in[j];
		out_mat[i][0]=out[0];
		out_mat[i][1]=out[1];
	}
	fclose(strin);
	orden->resuelve();
	double out2[2];
	printf("\nError:");
	for (i=0;i<17;i++)
	{
		in[0]=in_mat[i][0];
		in[1]=in_mat[i][1];
		orden->interpola(in,out2);
		printf("\n %lf  \t%lf",out2[0]-out_mat[i][0],out2[1]-out_mat[i][1]);
	}
	char c;scanf("%c%c",&c,&c);
}




long inversa(double *x2,double *y,long dim)//x es la entrada e y la salida
{
	int i,j,ord;
	double *x=new double[dim*dim];
	//1. Hacemos la matriz y=unidad  y 
	//   copiamos la matriz x[]=x2[]
	for (i=0;i<dim*dim;i++) {y[i]=0.0;x[i]=x2[i];}
	for (i=0;i<dim    ;i++) y[i*dim+i]=1.0;

	double diagon,coef;
	double *ptrx,*ptry,*ptrx2,*ptry2;
	for (ord=0;ord<dim;ord++)
	{
      //2 Hacemos diagonal de x =1
		diagon=x[ord*dim+ord];
	    if (fabs(diagon)<1e-15) 
			return ord;
		ptry=y+dim*ord;
		for (i=0;i<dim;i++)
			*ptry++/=diagon;
		ptrx=x+dim*ord+ord;  
		for (i=ord;i<dim;i++)//para i<ord *ptrx=0,
			*ptrx++/=diagon;      

		//Hacemos '0' la columna ord salvo elemento diagonal:
		for (i=0;i<dim;i++)//Empezamos por primera fila
		{
			if (i==ord) continue;
			coef=x[dim*i+ord];//elemento ha hacer 0 
			if (fabs(coef)<1e-15) continue; //si es cero se evita
			ptry =y+i*dim;
			ptry2=y+ord*dim;
			for (j=0;j<dim;j++)
				*ptry++=*ptry-coef * (*ptry2++);
			ptrx =x+i*dim+ord;
			ptrx2=x+ord*dim+ord;
			for (j=ord;j<dim;j++)
				*ptrx++=*ptrx-coef * (*ptrx2++);
		}
	}//end ord
	//imprimematriz(x," Debe ser matriz UNO",dim);
	delete[] x;
	return dim;
}




//[y]=[[x]]*[b]   : se trata de hallar coeficientes b
void ecuacion_lineal(double *x,double *y,long dimension,double *b)
{
	double *y2=new double[dimension*dimension];
	long i,j;
	i=inversa(x,y2,dimension);
	if (i<dimension)
	{
		printf("ERROR, matriz de determinante 0");
		return;
	}
	for (i=0;i<dimension;i++)
	{
		b[i]=0.0;
		for (j=0;j<dimension;j++)
		{
			b[i]+=y2[i*dimension+j]*y[j];
		}
	}
	delete[] y2;
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


/*
El fichero conversion usa com coeficientes:

10	2	1.5	-1.2   1.2	0.7
20	-2	2	1.7	  -1.5	-0.3


Fichero conversion:
x'      	y'      	utmx	utmy
1	2	19	19.5
2	3	27.2	17.1
-0.068575479	2.881902566	19.75666004	23.71378356
-0.76542444	-1.540156825	8.530972936	16.96658658
-0.473697329	-2.309280377	10.36504082	13.4696128
0.293178473	2.990704381	22.28246024	21.54266394
1.792774576	1.96028481	19.57624765	19.37455151
-1.162187948	-1.873788343	8.315115602	16.55309044
1.425068335	-2.007799046	6.789833285	19.66915799
-0.580439184	0.216922646	8.642060345	22.34221903
-0.489869675	-2.123558379	9.95192668	14.22732516
0.483803035	-2.902352748	10.54475405	13.20475473
-1.593838672	-1.223207697	5.316005885	21.68654414
-0.45453316	-0.043316754	8.802978197	21.14355723
1.6777127	1.101291572	14.69587009	20.49685236
-0.248286376	2.939914014	19.01356029	24.98318176
1.091009597	-0.768872368	9.007547058	19.38467065
-0.733496311	-1.498608317	8.530621924	17.06182104
-0.413008224	-1.299394313	8.846091683	17.20568819
-1.109054165	2.701517603	11.87154964	32.01688029
0.759458947	0.843947373	13.36041056	19.97441004
1.059913241	1.399944795	16.02412021	19.77618678
1.744606313	1.643812735	17.63540181	19.86027466
-1.158136525	-2.846397438	11.43179961	11.52828576
0.890229886	1.516607607	16.33458443	19.88479745
-1.302325997	2.416181089	9.294921236	33.28890813
-1.577593311	-0.629986603	4.383726054	24.51631562
1.872357735	-0.237238927	8.688351142	22.38994612
0.538508008	0.513397386	12.01538918	19.94898727
-0.445862176	-1.089848369	8.649496625	17.96476176
-0.735147262	0.931082908	9.06326115	25.01786084
-0.281695751	2.622222321	17.20155125	24.98792375
-0.169576066	-1.986659852	9.813390951	14.72533755

Otro fichero conversion:
x'      	y'      	utmx	utmy
-0.062189	0.160221	579864	4445962
-0.150082	0.983699	571497	4537295
-0.975992	0.197574	502043	4449686
-0.986241	0.971929	501157	4535640
-0.74648	0.971842	521330	4535662
-0.467783	0.975873	544776	4536215
-0.86417	0.778253	511461	4514150
-0.663998	0.773137	528354	4513627
-0.353474	0.810661	554529	4517940
-0.284545	0.669861	560470	4502355
-0.523067	0.671041	540309	4502349
-0.722877	0.676436	523420	4502876
-0.833798	0.453951	514092	4478156
-0.640891	0.477826	530438	4480855
-0.480371	0.467603	544051	4479788
-0.242677	0.466324	564203	4479792
-0.687169	0.32312 	526576	4463668
-0.450054	0.322331	546721	4463678
-0.257426	0.345464	563065	4466366


*/
