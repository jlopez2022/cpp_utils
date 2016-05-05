#include <stdio.h>
#include <string.h>

typedef unsigned char uchar;

class c_prueba
{
public:
	uchar a[10],b[10];
	void ini() { for(int i=0;i<10;i++) {a[i]=100+i;b[i]=200+i;} }
	void metedato0(uchar **a1) { *a1=&a[0]; }
	void metedato1(uchar **a1) { *a1=&b[0]; }
};

int main()
{
	c_prueba prueba1;
	prueba1.ini();
	uchar *a1=NULL,*a2=NULL;
	prueba1.metedato0(&a1);
	prueba1.metedato1(&a2);

	a1[0]=a1[0];
	for(int i=0;i<10;i++) 
		printf("%i %i\n",a1[i],a2[i]);
	printf("==== FIN ====\n");getchar();getchar();
	return 1;
}