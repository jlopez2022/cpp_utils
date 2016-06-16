//operador ?
#include <stdio.h>

void main()
{
	long i,j;
	i=-3;
	j= i<0 ? -i : i;
	i=3;
	j= i<0 ? -i : i;
	i=0;
	j= i<0 ? -i : i;
	i=10;
}