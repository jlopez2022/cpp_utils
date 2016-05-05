/* A sample program to illustrate setting up a serial port. */
/*
Abrir esta aplicacion DOS VECES:

en una se lee y en la otra se escribe
*/

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>

int main()
{
	printf("\n%li",CLOCKS_PER_SEC);
	char c,puerto[]="COM1";
	printf("\nPuerto COM1 o puerto COM2?");c=getche();printf("\n"); 
	if (c=='2') strcpy(puerto,"COM2");

    DCB dcb;
    HANDLE hCom;
    BOOL fSuccess;

	hCom = CreateFile( puerto,
                    GENERIC_READ | GENERIC_WRITE,
                    0,    // must be opened with exclusive-access
                    NULL, // no security attributes
                    OPEN_EXISTING, // must use OPEN_EXISTING
                    0,    // not overlapped I/O
                    NULL  // hTemplate must be NULL for comm devices
                    );

    if (hCom == INVALID_HANDLE_VALUE) 
    {
        // Handle the error.
        printf ("CreateFile %s failed with error %d.\n", puerto,GetLastError());
        return (1);
    }


   // Build on the current configuration, and skip setting the size
   // of the input and output buffers with SetupComm.

	fSuccess = GetCommState(hCom, &dcb);

	if (!fSuccess) 
	{
	  // Handle the error.
	  printf ("GetCommState failed with error %d.\n", GetLastError());
	  return (2);
	}

   // Fill in DCB: 57,600 bps, 8 data bits, no parity, and 1 stop bit.
	/*
	CBR_110  CBR_19200 
	CBR_300  CBR_38400 
	CBR_600  CBR_56000 
	CBR_1200 CBR_57600 
	CBR_2400 CBR_115200 
	CBR_4800 CBR_128000 
	CBR_9600 CBR_256000 
	CBR_14400 */

   dcb.BaudRate = CBR_4800;     // set the baud rate
   dcb.ByteSize = 8;             // data size, xmit, and rcv
   dcb.Parity = NOPARITY;        // EVENPARITYno parity bit
   dcb.StopBits = ONESTOPBIT;    // one stop bit
   dcb.fRtsControl = RTS_CONTROL_TOGGLE;

   fSuccess = SetCommState(hCom, &dcb);

   if (!fSuccess) {
      // Handle the error.
      printf ("SetCommState failed with error %d.\n", GetLastError());
      return (3);
   }

	COMMTIMEOUTS CommTimeouts;
	fSuccess = GetCommTimeouts( hCom, &CommTimeouts );

	if (!fSuccess) {
	  // Handle the error.
	  printf ("GetCommTimeouts failed with error %d.\n", GetLastError());
	  return (4);
	}

	CommTimeouts.WriteTotalTimeoutConstant   = 1;
	CommTimeouts.WriteTotalTimeoutMultiplier = 1;
	CommTimeouts.ReadTotalTimeoutConstant    = 0;
	CommTimeouts.ReadTotalTimeoutMultiplier  = 0;
	CommTimeouts.ReadIntervalTimeout         = 1;

	fSuccess = SetCommTimeouts( hCom, &CommTimeouts );

	if (!fSuccess) {
	  // Handle the error.
	  printf ("GetCommTimeouts failed with error %d.\n", GetLastError());
	  return (4);
	}
    printf ("Serial port %s successfully reconfigured.\n",puerto);
    unsigned char buffer[8] = { 0x61, 0x62, 0x63, 0x71, 0x72, 0x73 };
    unsigned char buffer2[1024] = { 0x01, 0x02, 0x03 };
    DWORD dwWritten,dwRead;

	printf("\nEscribir o Leer en puerto %s? ",puerto);c=getche();
	printf("\n");
	if (c=='E' || c=='e')
	{
		printf("\nEscribiendo, meter Q para salir\n");
		while (c!='Q')
		{
			c=getche();//printf(" ");
			if (!WriteFile(hCom, &c, 1, &dwWritten, NULL)) {
				printf ("Error during writing\n");
			}
		}
		return(0);
	}
	else
	{
		printf("\nLeyendo\n");
		FILE *str=fopen("NMEA.txt","wb");
		long tiempo,t2;tiempo=t2=clock();
		for (long i=0;i<10000;i++)
		{
			if (!ReadFile(hCom, &c, 1, &dwRead, NULL)) 
				printf ("\nError during reading");
			printf("%c",c);fprintf(str,"%c",c);
			t2=clock();
			//printf("# %li #",t2-tiempo);
			if ((t2-tiempo)>40)
			{
				printf("\n");
			}
			tiempo=t2;
		}
		fclose(str);
	}
   return (0);
}