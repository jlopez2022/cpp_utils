//Invierte el orden de los bits de LSB a MSB
//También invertido el nivel y el orden

#include <iostream>
using namespace std;

//Funcion que cambia el orden de los bits LSB-MSB
void reverse_bit_order(unsigned char *mat,long longitud)
{
	unsigned char u,v;
	long i,j;
	for (i=0;i<longitud;i++)
	{
		u=0;v=mat[i];
		for (j=0;j<8;j++)
		{
			u=u+(  ((v>>j)&1) << (7-j)  );
		}
		mat[i]=u;
	}
}

//Funcion que hace not a los bytes y luego cambia también el orden de los bits LSB-MSB
void invert_reverse_bit_order(unsigned char *mat,long longitud)
{
	unsigned char u,v;
	long i,j;
	for (i=0;i<longitud;i++)
	{
		u=0;v=~mat[i];
		for (j=0;j<8;j++)
		{
			u=u+(  ((v>>j)&1) << (7-j)  );
		}
		mat[i]=u;
	}
}

void printf_array(unsigned char *mat,long longitud)
{
	long i,j;
	for (i=0;i<longitud;i++)
		printf(" %02X",mat[i]);
	cout<<endl;
}

int main()
{
	{
		cout<<endl<<"LSB-MSB bit order change using function reverse_bit_order():"<<endl;
		unsigned char mat1[8]={0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF};
		cout<<"Init     :";printf_array(mat1,8);
		reverse_bit_order(mat1,8);
		cout<<"Commit-1 :";printf_array(mat1,8);
		reverse_bit_order(mat1,8);
		cout<<"Commit-2 :";printf_array(mat1,8);
	}
	{
		cout<<endl<<"inverse + LSB-MSB bit order change using function invert_reverse_bit_order():"<<endl;
		unsigned char mat1[8]={0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF};
		cout<<"Init     :";printf_array(mat1,8);
		invert_reverse_bit_order(mat1,8);
		cout<<"Commit-1 :";printf_array(mat1,8);
		invert_reverse_bit_order(mat1,8);
		cout<<"Commit-2 :";printf_array(mat1,8);
	}

	cout <<"\n\n===FIN===" << endl;getchar();getchar();
	return 1;
}