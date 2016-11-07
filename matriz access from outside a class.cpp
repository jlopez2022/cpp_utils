#include <iostream>
#include <string.h>

using namespace std;

class c_clase{

public:
	c_clase()
	{
		int matriz0_0[4] = { 100, 101, 102, 103 };
		int matriz1_0[3][4] = {
			{ 10, 11, 12, 13 },
			{ 20, 21, 22, 23 },
			{ 30, 31, 32, 33 }
		};
		memcpy(matriz0, matriz0_0, sizeof(matriz0_0));
		memcpy(matriz1, matriz1_0, sizeof(matriz1_0));
	}
	void dame_puntero(int **matriz1)
	{
		*matriz1 = matriz0;
	}
private:
	//Matrices a ser leidas
	int matriz0[4];
	int matriz1[3][4];
};



void main()
{
	int *ptr=NULL;

	c_clase clase1;
	clase1.dame_puntero(&ptr); //pido el puntero a la matriz a leer

	for (int i = 0; i < 4; i++)
		cout << ptr[i] << " "; //ojo, usar con precaucion, pues a partir de ahora accedo a matriz privada desde fuera

	cout << endl<< endl;
	cout << "=================== END ======================" << endl << endl;
	getchar(); getchar();
}