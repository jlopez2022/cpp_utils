#include <stdio.h>
#include <string.h>

long lee( void* vv)
{
	long i1;
	memcpy(&i1,vv,sizeof(long));
	return i1;
}

double lee_d( void* vv)
{
	double i1;
	memcpy(&i1,vv,sizeof(double));
	return i1;
}

struct s_control
{
	char line1[32];
	char line2[32];
}*control;
void line1_line2( void* vv)
{
	s_control* cc = (s_control* ) vv;
	long lon=strlen(cc->line1);
	memcpy(cc->line2,cc->line1,lon+1);//para que copie fin de caracter OJO!!
}


void main()
{
	long val=1777777;

	long i2;
	i2=lee((void *) &val);

	double dd=377e-177,d2;
	d2=lee_d((void *) &dd);


	i2=i2;
	control=new s_control[10];
	long i;
	for (i2=0;i2<10;i2++)
	{
		strcpy(control[i2].line2,"xxxxxxxxxxxxxxxxxxxxxxxxxx");
		for (i=0;i<31;i++)
			control[i2].line1[i]=(char) ('0'+i2);
		control[i2].line1[i]='\0';
	}
	for (i2=0;i2<10;i2++)
	{
		line1_line2( (void* ) &control[i2] );
	}
	i2=i2;
	delete control;
	i2=i2;
}


