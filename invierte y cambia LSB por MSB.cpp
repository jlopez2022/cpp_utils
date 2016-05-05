#include <stdio.h>
#define WORDS 23

typedef unsigned char byte;
void invierte(byte *code,long num);
void LSB_MSB(byte *code,long num);
void imprime(byte *code,long num);
void copy(byte *code1,byte *code2,long num);

void main()
{
	byte code[WORDS]={0xCF,0xCF,0xCF,0xCE,0xCF,0xCF,0xCF,0xCE,0xCE,0xCC,0xCD,0xC9,0xCF,0xCD,0xC7,0xCE,0xC6,0xBE,0xBC,0xBB,0xB9,0xB9,0xF2};
	byte code0[WORDS];
	copy(code,code0,WORDS);

	imprime(code,WORDS);printf("CODE");
	LSB_MSB(code,WORDS);
	imprime(code,WORDS);printf("LSB_MSB");
	copy(code0,code,WORDS);
	invierte(code,WORDS);
	imprime(code,WORDS);printf("INVIERTE");
	copy(code0,code,WORDS);
	LSB_MSB(code,WORDS);
	invierte(code,WORDS);
	imprime(code,WORDS);printf("LSB_MSB + INVIERTE");


	printf("\n=== FIN ===");
	getchar();getchar();
}


void invierte(byte *code,long num)
{
	long i;
	for (i=0;i<num;i++)
		code[i]=( ~code[i])&0xFF;
}

void LSB_MSB(byte *code,long num)
{
	long i,j;
	for (i=0;i<num;i++)
	{
		byte b=code[i],b2=0;
		for (j=0;j<8;j++)
		{
			b2=b2+(((b>>j)&0x1)<<(7-j));
		}
		code[i]=b2;
	}
}

void imprime(byte *code,long num)
{
	long i;
	printf("\n");
	for (i=0;i<num;i++) printf("%02X ",code[i]);
}

void copy(byte *code1,byte *code2,long num)
{
	long i;
	for (i=0;i<num;i++) code2[i]=code1[i];
}
