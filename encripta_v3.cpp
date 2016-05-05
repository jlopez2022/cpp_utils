#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RANDMAX2 32768.0

void generacodigo(char *code,char *decode,int seed)
{
	srand(seed);
	long i,j;
	for (i=-128;i<128;i++)
	{
		code[i]=(char) i;
	}
	char k;
	for (i=127;i>=-128;i--)
	{
		j=(long) (((128+i)*rand()/RANDMAX2) - 128);
		k=code[i];
		if ((k==107)||(k==23)||(code[j]==107)||(code[j]==23))
			k=k;
		code[i]=code[j];
		code[j]=k;
		decode[(long) code[i]]=(char) i;
	}
	/*
	//Comprobacion:
	unsigned char sum1[256],sum2[256];
	memset(sum1,0,256);memset(sum2,0,256);
	for (i=-128;i<128;i++)
	{
		sum1[code[i]+128]++;
		sum2[decode[i]+128]++;
	}
	long errores=0;
	for (i=-128;i<128;i++)
	{
		long error=0;
		if (sum1[i+128]!=1)
		{
			printf("\nERROR %i en calculo de code",i);
			error=1;
		}
		if (sum2[i+128]!=1)
		{
			if (!error)
				printf("\nERROR %i en calculo de ",i);
			printf("decode ");
			error++;
		}
		if (decode[code[i]]!=(char) i)
		{
			if (!error)
				printf("\nERROR %i en calculo de ",i);
			printf("code-decode ");
			error++;
		}
		errores+=error;
	}
	printf("\nERRORES=%li",errores);
	//*/
}


void encripta(double *datin,double *datout,long datos,char *codigo)
{
	char *a,*b;
	a=(char *) datin;
	b=(char *) datout;
	long i,j;
	for(i=0;i<datos;i++)
	{
		for (j=0;j<8;j++)
		{
			b[j]=codigo[a[j]];
		}
		a+=8;
		b+=8;
	}
}

void encripta2(char *datin,char *datout,long datinsize)
{
	memcpy(datout,datin,datinsize);
	srand(777);
	char a;
	long i,pos;
	for (i=0;i<datinsize;i++)
	{
		pos=(long) ((1.0*rand()/RANDMAX2)*datinsize);
		a=datout[i];
		datout[i]=datout[pos];
		datout[pos]=a;
	}
}

void desencripta2(char *datin,char *datout,long datinsize)
{
	memcpy(datout,datin,datinsize);
	srand(777);
	long *posicion=new long[datinsize];
	long i;
	for (i=0;i<datinsize;i++)
	{
		posicion[i]=(long) ((1.0*rand()/RANDMAX2)*datinsize);
	}
	char a;
	long index=0,pos;
	for (i=datinsize-1;i>=0;i--)
	{
		pos=posicion[i];
		a=datout[i];
		datout[i]=datout[pos];
		datout[pos]=a;
	}
	delete[] posicion;
}


void comprime(char *filein,char *fileout,double *tipo)
{
	FILE *strin,*strout;
	strin=fopen(filein,"r");
	strout=fopen(fileout,"w");
	if (!strin || !strout)
	{
		printf("\nERROR en apertura de ficheros %s o %s",filein,fileout);getchar();getchar();return;
	}

	double x;
	unsigned char *ptr;
	while(!feof(strin))
	{
		ptr=(unsigned char *) &x;
		fscanf(strin,"%lg",&x);
		long i;
		for (i=0;i<8;i++)
			fputc(*ptr++,strout);
	}
	fclose(strin);fclose(strout);
}

void descomprime(char *filein,char *fileout,double *tipo)
{
	FILE *strin,*strout;
	strin=fopen(filein,"r");
	strout=fopen(fileout,"w");
	if (!strin || !strout)
	{
		printf("\nERROR en apertura de ficheros %s o %s",filein,fileout);getchar();getchar();return;
	}

	double x;
	unsigned char *ptr;
	while(!feof(strin))
	{
		ptr=(unsigned char *) &x;
		long i;
		for (i=0;i<8;i++)
		{
			*ptr++=(unsigned char) fgetc(strin);
		}
		fprintf(strout,"%lg ",x);
	}
	fclose(strin);fclose(strout);
}



void comprime_temp(char *filein,char *fileout)
{
	FILE *strin,*strout;
	strin=fopen(filein,"r");
	strout=fopen(fileout,"w");
	if (!strin || !strout)
	{
		printf("\nERRORen apertura de ficheros %s o %s",filein,fileout);getchar();getchar();return;
	}

	float x;
	while(!feof(strin))
	{
		fscanf(strin,"%g",&x);
		if (x<0) x-=0.5;
		else     x+=0.5;
		fputc((char) x,strout);
	}
	fclose(strin);fclose(strout);
}

void descomprime_temp(char *filein,char *fileout)
{
	FILE *strin,*strout;
	strin=fopen(filein,"rb");
	strout=fopen(fileout,"w");
	if (!strin || !strout)
	{
		printf("\nERRORen apertura de ficheros %s o %s",filein,fileout);getchar();getchar();return;
	}

	char c;
	while(!feof(strin))
	{
		c=fgetc(strin);
		fprintf(strout,"%i ",c);
	}
	fclose(strin);fclose(strout);
}


void comprime_temp(char *filein,char *fileout,char *code)
{
	FILE *strin,*strout;
	strin=fopen(filein,"r");
	strout=fopen(fileout,"w");
	if (!strin || !strout)
	{
		printf("\nERRORen apertura de ficheros %s o %s",filein,fileout);getchar();getchar();return;
	}

	float x;
	while(!feof(strin))
	{
		fscanf(strin,"%g",&x);
		if (x<0) x-=0.5;
		else     x+=0.5;
		fputc((char) code[(int) x],strout);
	}
	fclose(strin);fclose(strout);
}

void descomprime_temp(char *filein,char *fileout,char *decode)
{
	FILE *strin,*strout;
	strin=fopen(filein,"rb");
	strout=fopen(fileout,"w");
	if (!strin || !strout)
	{
		printf("\nERRORen apertura de ficheros %s o %s",filein,fileout);getchar();getchar();return;
	}

	char c;
	while(!feof(strin))
	{
		c=fgetc(strin);
		fprintf(strout,"%i ",decode[c]);
	}
	fclose(strin);fclose(strout);
}

int main()
{
	char code_m[256],*code=code_m+128;
	char decode_m[256],*decode=decode_m+128;
	generacodigo(code,decode,-777);


	FILE *strout;
	strout=fopen("double.txt","w");
	if (!strout)
	{
		printf("\nERRORen apertura de fichero double.txt");getchar();getchar();return -1;
	}
	long i;
	for (i=0;i<1024;i++)
	{
		float x;
		x=(float) (-125.0+250.0*rand()/RANDMAX2);
		fprintf(strout,"%g ",x);
	}
	fclose(strout);
	comprime_temp("double.txt","doubleout.txt",code);
	descomprime_temp("doubleout.txt","doubleout2.txt",decode);
	


	double ejemplo[8]={1.33123456789e-80,-7.773456789e200,0,1,-1,-1e300,1.11e300,1.111111111111111111111e199};
	double datout[8];
	encripta(ejemplo,datout,8,code);

	double datout2[8];
	encripta(datout,datout2,8,decode);

//	char c1[15]={"abcdefghijklmn"},c2[15],c3[15];
//	encripta2(   (char *) c1,(char *) c2,14);
//	desencripta2((char *) c2,(char *) c3,14);
//	encripta2(   (char *) ejemplo,(char *) datout,8*sizeof(double));
//	desencripta2((char *) datout,(char *) datout2,8*sizeof(double));

	printf("\n");
	for (i=0;i<8;i++)
		printf("%lg,",datout2[i]);


	long numdatos=56000;
	printf("\n===================\nEncriptando %li datos",numdatos);
	double datout10[56000],datout11[56000],datout12[56000];
	for (i=0;i<56000;i++)
		datout10[i]=(1.0/7.0*i*1025*i+1.111*i)*rand();
	char *ptr1,*ptr2;
	ptr1=(char *) datout10;
	ptr2=(char *) datout12;
	encripta2(   (char *) datout10,(char *) datout11, numdatos*sizeof(double));
	desencripta2((char *) datout11,(char *) datout12, numdatos*sizeof(double));

	long errores=0;
	for (i=0;i<numdatos;i++)
		if(datout10[i]!=datout12[i])
			errores++;
	printf("\nERRORES en encripta2=%li",errores);
	getchar();getchar();

	return 1;
}

