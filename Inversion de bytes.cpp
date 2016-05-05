#include <stdio.h>


int main()
{
	/*char texto1[]="texto de prueba 11 22 33  44 xxx zzz yyy XXX YYY ... ,,, /// \t\t\t\t";
	char texto2[1024]; strcpy(texto2,texto1);
	quita_duplicado(texto2);
	return 0;*/

	int ii;unsigned char cc; 
	cc=0x11;ii=(~cc)&0xFF;printf("\n%04X %04X",cc,ii);
	cc=255 ;ii=(~cc)&0xFF;printf("\n%04X %04X",cc,ii);
	cc=0x55;ii=(~cc)&0xFF;printf("\n%04X %04X",cc,ii);
	cc=0xAF;ii=(~cc)&0xFF;printf("\n%04X %04X",cc,ii);
	cc=0x00;ii=(~cc)&0xFF;printf("\n%04X %04X",cc,ii);
	cc=0x5F;ii=(~cc)&0xFF;printf("\n%04X %04X",cc,ii);
	cc=0xF5;ii=(~cc)&0xFF;printf("\n%04X %04X",cc,ii);
	getchar();getchar();
	return 0;
}