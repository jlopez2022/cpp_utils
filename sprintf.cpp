//sirve para escribir con formato en cadenas de caracteres
#include <stdio.h>
#include <stdlib.h>

void mete(char a,char &c)
{
	int i,j;c=0;
	for (i=0;i<8;i++)
	{
		j=(a>>i) & 1;//bit a meter
		if (i<8) c+=j<<i;
	}
}

int main()
{


	int i;
	char a[12]={0xBF,0x00 ,0x90 ,0x31 ,0xCF ,0x95 ,0x7A ,0x59 ,0xE5 ,0xD2 ,0xBF ,0x2C}; 
	char buffer[28];
	for (i=0;i<12;i++)
		sprintf(buffer+2*i,"%02X",a[i]);
//	sprintf(buffer+2*i,"\0",a[i]);
	printf("\nLinea=%s\n",buffer);


	char c;
	for (i=0;i<12;i++)
	{
		mete(a[i],c);
		printf("%02X ",c);
	}
	printf("\nFIN");getchar();getchar();
}

