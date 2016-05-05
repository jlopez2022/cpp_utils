/* Analizador de calibraciones.cpp: 

*/
#include "stdafx.h"
#include <iostream>

using namespace std;

long main( void )
{
	long i;double x;char linea[1024];

	//cerr vá siempre a pantalla. Si se redirige cout a fichero, cerr sige yendo a pantalla
	cerr<<"AVISO DE ERROR"<<endl;  

	cout<<"Meter dato entero:";
	cin>>i;
	cout<<"Dato="<<i<<endl;

	cout<<"Meter dato double:";
	cin>>x;
	cout<<"Dato="<<x<<endl;

	cout<<"Meter texto:";
	cin>>linea;
	cout<<"Texto="<<linea<<endl;



	printf("\nFIN");
	getchar();
	getchar();
	return 1;
}


