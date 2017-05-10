//Friend classes
#include <iostream>
#include <stdlib.h>
#pragma warning(disable:4996)

using namespace std;

class c_base
{
private:
	static int xmax, ymax;
	friend class c_uno;
	friend class c_dos;
};

int c_base::xmax, c_base::ymax;

class c_uno
{
private:
	c_base *root;
public:
	void set(int xmax1, int ymax1) { root->xmax = xmax1; root->ymax = ymax1; }
	void get(int &xmax1, int &ymax1) { xmax1 = root->xmax; ymax1 = root->ymax; }
};
class c_dos
{
private:
	c_base *root;
public:
	void set1(int xmax1, int ymax1) { root->xmax = xmax1; root->ymax = ymax1; }
	void get1(int &xmax1, int &ymax1) { xmax1 = root->xmax; ymax1 = root->ymax; }
};





void main()
{
	c_uno uno;
	c_dos dos;
	uno.set(10001, 2001);
	dos.set1(1280, 720);
	int xmax, ymax;
	uno.get(xmax, ymax);
	cout << "uno:" << xmax << " " << ymax << endl;
	dos.get1(xmax, ymax);
	cout << "dos:" << xmax << " " << ymax << endl;
	cout << "==== END ====" << endl;
	getchar();
}


