#include <stdio.h>

typedef enum {primera_vez,vez_posterior} VECES;
void llamada(void);

void main(void)
{
char c;
llamada();
llamada();
llamada();
scanf("%c%c",&c,&c);
}




void llamada(void)
{static VECES i=primera_vez; 
 if (i==primera_vez) printf("\nPrimera Vez");
	else printf("\nVez Sucesiva");
 i=vez_posterior;
}



