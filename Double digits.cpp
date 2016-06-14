//double accuracy
#include <iostream>
using namespace std;


int main()
{
	long i;
	{
		long double xx = 1.0, xant = xx, delta = 1.0;
		for (i = 0; i < 100; i++)
		{
			delta = delta / 10;
			xx += delta;
			if (xx == xant) break;
			else xant = xx;
		}
		cout << "xx (long double) =" << xx << " digits=" << i - 1 << endl;
	}
	{
		double xx = 1.0, xant = xx, delta = 1.0;
		for (i = 0; i < 100; i++)
		{
			delta = delta / 10;
			xx += delta;
			if (xx == xant) break;
			else xant = xx;
		}
		cout << "xx (double) =" << xx << " digits=" << i - 1 << endl;
		xx = 1e17; delta = xx;
		for (i = 0; i < 100; i++)
		{
			delta = delta / 10;
			xx += delta;
			if (xx == xant) break;
			else xant = xx;
		}
		cout << "xx (double) =" << xx << " digits=" << i - 1 << endl;
	}
	{
		float xx = 1.0, xant = xx, delta = 1.0;
		for (i = 0; i < 100; i++)
		{
			delta = delta / 10;
			xx += delta;
			if (xx == xant) break;
			else xant = xx;
		}
		cout << "xx (float ) =" << xx << " digits=" << i - 1 << endl;
	}
	cout << "=== FIN ===" << endl; getchar(); getchar();
	return 1;
}
