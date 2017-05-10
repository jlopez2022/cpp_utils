//Array buffer
#include <iostream>

#pragma warning(disable:4996) 
typedef unsigned char uchar;
using namespace std;

class c_buffer
{
public:
	c_buffer(long size1, int bufferlong1){ index = 0; size = size1; bufferlong = bufferlong1; buffer = new uchar[size*bufferlong]; }
	~c_buffer(){ delete[] buffer; }
	void increase_index(){ index = (index + 1) % bufferlong; }
	void decrease_index(){ if (--index<0) index= bufferlong-1; }
	uchar *buffer_ptr(int position) //position = from -(bufferlong-1) to (bufferlong-1), if 0 is the actual position
	{ 
		if ((position > 0) || (position <= -bufferlong))
		{
			cout << "ERROR at c_buffer::buffer_ptr position=" << position << " is out of bounds " << -bufferlong + 1 << " to 0" << endl; getchar(); return NULL;
		}
		int position2 = index + position;
		if (position2 < 0)
			position2 += bufferlong;
		return &buffer[position2*size];
	}
private:
	int index;
	long size;
	int bufferlong;
	uchar *buffer;
};


int main()
{
	c_buffer buffer1(10, 7);//7 niveles, de tamaño 10

	uchar *ptr;
	int i, j;
	for (j = 0; j < 7; j++)
	{
		ptr = buffer1.buffer_ptr(0);
		for (i = 0; i < 10; i++)
		{
			ptr[i] = j * 10 + i;
		}
		buffer1.increase_index();//next buffer group
	}

	buffer1.decrease_index();
	cout << "actual buffer:";
	ptr = buffer1.buffer_ptr(0);
	for (i = 0; i < 10; i++)
	{
		cout << (int) ptr[i] << " ";
	}
	cout << endl << "buffer before:";
	ptr = buffer1.buffer_ptr(-1);
	for (i = 0; i < 10; i++)
	{
		cout << (int)ptr[i] << " ";
	}
	cout << endl << "first buffer:";
	ptr = buffer1.buffer_ptr(-6);
	for (i = 0; i < 10; i++)
	{
		cout << (int)ptr[i] << " ";
	}

	//3 new levels
	cout << endl << "3 new levels introducted" << endl;
	for (j = 0; j < 3; j++)
	{
		buffer1.increase_index();//next buffer group
		ptr = buffer1.buffer_ptr(0);
		for (i = 0; i < 10; i++)
		{
			ptr[i] = j * 10 +9 -i;
		}
	}
	cout << "actual buffer:";
	ptr = buffer1.buffer_ptr(0);
	for (i = 0; i < 10; i++)
	{
		cout << (int)ptr[i] << " ";
	}
	cout << endl << "buffer before:";
	ptr = buffer1.buffer_ptr(-1);
	for (i = 0; i < 10; i++)
	{
		cout << (int)ptr[i] << " ";
	}
	cout << endl << "buffer -2 levels:";
	ptr = buffer1.buffer_ptr(-2);
	for (i = 0; i < 10; i++)
	{
		cout << (int)ptr[i] << " ";
	}
	cout << endl << "buffer -3 levels:";
	ptr = buffer1.buffer_ptr(-3);
	for (i = 0; i < 10; i++)
	{
		cout << (int)ptr[i] << " ";
	}

	cout << endl << endl << "=== end ===" << endl; getchar();
	return 0;
}