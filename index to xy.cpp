#include <stdio.h>
#include <iostream>

using namespace std;


//si tenemos un indice de valor x*xmax+y, obtengo x e y, siempre y cuando  x e y sean < xmax/2
void hallaxy(long index, long xmax, long &x, long &y)
{
	x = index % xmax;
	if (x > (xmax /  2)) x -= xmax;
	if (x < (xmax / -2)) x += xmax;
	y = (index - x) / xmax;
}


void main()
{
	long x, y, x2, y2;
	long index, errores = 0;
	index = 1001 ; hallaxy(index, 1000, x, y);cout <<  index << " x y =" << x << " " << y << endl;
	index =  999 ; hallaxy(index, 1000, x, y); cout << index << " x y =" << x << " " << y << endl;
	index = -999 ; hallaxy(index, 1000, x, y); cout << index << " x y =" << x << " " << y << endl;
	index = -1001; hallaxy(index, 1000, x, y); cout << index << " x y =" << x << " " << y << endl;
	index = 0    ; hallaxy(index, 1000, x, y); cout << index << " x y =" << x << " " << y << endl;
	long xmax = 1000;
	for (y = -16; y < 16 ; y++)
		for (x = -16; x < 16; x++)
		{
			index = y*xmax + x;
			hallaxy(index, xmax, x2, y2);
			if ((x != x2) || (y != y2))
			{
				cout << "xy=" << x << " " << y << " xy2=" << x2 << " " << y2 << endl;
				errores++;
			}
		}
	cout << "errores=" << errores << endl;
	cout << "======end========\n"; getchar(); getchar();
}