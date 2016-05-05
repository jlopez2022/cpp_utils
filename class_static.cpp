//Arbol móvil
#include <stdio.h>


class cclase
{
public:
	cclase *ptr;
	long index;
	static cclase *mclase;
	static long pclase;

	void create()
	{
		ptr=mclase+pclase++;
	}
	void ini(long dim)
	{
		mclase=new cclase[dim];
	}

};

cclase *cclase::mclase;

long cclase::pclase;

class cclase2 : public cclase
{
	long index2;
};

void main()
{
	cclase clase[10];
	long i;
	for (i=0;i<10;i++)
		clase[i].index=i;
	clase[0].ini(100);
	clase[0].pclase=10;
	clase[1].create();
	clase[2].create();
	clase[3].create();
	for (i=0;i<10;i++)
		printf("\n%li",clase[i].pclase);

	cclase2 clase2;
	clase2.create();
	printf("\n%li",clase[0].pclase);
	printf("\n%li",clase2.pclase);

	char c;scanf("%c%c",&c,&c);

}