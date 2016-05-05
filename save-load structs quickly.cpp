#include <stdio.h>

struct s_uno
{
	long size;
	char a;
	float b;
	int c;
	double d;
};

void main()
{
	s_uno uno;
	uno.a=1;uno.b=2.222f;uno.c=38008;uno.d=3.3333333e-120;uno.size=sizeof(uno);


	FILE *str=fopen("out.txt","wb");
	char *ptr;
	ptr=(char *) &uno;
	long ptr_max;
	ptr_max=sizeof(uno);

	long i;
	for (i=0;i<ptr_max;i++)
	{
		fputc(ptr[i],str);
	}
	fclose(str);

	str=fopen("out.txt","rb");

	s_uno dos;
	ptr=(char *) &dos;
	for (i=0;i<ptr_max;i++)
	{
		ptr[i]=fgetc(str);
	}
	fclose(str);

	i=i;
}


