#include <iostream>
using namespace std;


//In the .h file:
class c_clase
{
public:
	static const int airfoils = 7;
	static const int tipo_calculo[airfoils];
	int num_planes;

	//ruder=to turn right-left 
	//gear: always on on www1 aircrafts
	static const char airfoilfile[airfoils][200];
};

//in the cpp file:
const char c_clase::airfoilfile[airfoils][200] = {
	"GOE 418 Fokker D.VIII.txt",
	"GOE 298 Fokker Dr1.txt",
	"NACA 2405 SPAD XIII.txt",
	"GOE 100 SOPWITH.txt",
	"NACA 4308 Nieuport 11.txt",
	"NACA 6307 Nieuport 17.txt",
	"GOE 174 ALBATROS.txt" };
const int c_clase::tipo_calculo[airfoils] = { 2, 1, 2, 2, 2, 2, 2 };


void main()
{
	c_clase clase1;
	for (int i = 0; i < 7; i++)
		cout << "Number:" << i << " profile=" << clase1.airfoilfile[i] << "\t calculo=" << clase1.tipo_calculo[i] << endl;

	cout << "\n=============== FIN ==================" << endl;
	getchar(); getchar();
}