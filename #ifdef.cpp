//buffer circular de longitud LON
#include <stdio.h>
#include <math.h>

#define MICROPIC  //desactivar esta línea para simular al micropic


#ifdef MICROPIC
	#include "#ifdef.h"
#else
	int leeanalog(int channel)
	{
		return 7000+channel;
	}
	int kk=777;
#endif



void main()
{

	int i;
	i=leeanalog(7);

	
	#ifdef MICROPIC
		printf("\nConectado a Micropic");
	#else
		printf("\nMicropic no conectado. Simulando Micropic");
	#endif
	
	
	printf("\ni =%li",i);
	printf("\nkk=%li",kk);
	getchar();getchar();
}