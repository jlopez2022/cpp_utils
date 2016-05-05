// InpoutTest.cpp : Defines the entry point for the console application.
//¡¡ATENCION: hay que meter inpout32.dll en WINDOWS (No hace falta con Dev C++)!!
//¡¡Atencion en el proyecto, Resource Files(ventana de la izquierda)
// añadir inpout32.lib
//Sirve para escribir palabras en el registro serie 74HC594

/*
378H PORT: In this address the CPU writes the data to be sent to the printer. It is an OUTPUT port. The eight data bits (D0-D7) are latched to appear in the output connector. In the table 2.1 we can see which pins of the connector are used.

Data Bits Table		
BIT	FUNCTION	PIN
D0	data 0		2
D1	data 1		3
D2	data 2		4
D3	data 3		5
D4	data 4		6
D5	data 5		7
D6	data 6		8
D7	data 7		9
	GND			18-25
In the MS-DOS operative system three parallel ports, called LPT1, LPT2 and LPT3, are supported. So we can find three addresses dedicated to these ports in the memory map of the PC. Let's study the addresses dedicated to LPT1 first. Each parallel port uses three addresses of the I/O map. For LPT1 these addresses are 378H, 379H and 37AH.

379H PORT: This is an INPUT port. These signals are used by the CPU to know the state of the printer. The location of the bits is listed in table 2.2. 

Status Bits Table		
BIT	FUNCTION	PIN
D0	not used	
D1	not used	
D2	not used	
D3	ERROR/		15
D4	SLCT/		17
D5	PE			12
D6	ACK/		10
D7	BUSY/		11

37AH PORT: In this port the computer writes the signals that control the printer. Therefore, it is an OUTPUT port, see table 2.3.

Control Bits Table
BIT	FUNCTION	PIN
D0	STROBE		1
D1	AUTO FD		14
D2	INIT/		16
D3	SLCT IN/	17
D4	Habilitation IRQ7	
D5	not used	
D6	not used	
D7	not used	

The computer has three LPTn ports. The addresses of the control and data signals for each LPTn port are listed below. Each port works in the same way that LPT1 does.
Table 2.4
Adresses of LPTn
PORT	DATA	STATUS	CONTROL
LPT1	378H	379H	37AH
LPT2	278H	279H	27AH
LPT3	3BCH	2BDH	3BEH
As you can see, the parallel port is able to control the IRQ7 interruption channel. This is a very powerful capability 
*/

//#include "stdafx.h" 
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
/* ----Prototypes of Inp and Outp--- */

short _stdcall Inp32(short PortAddress);
void _stdcall Out32(short PortAddress, short data);

/*--------------------------------*/
//Escribe:
//datos[0] se escribe en el pin 2
//datos[1] "       "            3
//datos[numdatos]  "            numdatos
void escribe_byte(int datos[8],int numdatos);//se pueden meter 16 bits en vez de 8 si se ponen los registros en serie

void main()
{

	int datos[8];
	datos[0]=0xC7;//A escribir los primeros 8 bits en primer  74HC594
	datos[1]=0x8E;//A escribir los primeros 8 bits en segundo 74HC594 
	datos[2]=0x1C;//En el tercero
	escribe_byte(datos,3);



	//char c;scanf("%c%c",&c,&c);
}

//Escribe:
//datos[0] se escribe en el pin 2
//datos[1] "       "            3
//datos[numdatos]  "            numdatos
//Usando el 78HC594 el pin 1 se conecta a SRCLK (los CLK invertidos=Hi)
//El pin 2,3,4 a SER de chips 1,2,3,...
void escribe_byte(int datos[8],int numdatos)
{
	int datout;
	for (int bit=0;bit<8;bit++)
	{
		datout=0;
		Out32(890,00);
		for (int j=0;j<numdatos;j++)
		{
			datout+=((datos[j]>>bit) & 1)<<j;
		}
		Out32(888,datout);
		Out32(890,01);
	}
}
