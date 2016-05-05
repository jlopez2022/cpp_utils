#include <stdio.h>

int main()
{
	float m[]={1e7,-1,1,0,0.1234};
	float x;
	long j=0;
	while (1)
	{
		printf("\nfloat:");
		scanf("%g",&x);
		//x=m[j++];
		long *i;
		i=(long *) &x;
		char *c;
		c=(char *) &x;
		printf(" = %X",*i);

	}
	return 1;
}