/*
  La version V305 reunifica las tareas PERO incorpora CFile->close() y session.Close():ver F2_lee_bloque(void* vv)
  La version V304 divide el tiempo de espera en 2 para que no hallan mas de 14 tareas cada vez.
  Ademas halla el tiempo para cada paquete
  La version V303 pone F3_espera() en el sitio adecuado entre lanzamiento y captura.
  La version V302 mete las tareas deteached y hace la espera en el lugar adecuado ¡QUE BIEN VA!
  OJO: la V301 funciona PERO no hace la espera en el sitio adecuado
  La version V301 incluye multitarea y simbolos. OJO: Web_a_file_V301 sin pru va bien
  Problemas que no crea mas de 14 tareas. Ver si meter PTHREAD_CREATE_DETACHED o una espera entre creacion y creacion
  Consejos para V302: http://publib.boulder.ibm.com/iseries/v5r2/ic2928/index.htm?info/rzahw/rzahwe11rx.htm
 
1. Crear como Console application con MFC activado.
2. Incluir StdAfx.cpp,y StdAfx.h en el directorio a compilar 
   Ver: http://visualcpp.net/index.php?qID=35
3. Meter en Project->settings->linker: pthreadVC2.lib 
4. Ademas deben estar pthread.h y sched.h en el directorio y pthreadVC2.dll y .lib 
5. Project->setting->C/C++,code generation, use runtime libray: multithreating dll
6. EN PROJECT->SETTING->LINK->OUTPUT en RESERVE poner: 0x1000000  (=16Mb)

7. Bajar pthtread: .h,dll y .lib de: ftp://sourceware.org/pub/pthreads-win32/dll-latest/
*/

#pragma once
//#define _MULTI_THREADED
#include "stdafx.h"
#include <stdio.h>
#include <afxinet.h>//Read(), CInternetSession
#include <conio.h>	//_kbhit
#include "pthread.h"//libreria de hilos 
//1.0 Zona inicializacion
#define D_BUFFER_SIZE 4000 
#define D_URL_SIZE 2000
#define D_SYMBOL_SIZE 14
#define D_MAX_SYMBOLS 100 
//Zona de captura
#define D_TIMEOUT_MS 6200 //debe ser inferior a 3xD_TIEMPO_REFRESCO/4 (1+3 reintentos)
//2.0 Zona espera
#define D_TIEMPO_REFRESCO 20000//Debe ser >= 10m Segundos mínimos a esperar entre una lectura de bloques
//Zona main()
#define D_MAX_LECTURAS 43200 //24*3600/20= 43200 paquetes 

CWinApp theApp;
using namespace std;



//===1.0 Zona inicializacion 
//===1.2 Struct que contiene los paquetes
struct s_lee_url
{
	char buffer[D_BUFFER_SIZE];
	char url[D_URL_SIZE];
	volatile __int16 estado;//0,1,2=buffer vacio/lleno/llenando. volatile para que pueda leerse desde dentro y fuera de la thread
	__int32 nombre_bloque;
	long tiempo_captura;
	__int32 veces;//Veces que se efectua transaccion (buffer lleno)
}*g_lee;
long g_bloques;//Tamaño de g_lee[]
//===1.3 //Si retorno no igual a 0 terminar.
long F10_inicializa(void); //Halla el numero de simbolos;
//===1.4 Lee los simbolos
void F11_inicializa(long last_simbolos); 

//===2.0 ZONA lectura 
//===2.1.writer: usado por lee_bloque
//long getURLFile(const char *url, char *buffer, long max_bytes, char *errorMessage); 
//static size_t writer(void *vdata, size_t size, size_t nmemb, void *vbuffer_in); 
//===2.2. lee_bloque: rutina principal
static void* F2_lee_bloque(void* vv);//=pull_one_curl() 

//===3.0 Espera hasta 3000
//===3.1 Segundo desde las 0h de hoy
long Fahora(void);
//===3.2 Refresca tiempo_actual y espera hasta D_TIEMPO_REFRESCO segundos
void F3_espera(long &tiempo_actual)
{
	long tant=tiempo_actual;tiempo_actual=Fahora();
	tant=D_TIEMPO_REFRESCO-1000*(tiempo_actual-tant); if (tant<0) tant=0;
	Sleep((DWORD) tant);
	tiempo_actual=Fahora();
}

//===4. Rutinas que usan los datos almacenadoes en curl
//void F4_sacadatos(FILE *strout,char *ptr) { fprintf(strout,"%s",ptr); }



int _tmain()
{
	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		printf("Fatal Error: MFC initialization failed");getchar();getchar();
		return -1;
	}

	FILE *strout;
	strout=fopen("output.txt","wb");//CAMBIAR a "a" ? el 'b' es porque mete un 0x0D si no.
	if (!strout) {	printf("\nError abriendo fichero output.txt");getchar();getchar();return 0; }

	//1.0 Inicializo:
	long simbolos;
	simbolos=F10_inicializa();//Halla numero de simbolos y g_bloques, numero de bloques
	if (!simbolos)
		return -1;
	g_lee=new s_lee_url[g_bloques]; 
	printf("\nEl numero maximo de tareas es %li y hay %li tareas",PTHREAD_THREADS_MAX,g_bloques);
	long tiempo_actual,tiempo_actual0;tiempo_actual=tiempo_actual0=Fahora();
	long last_simbolos;last_simbolos=simbolos % D_MAX_SYMBOLS;//numero de simbolos del ultimo bloque
	F11_inicializa(last_simbolos);
	fprintf(strout,"\nSymbols: %li Bloques: %li",simbolos,g_bloques);
	printf(        "\nSymbols: %li Bloques: %li",simbolos,g_bloques);

	//===Bucle principal===
	pthread_t *tid=new pthread_t[g_bloques];
	pthread_attr_t attr;
    pthread_attr_init(&attr);//Create a default thread attributes object
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);//La hace deteachable

	long lectura_nbloques;//Veces que se ha lanzado lectura de todos los bloques
	long num_iniciados=0,num_vaciados=0,num_errores1=0,num_errores2=0;
	for (lectura_nbloques=0;lectura_nbloques<D_MAX_LECTURAS;lectura_nbloques++)
	{

		//2.0 Lanzar las lecturas de bloques vacios:
		int error;
		long bloq;
		printf("\nINI tareas:");
		for (bloq=0;bloq<g_bloques;bloq++)
		{
			if (g_lee[bloq].estado==0)//vacio		//LEE ESTADO
			{
				g_lee[bloq].estado=2;				//ESTADO LLENANDO
				error = pthread_create(&tid[bloq],&attr,F2_lee_bloque,(void *) &g_lee[bloq]);//NO EXISTE F_PULL!!!!!
				if (0!=error)//error
				{	
					printf(" %4liERROR%li",bloq,error);
					num_errores1++;
					g_lee[bloq].estado=0;			//ESTADO VACIO
				}
				else
				{
					printf(" %4li",bloq);
				}
				num_iniciados++;
			}
//			if (bloq % 14 == 13) 
//					F3_espera(tiempo_actual);		//Lanzamiento de espera
		}
		//if (lectura_nbloques==(D_MAX_LECTURAS-1))
		F3_espera(tiempo_actual);
		printf("\nFIN tareas:");
		for (bloq=0;bloq<g_bloques;bloq++)
		{
			if (g_lee[bloq].estado==1)//lleno o error//LEE ESTADO
			{
				if(g_lee[bloq].buffer[0])
				{
					printf(" %4li",bloq);
					long bsize;bsize=strlen(g_lee[bloq].buffer);
					fprintf(strout,"\n#Tiempo_captura= %li size= %li",g_lee[bloq].tiempo_captura,bsize);
					fprintf(strout,"\n%s",g_lee[bloq].buffer);// o hacer estimacion....
					g_lee[bloq].veces++;//incremento veces que se ha llenado y vaciado el buffer
					num_vaciados++;
				}
				else//hubo error
					num_errores2++;
				g_lee[bloq].estado=0;				//ESTADO VACIO
			}
			else//llenando.  
			{
				//printf("\nTAREA#%li:llenando",i2);
			}
		}
		printf("\nFIN lectura %li iniciados:%li vaciados:%li errores lanzado:%li errores url:%li",lectura_nbloques,num_iniciados,num_vaciados,num_errores1,num_errores2);
		//num_iniciados=num_vaciados=num_errores1=num_errores2=0;
		if(_kbhit())
			break;
	}
	//===FIN Bucle principal===

	//Parar tareas:
	tiempo_actual=Fahora();
	printf("\n\n==== FIN ======\n");
	printf("\nTiempo inicial=%li Tiempo Final=%li Total=%li",tiempo_actual,tiempo_actual0,tiempo_actual-tiempo_actual0);
	printf("\nFIN lectura %li iniciados:%li vaciados:%li errores lanzado:%li errores url:%li",lectura_nbloques,num_iniciados,num_vaciados,num_errores1,num_errores2);
	fprintf(strout,"\n\n==== FIN ======\n");
	fprintf(strout,"\nTiempo inicial=%li Tiempo Final=%li Total=%li",tiempo_actual,tiempo_actual0,tiempo_actual-tiempo_actual0);
	fprintf(strout,"\nFIN lectura %li iniciados:%li vaciados:%li errores lanzado:%li errores url:%li",lectura_nbloques,num_iniciados,num_vaciados,num_errores1,num_errores2);
	fclose(strout);
	Sleep((DWORD) (D_TIMEOUT_MS));
	delete[] tid;
	delete[] g_lee;
	printf("\n=== FIN FIN FIN ===");getchar();getchar();
	return 0;
}
//====================== end main ===============================
//===1.3 
long F10_inicializa(void) //Halla el numero de simbolos;
{
	FILE *strin;
	//1.0 Compruebo que existe el fichero y veo la longitud
	strin=fopen("simbolos.txt","r");
	if (!strin)
	{
		printf("\nError abriendo fichero simbolos.txt");getchar();getchar();return 0;
	}
	long i=0;
	while(!feof(strin))
	{
		char simbolo[100];long x;
		fscanf(strin,"%s",simbolo);
		x=strlen(simbolo);
		if (x>0)
			i++;
		if (x>=D_SYMBOL_SIZE)
		{
			printf("\nError tamaño de simbolo=%li que es mayor que el maximo",x);getchar();getchar();
			fclose(strin);return 0;
		}
	}
	fclose(strin);
	long simbolos=i-1;
	g_bloques=(long) (0.999+1.0*simbolos/D_MAX_SYMBOLS);
	return simbolos;
}

//===1.4 Lee los simbolos, inicializa struct
void F11_inicializa(long last_simbolos) 
{
	//1.1. Creo los bloques curl:
	char url0[]="http://finance.yahoo.com/d/quotes.csv?s=";
	char url1[]="&f=sl1v";//symbol,name,last trade price,volume
	char urlquery[D_URL_SIZE];
	long bloq;
	for (bloq=0;bloq<g_bloques;bloq++)
	{
		g_lee[bloq].buffer[0]='\0';
		g_lee[bloq].estado=0;//vacio
		g_lee[bloq].veces=0;
		g_lee[bloq].nombre_bloque=bloq;
	}

	//1.2. Leo el nombre de los simbolos:
	FILE *strin;
	strin=fopen("simbolos.txt","r");
	for (bloq=0;bloq<g_bloques;bloq++)
	{
		strcpy(urlquery,url0);
		char simbolo[D_SYMBOL_SIZE];
		long max=D_MAX_SYMBOLS;
		if (bloq==(g_bloques-1))
			max=last_simbolos;
		long i;
		for (i=0;i<max;i++)
		{
			fscanf(strin,"%s",&simbolo);
			strcat(urlquery,simbolo);
			if (i<max-1)
				strcat(urlquery,"+");
		}
		strcat(urlquery,url1);
		strcpy(g_lee[bloq].url,urlquery);
		printf("\n##INI_QUERY:%li = %s",bloq,g_lee[bloq].url);
	}
	fclose(strin);
}
//===2.1.lee URL: 
//===2.2. lee_bloque: rutina principal
static void* F2_lee_bloque(void* vv)//=pull_one_curl() 
{
	s_lee_url* cc = (s_lee_url* ) vv;
	cc->nombre_bloque;
	//long getURLFile(const char *url, char *buffer, long max_bytes, char *errorMessage) 
	char *url=cc->url;
	char *buffer=cc->buffer;

	TCHAR szCause[255];

	long numBytes;
	TRY  
	{
		CInternetSession session;
		session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, D_TIMEOUT_MS);
		session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 3);
		CFile *remoteFile = session.OpenURL(url, 1 , 
			INTERNET_FLAG_TRANSFER_BINARY | INTERNET_FLAG_RELOAD);

		numBytes = remoteFile->Read(buffer, D_BUFFER_SIZE-1);
		buffer[numBytes]='\0';
		char control[101];strncpy(control,buffer+50,100);control[100]='\0';//¡¡¡COMPROBAR!!!
		if (strstr(buffer,"<TITLE>Error Message"))
		{
			printf("\n##ERROR en bloque %li URL no encontrada o no da datos",cc->nombre_bloque);
			buffer[0]='\0'; cc->estado=1;return NULL;
		}
		remoteFile->Close();//OJOOOOOOOOOOO!!!!!!!
		session.Close();//OJO!!
	}
	CATCH_ALL(error) 
	{
		error->GetErrorMessage(szCause,254,NULL);
		printf("\n##ERROR en bloque %li URL no encontrada, error windows:%s",cc->nombre_bloque,szCause);
		buffer[0]='\0'; cc->estado=1;return NULL;
	}
	END_CATCH_ALL;
	cc->tiempo_captura=Fahora();
	cc->estado=1;				//ESTADO LLENO (o con error)
	return NULL;
}


//===3.1 Segundo desde las 0h de hoy
long Fahora(void)
{
	long tiempo;
	time_t ltime;struct tm *today;time( &ltime );today = localtime( &ltime );
	tiempo=(long) (3600*today->tm_hour+60*today->tm_min+today->tm_sec);
	return tiempo;
}


//===4. Rutinas que usan los datos almacenadoes l


