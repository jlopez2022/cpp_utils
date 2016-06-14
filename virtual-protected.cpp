#include <iostream>
using namespace std;


class c_nave
{
public:
	virtual void inicializa(){/*NO HAGO NADA. lo pongo por si se olvidara en los hijos*/ }
	void acelera(float dx,float dy,float thrust)
	{
		speed_x+=thrust/weight;
		posicion_x+=speed_x;
	}
protected:
	float posicion_x,posicion_y,speed_x,speed_y;
	float weight;
	float ammunition;
};

class c_nave_gorda:public c_nave
{
public:
	void inicializa() { this->weight=100.0f;posicion_x=posicion_y=speed_x=speed_y=0.0f;ammunition=10000;}
};
class c_nave_chica:public c_nave
{
public:
	void inicializa() { this->weight=10.0f;posicion_x=posicion_y=speed_x=speed_y=0.0f;ammunition=500;}
};





int main()
{
	c_nave *nave[2];
	nave[0]=new c_nave_gorda();nave[0]->inicializa();
	nave[1]=new c_nave_chica();nave[1]->inicializa();
	//c_nave_gorda nave1;
	//c_nave_chica nave2;
	cout <<"\n\n===FIN===" << endl;getchar();getchar();
	return 1;
}


