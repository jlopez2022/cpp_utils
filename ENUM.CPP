#include <fstream>
#include <iostream>

using namespace std;


//Not recommended:
enum e_flag{ F_NC = 100, F_CAR = 101, F_BK = 102 };//Not recomended
//Recommended use "enum class" so not possible errors:
enum class e_state{ NC=100,CAR=101,BK=102}; //none, is a car, is background (road)

typedef unsigned char uchar;
enum e_type : uchar{TIPO1=110,TIPO2=111,TIPO3=103,TIPO4=1015};

void main()
{
	e_flag flag1;
	flag1 = F_NC;
	cout << "FLAG=" << flag1 << endl;
	flag1 = F_CAR;
	cout << "FLAG=" << flag1 << endl;
	flag1 = F_BK;
	cout << "FLAG=" << flag1 << endl;

	e_state state1;
	state1 = e_state::NC;
	cout << "State=" << (int) state1 << endl;
	state1 = e_state::CAR;
	cout << "State=" << (int) state1 << endl;
	state1 = e_state::BK;
	cout << "State=" << (int) state1 << endl;


	e_type tipo1;
	tipo1 = TIPO1;
	cout << "Tipo=" << (int)tipo1 << endl;
	tipo1 = e_type::TIPO2;
	cout << "Tipo=" << (int)tipo1 << endl;	
	tipo1 = e_type::TIPO3;
	cout << "Tipo=" << (int)tipo1 << endl;
	tipo1 = TIPO4;
	cout << "Tipo=" << (int)tipo1 << endl;
	cout << "\n=== END===" << endl;
	getchar(); getchar();

}