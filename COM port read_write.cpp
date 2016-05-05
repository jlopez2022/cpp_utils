/* A sample program to illustrate setting up a serial port. */

#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
   DCB dcb1,dcb2;
   HANDLE hCom1,hCom2;
   BOOL fSuccess;

   hCom1 = CreateFile( "COM1",
                    GENERIC_READ | GENERIC_WRITE,
                    0,    // must be opened with exclusive-access
                    NULL, // no security attributes
                    OPEN_EXISTING, // must use OPEN_EXISTING
                    0,    // not overlapped I/O
                    NULL  // hTemplate must be NULL for comm devices
                    );

   if (hCom1 == INVALID_HANDLE_VALUE) 
   {
       // Handle the error.
       printf ("CreateFile-1 failed with error %d.\n", GetLastError());
       return (1);
   }


   hCom2 = CreateFile( "COM2",
                    GENERIC_READ | GENERIC_WRITE,
                    0,    // must be opened with exclusive-access
                    NULL, // no security attributes
                    OPEN_EXISTING, // must use OPEN_EXISTING
                    0,    // not overlapped I/O
                    NULL  // hTemplate must be NULL for comm devices
                    );

   if (hCom2 == INVALID_HANDLE_VALUE) 
   {
       // Handle the error.
       printf ("CreateFile-2 failed with error %d.\n", GetLastError());
       return (1);
   }


   // Build on the current configuration, and skip setting the size
   // of the input and output buffers with SetupComm.

   fSuccess = GetCommState(hCom1, &dcb1);

   if (!fSuccess) 
   {
      // Handle the error.
      printf ("GetCommState-1 failed with error %d.\n", GetLastError());
      return (2);
   }

   fSuccess = GetCommState(hCom2, &dcb2);

   if (!fSuccess) 
   {
      // Handle the error.
      printf ("GetCommState-2 failed with error %d.\n", GetLastError());
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

   dcb1.BaudRate = CBR_56000;     // set the baud rate
   dcb1.ByteSize = 8;             // data size, xmit, and rcv
   dcb1.Parity = EVENPARITY;        // no parity bit
   dcb1.StopBits = ONESTOPBIT;    // one stop bit
   dcb1.fRtsControl = RTS_CONTROL_TOGGLE;

   fSuccess = SetCommState(hCom1, &dcb1);

   if (!fSuccess) {
      // Handle the error.
      printf ("SetCommState-1 failed with error %d.\n", GetLastError());
      return (3);
   }

   dcb2.BaudRate = CBR_56000;     // set the baud rate
   dcb2.ByteSize = 8;             // data size, xmit, and rcv
   dcb2.Parity = EVENPARITY;        // no parity bit
   dcb2.StopBits = ONESTOPBIT;    // one stop bit
   dcb2.fRtsControl = RTS_CONTROL_TOGGLE;

   fSuccess = SetCommState(hCom2, &dcb2);

   if (!fSuccess) {
      // Handle the error.
      printf ("SetCommState-2 failed with error %d.\n", GetLastError());
      return (3);
   }

	COMMTIMEOUTS CommTimeouts1,CommTimeouts2;
	fSuccess = GetCommTimeouts( hCom1, &CommTimeouts1 );

	if (!fSuccess) {
	  // Handle the error.
	  printf ("GetCommTimeouts-1 failed with error %d.\n", GetLastError());
	  return (3);
	}

	CommTimeouts1.WriteTotalTimeoutConstant   = 1;
	CommTimeouts1.WriteTotalTimeoutMultiplier = 1;
	CommTimeouts1.ReadTotalTimeoutConstant    = 0;
	CommTimeouts1.ReadTotalTimeoutMultiplier  = 0;
	CommTimeouts1.ReadIntervalTimeout         = 1;

	CommTimeouts2.WriteTotalTimeoutConstant   = 1;
	CommTimeouts2.WriteTotalTimeoutMultiplier = 1;
	CommTimeouts2.ReadTotalTimeoutConstant    = 0;
	CommTimeouts2.ReadTotalTimeoutMultiplier  = 0;
	CommTimeouts2.ReadIntervalTimeout         = 1;

	fSuccess = SetCommTimeouts( hCom1, &CommTimeouts1 );

	if (!fSuccess) {
	  // Handle the error.
	  printf ("GetCommTimeouts-1 failed with error %d.\n", GetLastError());
	  return (3);
	}
    printf ("Serial port COM1 successfully reconfigured.\n");

	fSuccess = GetCommTimeouts( hCom2, &CommTimeouts2 );

	if (!fSuccess) {
	  // Handle the error.
	  printf ("GetCommTimeouts-2 failed with error %d.\n", GetLastError());
	  return (3);
	}

	CommTimeouts2.WriteTotalTimeoutConstant = 1;
	CommTimeouts2.WriteTotalTimeoutMultiplier = 1;

	fSuccess = SetCommTimeouts( hCom1, &CommTimeouts2 );

	if (!fSuccess) {
	  // Handle the error.
	  printf ("GetCommTimeouts-2 failed with error %d.\n", GetLastError());
	  return (3);
	}
    printf ("Serial port COM2 successfully reconfigured.\n");

   unsigned char buffer[8] = { 0x61, 0x62, 0x63, 0x71, 0x72, 0x73 };
   unsigned char buffer2[1024] = { 0x01, 0x02, 0x03 };
   DWORD dwWritten,dwRead;

   while (true) {

		if (!WriteFile(hCom1, buffer, 3, &dwWritten, NULL)) {
			printf ("Error during writing\n");
		}

		printf("\nWritten-1 %d ", dwWritten);
		for (long i=0;i<3;i++) printf("%X ",buffer[i]);
		
		Sleep(100);

		if (!ReadFile(hCom2, buffer2, 3, &dwRead, NULL)) {
			printf ("Error during reading-1\n");
		}

		printf("\nRead-1    %d ", dwRead);
		for (i=0;i<3;i++) printf("%X ",buffer2[i]);

		if (!WriteFile(hCom2, buffer+3, 3, &dwWritten, NULL)) {
			printf ("Error during writing-1\n");
		}

		printf("\nWritten-2 %d ", dwWritten);
		for (i=0;i<3;i++) printf("%X ",buffer[i+3]);
		
		Sleep(100);

		if (!ReadFile(hCom1, buffer2, 3, &dwRead, NULL)) {
			printf ("Error during reading-2\n");
		}

		printf("\nRead-2    %d ", dwRead);
		for (i=0;i<3;i++) printf("%X ",buffer2[i]);

		if (!ReadFile(hCom1, buffer2, 3, &dwRead, NULL)) {
			printf ("Error during reading-3\n");
		}

		printf("\nRead-3    %d ", dwRead);
		for (i=0;i<3;i++) printf("%X ",buffer2[i]);

		Sleep(1000);
   }	

   return (0);
}