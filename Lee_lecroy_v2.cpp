//Lee ficheros csv generados por osciloscopios lecroy sacando todo en un unico fichero de salida con los 4 canales
#include <stdio.h>
#define FILTRO 10
#define VMED 2.5
#define TRIG 1.0

void leelinea(FILE *str,char *lin)
{

	char *ptr=lin;

	do
	{
		*ptr=fgetc(str);
		if (*ptr==0x0A)
		{
			*ptr='\0';
			//fgetc(str);
			break;
		}
		ptr++;
	}while(!feof(str));
}

void main()
{
	char fichero[256]="C1v-i 50ms00000.csv";
	char linea[1024];


	FILE *strin,*strout,*strout2;
	strin  =fopen(fichero,"r");
	strout =fopen("out_filtered.txt","w");
	strout2=fopen("out_freq.txt","w");

	if(!strin)
	{
		printf("\nERROR");
		getchar();getchar();
	}

	long i;
	for (i=0;i<5;i++)
		leelinea(strin,linea);

	double t1,t2,x,xmed,DELTAT;
	fscanf(strin,"%lg",&t1);fscanf(strin,",%lg",&x);
	fscanf(strin,"%lg",&t2);fscanf(strin,",%lg",&x);
	double vini=x;
	DELTAT=(t2-t1)*FILTRO;
	long datosout=0;
	long estado;//0=antes de subir a vmax,1=despues de subir sobre vmax y antes de bajar a vmin
	double timeant=-1.0,time=0;//tiempo de anterior transicion. Tiempo actual
	double vmin=VMED-0.5*TRIG;
	double vmax=VMED+0.5*TRIG;
	if (vini>(vmin+vmax)/2.0)
		estado=1;
	else 
		estado=0;
	fprintf(strout, "Delta t= %lg ",DELTAT);
	fprintf(strout2,"Delta t= %lg ",DELTAT);
	fprintf(strout ,"\nTime\tVolts");
	fprintf(strout2,"\nTime\tDelta Time\tFreq");
	while(!feof(strin))
	{
		xmed=0;
		for (i=0;i<FILTRO;i++)
		{
			fscanf(strin,"%lg ",&t1);fscanf(strin,",%lg",&x);
			xmed+=x;
		}
		xmed/=FILTRO;datosout++;
		fprintf(strout,"\n%lg\t%lg",time,xmed);
		time+=DELTAT;
		if ((estado==0) && (xmed>vmax))
		{
			estado=1;
			fprintf(strout2,"\n%lg\t%lg\t%lg",time,time-timeant,1.0/(time-timeant));
			timeant=time;
		}
		if ((estado==1) && (xmed<vmin))
		{
			estado=0;
		}
		fprintf(strout,"\t%li",estado);
	}

	printf("\nFIN escritos %li datos",datosout);
	fclose(strin);fclose(strout);fclose(strout2);
	getchar();getchar();

}

