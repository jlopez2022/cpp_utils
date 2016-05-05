#include <windows.h>
#include <stdio.h>

int main()
{
 HANDLE
 hCom1=CreateFile("COM4",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,0),
 hCom2=CreateFile("COM3",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,0);
/*
 COMMTIMEOUTS timeouts;
 timeouts.ReadIntervalTimeout = 1;
 timeouts.ReadTotalTimeoutMultiplier = 1;
 timeouts.ReadTotalTimeoutConstant = 1;
 timeouts.WriteTotalTimeoutMultiplier = 1;
 timeouts.WriteTotalTimeoutConstant = 1;
 if (!SetCommTimeouts(hCom1, &timeouts)) { printf("\nError timeout puerto-1");getchar();getchar(); return-1;}
 if (!SetCommTimeouts(hCom2, &timeouts)) { printf("\nError timeout puerto-2");getchar();getchar(); return-1;}
*/
 SetupComm(hCom1,4048,4048);
 SetupComm(hCom2,4048,4048);

 DCB dcb;
 ZeroMemory(&dcb,sizeof(dcb));
 dcb.DCBlength=sizeof(dcb);
 BuildCommDCB("baud=9600 parity=N data=8 stop=1",&dcb);
 if (SetCommState(hCom1,&dcb)) printf("\nAbierto puerto-1");
 else { printf("\nError SetCommState puerto-1");getchar();getchar(); return-1;}
 if (SetCommState(hCom2,&dcb)) printf("\nAbierto puerto-2");
 else { printf("\nError SetCommState puerto-2");getchar();getchar(); return-1;}

 DWORD res;
 char dato2[4048];
 
 WriteFile(hCom1,"Hey, RS232!",11,&res,NULL);
 printf("\nEnviados  %li bytes y espero 50ms ",res); Sleep(50);
 ReadFile( hCom2,dato2,11,&res,NULL);
 printf("Recibidos %li bytes",res);
 
 WriteFile(hCom1,"Hey, RS232!",11,&res,NULL);
 printf("\nEnviados  %li bytes y espero 100ms ",res); Sleep(100);
 ReadFile( hCom2,dato2,11,&res,NULL);
 printf("Recibidos %li bytes",res);
 
 WriteFile(hCom1,"Hey, RS232!",11,&res,NULL);
 printf("\nEnviados  %li bytes y espero 200ms ",res); Sleep(200);
 ReadFile( hCom2,dato2,11,&res,NULL);
 printf("Recibidos %li bytes",res);

 WriteFile(hCom1,"Hey, RS232!",11,&res,NULL);
 printf("\nEnviados  %li bytes y espero 500ms ",res); Sleep(500);
 ReadFile( hCom2,dato2,11,&res,NULL);
 printf("Recibidos %li bytes",res);
 
 CloseHandle(hCom1);
 CloseHandle(hCom2);
 printf("\n===FIN===");
 getchar();
 getchar();


 return 0; 
}