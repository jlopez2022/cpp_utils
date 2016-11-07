/* Analizador de calibraciones.cpp: 

*/
#include <iostream>
#include <fstream>

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

	long i1;
	ofstream file1("texto.txt");
	if (!file1.is_open())
		cerr<<"ERROR at texto.txt"<<endl;

	file1 << "1 2 ";
	i1=3;file1<<i1<<" ";
	i1=4;file1<<i1<<" ";
	i1=5;file1<<i1<<" ";
	file1.close();

	ifstream file2("texto.txt");
	if (!file2.is_open())
		cerr<<"ERROR at texto.txt"<<endl;
	while (file2.good())//Hapens one time more. Caution
	{
		file2 >> i1;cout <<"i1="<<i1<<endl;
	}

	file2.close();


	cout <<"\n\n===FIN===" << endl;getchar();getchar();
	getchar();
	getchar();
	return 1;
}


