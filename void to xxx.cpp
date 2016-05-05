#include <stdio.h>
#include <string.h>

long lee( void *v1)
{
	long i1;
	memcpy(&i1,v1,sizeof(long));
	return i1;
}

double lee_d( void *v1)
{
	double i1;
	memcpy(&i1,v1,sizeof(double));
	return i1;
}

void main()
{
	long val=1777777;

	long ii;
	ii=lee((void *) &val);

	double dd=377e-177;
	dd=lee_d((void *) &dd);
	ii=ii;
}


