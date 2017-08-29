//Extracts randomly from a stack until it is empty!
#include <iostream>
#include <vector>
#include <stdlib.h> //rand

using namespace std;
typedef unsigned char uchar;

class c_rand_extract
{
public:
	c_rand_extract(int xmax1, int ymax1);
	~c_rand_extract(){  }
	//extracts data until the stack is emptied, then -1 are sent:
	int stack_extract();
	//extracts data until the stack until is emptied, then reloads:
	int loop_stack_extract();
	//remixes the output data. It is recommended max 32Megaops, (32 if 1Megapixel):
	void remix(int times);
	void check_stack_extract();//changes the stack, be careful!
private:
	int last_index;
	vector<int> stack;
	int xmax, ymax, pixels;
};

c_rand_extract::c_rand_extract(int xmax1, int ymax1)
{
	xmax = xmax1; ymax = ymax1; pixels = xmax*ymax;
	stack.resize(pixels);
	last_index = pixels;
	for (int i = 0; i < pixels; i++) stack[i] = i;  //fills the stack
}
int c_rand_extract::stack_extract()
{
	if (last_index <= 0) return -1;
	static int ix=0;
	ix = (ix + rand()) % last_index;
	int ret = stack[ix];
	stack[ix] = stack[--last_index];
	stack[last_index] = ret; //stack not destroyed, only removed!!!!
	return ret;
}
int c_rand_extract::loop_stack_extract()
{
	static int ix=0;
	ix = (ix + rand()) % last_index;
	int ret = stack[ix];
	stack[ix] = stack[--last_index];
	stack[last_index] = ret; //stack not destroyed, only removed!!!!
	if (last_index <= 0)
		last_index = pixels;
	return ret;
}

void c_rand_extract::remix(int times)
{
	for (int n = 0; n < times; n++)
	{
		for (int i = 0; i < pixels; i++)
			loop_stack_extract();
	}
}

void c_rand_extract::check_stack_extract()
{
	vector<int> stack2(pixels,0);
	int i;
	for (i = 0; i < pixels; i++)
		stack2[stack_extract()] = 1;
	int sum=0;
	for (i = 0; i < pixels; i++)
		sum += stack2[i];
	if (sum != pixels)
		cout << "ERROR1 sum=" << sum << " != " << pixels << endl;
	else
		cout << "FIRST test ok" << endl;

	last_index = pixels;
	for (i = 0; i < pixels; i++) 
		stack2[i] = 0;
	for (i = 0; i < pixels; i++)
		stack2[stack_extract()] = 1;
	sum = 0;
	for (i = 0; i < pixels; i++)
		sum += stack2[i];
	if (sum != pixels)
		cout << "ERROR2 sum=" << sum << " != " << pixels << endl;
	else
		cout << "SECOND test ok" << endl;
	last_index = pixels;
}


int main()
{
	int xmax = 1280, ymax = 720;
	c_rand_extract c1(xmax, ymax);
	c1.remix(32);
	c1.check_stack_extract();
	cout << "=== END ===" << endl; getchar();
	return 1; 
}

