#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define YMAX 400
#define XMAX 600
#define TOP 20 //NO SALE ERROR ni aun subiendo el numero

__int16 (*face_d)[XMAX];
int compara_d(const void *p1,const void *p2)
{
	__int16 *a = &(* (__int16 *) p1);
	__int16 *b = &(* (__int16 *) p2);
	long a1=face_d[a[1]][a[0]]+face_d[a[5]][a[4]]-2*face_d[a[3]][a[2]];if (a1<0) a1=-a1;
	long b1=face_d[b[1]][b[0]]+face_d[b[5]][b[4]]-2*face_d[b[3]][b[2]];if (b1<0) b1=-b1;
	if (a1<b1) return 1; // ">" si es creciente, "<" si decreciente
	else       return -1;
}

long alto(__int16 a[6],__int16 (*face_d)[XMAX])
{
	long	a1=face_d[a[1]][a[0]]+face_d[a[5]][a[4]]-2*face_d[a[3]][a[2]];
	if (a1<0) return -a1;
	return a1;
}

void main()
{
	__int16 face1[YMAX][XMAX];
	face_d=face1;
	__int16 datos[TOP][6],*ptr;
	srand(0);
	long x,y;

	for (y=0;y<YMAX;y++)
		for (x=0;x<XMAX;x++)
			face1[y][x]=rand() % 256;

	long i;
	for (i=0;i<TOP;i++)
	{
		ptr=datos[i];
		*ptr++=rand() % XMAX;
		*ptr++=rand() % YMAX;
		*ptr++=rand() % XMAX;
		*ptr++=rand() % YMAX;
		*ptr++=rand() % XMAX;
		*ptr++=rand() % YMAX;
	}
	printf("\nLISTA:");
	for (i=0;i<TOP;i++)
		printf("\n%li:%li",i,alto(datos[i],face1));
	qsort(datos,TOP,6*sizeof(__int16),compara_d);
	long j;
	printf("\n\nLISTA ordenada:");
	__int16 ant=32767;
	long error2=0;
	for (i=0;i<TOP;i++)
	{
		j=face1[datos[i][1]][datos[i][0]]+face1[datos[i][5]][datos[i][4]]-2*face1[datos[i][3]][datos[i][2]];
		if (j<0) j=-j;
		printf("\n%li",j);if (ant<j) {printf(" ERROR!!!!");error2++;}
		ant=j;
	}
	printf("\n\n=== NUMERO TOTAL DE ERRORES=%li",error2); 

	printf("\n====FIN====");getchar();getchar();
}