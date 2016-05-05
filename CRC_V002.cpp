//V002: añado CRC de Heli

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LON1 5
#define CRC8_POLY 0x8C // X^8 + X^5 + X^4 + X^0 bit reversed



typedef unsigned char byte;

byte ActualizaCRC8 (byte Dato, byte CRC8)
{
  byte Cont;
   
  for (Cont = 0; Cont < 8; Cont++)
  {
    if ((CRC8 ^ Dato) & 0x01) CRC8 = (CRC8 >> 1 ) ^ CRC8_POLY;
    else CRC8 >>= 1;
    Dato >>= 1;
  }
  return CRC8;
}

byte HallaCRC8_2(byte *u, byte size)
{
	byte crc=0x0;
	int i,j;
  
    for(j=0; j< size; j++)
    {
         crc = crc ^ u[j];
         for (i=0; i<8; i++)
         if (crc & 0x01)	crc = (crc>>1) ^ CRC8_POLY;
         else				crc = crc >> 1;
    }
	return crc;
}


unsigned __int16 HallaCRC16(unsigned __int16 *u, unsigned __int16 size)
{
	unsigned __int16 crc=0xFFFF,i,j;
  
    for(j=0; j< size; j++)
    {
         crc = crc ^ u[j];
         for (i=0; i<16; i++)
         if (crc & 0x0001)	crc = (crc>>1) ^ 0x8408;
         else				crc = crc >> 1;
    }
	return crc;
}


byte alea[256]={193,35,160,0,58,115,27,61,82,44,55,241,66,57,83,235,179,166,168,45,129,15,186,153,224,
		        94,187,28,19,198,169,223,64,219,5,200,67,46,139,17,222,132,199,39,164,119,13,53,42,212,
				184,221,150,182,70,59,60,163,137,133,214,18,118,203,85,154,80,238,188,120,237,253,192,
				101,251,246,158,43,10,148,210,220,135,165,1,68,102,30,107,180,93,29,74,73,161,146,75,
				175,145,157,228,38,20,96,254,121,24,190,185,114,99,78,100,128,152,12,171,195,14,159,37,
				234,201,216,242,191,181,6,34,98,31,136,149,162,142,206,218,239,208,111,95,130,202,194,
				2,205,226,71,110,156,155,126,151,230,183,240,56,81,172,177,88,215,232,26,32,124,50,122,
				72,147,252,106,63,21,244,117,49,231,104,112,196,131,245,207,92,97,22,123,91,211,25,3,167,
				189,143,213,116,217,65,90,229,33,247,125,178,8,89,84,51,77,173,41,236,9,255,140,204,243,
				227,174,48,170,127,86,36,144,209,11,4,16,47,113,79,7,134,103,248,69,23,225,62,197,87,108,
				52,40,109,249,54,176,76,250,233,138,105,141};

//LON1 es la longitud de u[] menos 1
byte hallaCRC(byte *u)
{
	int i;
	byte CRC=0;
	for (i=0;i<LON1;i++)
	{
//		CRC^=u[i];
//		CRC+=u[i];
//		CRC=alea[(CRC+u[i])&0xFF];
//		CRC=ActualizaCRC8 (u[i], CRC);//EL MEJOR
	}
	CRC=HallaCRC8_2(u,LON1);//mismo resultado que ActualizaCRC8 pero más comprimido
	return CRC;
}
void poneCRC(byte *u)
{
	u[LON1]=hallaCRC(u);
}

//si hay un byte distinto devuelve 1, si no devuelve 0
int miraerror(byte *vector1,byte *vector2)
{
	int i,ret=0;
	if (vector1[LON1]!=vector2[LON1]) return 0;
	for (i=0;i<LON1;i++)
		if (vector1[i]!=vector2[i]) ret=1;
	return ret;
	
}
void copia(byte *vector1,byte *vector2)
{
	int i;
	for (i=0;i<LON1;i++)
		vector2[i]=vector1[i];
	
}


int main()
{
    double  inicio,fin;inicio=clock();
	FILE *report=fopen("report.txt","a");
	if (!report) return -1;
	fprintf(report,"\n==============================================");
//	fprintf(report,"\nExclusive OR ^:");
//	fprintf(report,"\nSuma sin carry +:");
//	fprintf(report,"\nUso de indices:");
	fprintf(report,"\nRutina CRC8-2:");
	byte vector1[LON1+1]={0xA5,0x54,0x81,0x00,0};
	byte vector2[LON1+1];
	poneCRC(vector1);

	long i,j,error,ntests;
	//Comprobación aleatoria
	error=0;ntests=0;
	for (i=0;i<200000;i++)
	{
		for (j=0;j<LON1;j++)
			vector2[j]=rand()&0xFF;
		poneCRC(vector2);
		if (miraerror(vector1,vector2)) 
		{
			error++;
			printf("\nERROR %i vector2=",error);
			for (j=0;j<LON1;j++)
				printf(" %X",vector2[j]);
		}
		ntests++;
		if(i % 2000 ==0) printf("\nChequeado %i./.",i/2000);
	}
	printf("\n=================================================");
	printf(        "\nLanzados %i tests aleatorios, erroneos %i:       \t 1 cada %g",ntests,error,1.0*ntests/error);
	fprintf(report,"\nLanzados %i tests aleatorios, erroneos %i:       \t 1 cada %g",ntests,error,1.0*ntests/error);

	//Comprobación un error en 1 bit en cada posición
	error=0;ntests=0;
	for (i=0;i<8;i++)
	{
		byte err=1<<i;
		for (j=0;j<LON1;j++)
		{
			copia(vector1,vector2);
			vector2[j]=vector2[j]^err;
			poneCRC(vector2);
			if (miraerror(vector1,vector2)) 
			{
				error++;
				printf("\nERROR %i vector2=",error);
				for (j=0;j<LON1;j++)
					printf(" %X",vector2[j]);
			}
			ntests++;
		}
	}
	printf("\n=================================================");
	printf(        "\nLanzados %i tests 1 bit, erroneos %i:            \t 1 cada %g",ntests,error,1.0*ntests/error);
	fprintf(report,"\nLanzados %i tests 1 bit, erroneos %i:            \t 1 cada %g",ntests,error,1.0*ntests/error);

	//Comprobación dos bits erroneos de la misma columna, uno en cada vector
	error=0;ntests=0;
	int j2;
	for (i=0;i<8;i++)
	{
		byte err=1<<i;
		for (j=0;j<LON1-1;j++)
		{
			for (j2=j+1;j2<LON1;j2++)
			{
				copia(vector1,vector2);
				vector2[j]=vector2[j]^err;
				vector2[j2]=vector2[j2]^err;
				poneCRC(vector2);
				if (miraerror(vector1,vector2)) 
				{
					error++;
					printf("\nERROR %i vector2=",error);
					for (j=0;j<LON1;j++)
						printf(" %X",vector2[j]);
				}
				ntests++;
			}
		}
	}
	printf("\n=================================================");
	printf(        "\nLanzados %i tests 2 bits 1 posicion, erroneos %i:\t 1 cada %g",ntests,error,1.0*ntests/error);
	fprintf(report,"\nLanzados %i tests 2 bits 1 posicion, erroneos %i:\t 1 cada %g",ntests,error,1.0*ntests/error);

	//Comprobación un error en 2 bits aleatorios
	error=0;ntests=0;
	for (i=0;i<200000;i++)
	{
		copia(vector1,vector2);
		byte err;
		int ix;
		ix=rand() % LON1;
		err=1<<(rand() %8);
		vector2[ix]^=err;
		ix=rand() % LON1;
		err=1<<(rand() %8);
		vector2[ix]^=err;
		poneCRC(vector2);
		if (miraerror(vector1,vector2)) 
		{
			error++;
			/*
			printf("\nERROR %i vector2=",error);
			for (j=0;j<LON1;j++)
				printf(" %X",vector2[j]);
			*/
		}
		ntests++;
	}
	printf("\n=================================================");
	printf(        "\nLanzados %i tests 2 bits aleatorios, erroneos %i:\t 1 cada %g",ntests,error,1.0*ntests/error);
	fprintf(report,"\nLanzados %i tests 2 bits aleatorios, erroneos %i:\t 1 cada %g",ntests,error,1.0*ntests/error);

	//Comprobación un error en 3 bits aleatorios
	error=0;ntests=0;
	for (i=0;i<200000;i++)
	{
		copia(vector1,vector2);
		byte err;
		int ix;
		ix=rand() % LON1;
		err=1<<(rand() %8);
		vector2[ix]^=err;

		ix=rand() % LON1;
		err=1<<(rand() %8);
		vector2[ix]^=err;

		ix=rand() % LON1;
		err=1<<(rand() %8);
		vector2[ix]^=err;

		poneCRC(vector2);
		if (miraerror(vector1,vector2)) 
		{
			error++;
			/*
			printf("\nERROR %i vector2=",error);
			for (j=0;j<LON1;j++)
				printf(" %X",vector2[j]);
			*/
		}
		ntests++;
	}
	printf("\n=================================================");
	printf(        "\nLanzados %i tests 3 bits aleatorios, erroneos %i:\t 1 cada %g",ntests,error,1.0*ntests/error);
	fprintf(report,"\nLanzados %i tests 3 bits aleatorios, erroneos %i:\t 1 cada %g",ntests,error,1.0*ntests/error);
	fin=clock();
	printf("\nDuracion=%lg",fin-inicio);
	fprintf(report,"\nDuracion=%lg",fin-inicio);
	fclose(report);
	getchar();getchar();
	return 0;
}

/*
Resultados:
==============================================
Exclusive OR:
Lanzados 200000 tests aleatorios, resultando erroneos 748:			1 cada 267.38
Lanzados 40 tests 1 bit, resultando erroneos 0:                 	1 cada 1.#INF
Lanzados 32 tests 2 bits 1 posicion, resultando erroneos 8: 		1 cada 4
Lanzados 200000 tests 2 bits aleatorios, resultando erroneos 20006: 1 cada 9.997
Lanzados 200000 tests 3 bits aleatorios, resultando erroneos 0: 	1 cada 1.#INF
Duracion=844
Duracion=234 (2ª vez se ejecuta)
==============================================
SUMA sin carry:
Lanzados 200000 tests aleatorios, resultando erroneos 781 			1 cada 256.082
Lanzados 40 tests 1 bit, resultando erroneos 0 						1 cada 1.#INF
Lanzados 44 tests 2 bits 1 posicion, resultando erroneos 6 			1 cada 7.33333
Lanzados 200000 tests 2 bits aleatorios, resultando erroneos 8558 	1 cada 23.3699
Lanzados 200000 tests 3 bits aleatorios, resultando erroneos 1491 	1 cada 134.138
Duracion=844
Duracion=234 (2ª vez se ejecuta)
==============================================
Uso de indices:
Lanzados 200000 tests aleatorios, resultando erroneos 781 			1 cada 256.082
Lanzados 40 tests 1 bit, resultando erroneos 0 						1 cada 1.#INF
Lanzados 74 tests 2 bits 1 posicion, resultando erroneos 1 			1 cada 74
Lanzados 200000 tests 2 bits aleatorios, resultando erroneos 767 	1 cada 260.756
Lanzados 200000 tests 3 bits aleatorios, resultando erroneos 775 	1 cada 258.065
Duracion=844
Duracion=234 (2ª vez se ejecuta)
==============================================
Rutina CRC8 de Heli:
Lanzados 200000 tests aleatorios, resultando erroneos 841 			1 cada 237.812
Lanzados 40 tests 1 bit, resultando erroneos 0 						1 cada 1.#INF
Lanzados 80 tests 2 bits 1 posicion, resultando erroneos 0 			1 cada 1.#INF
Lanzados 200000 tests 2 bits aleatorios, resultando erroneos 0 		1 cada 1.#INF
Lanzados 200000 tests 3 bits aleatorios, resultando erroneos 0 		1 cada 1.#INF
Duracion=1078
Duracion=1094
Duracion=484 (2ª vez se ejecuta) 
==============================================
Rutina CRC8-2:
Lanzados 200000 tests aleatorios, erroneos 841:       				1 cada 237.812
Lanzados 40 tests 1 bit, erroneos 0:            					1 cada 1.#INF
Lanzados 80 tests 2 bits 1 posicion, erroneos 0:					1 cada 1.#INF
Lanzados 200000 tests 2 bits aleatorios, erroneos 0:				1 cada 1.#INF
Lanzados 200000 tests 3 bits aleatorios, erroneos 0:				1 cada 1.#INF
Duracion=1031
==============================================
Rutina CRC8-2:
Lanzados 200000 tests aleatorios, erroneos 841:       				1 cada 237.812
Lanzados 40 tests 1 bit, erroneos 0:            					1 cada 1.#INF
Lanzados 80 tests 2 bits 1 posicion, erroneos 0:					1 cada 1.#INF
Lanzados 200000 tests 2 bits aleatorios, erroneos 0:				1 cada 1.#INF
Lanzados 200000 tests 3 bits aleatorios, erroneos 0:				1 cada 1.#INF
Duracion=453
*/