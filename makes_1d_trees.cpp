//Ordering using vectors. Also obtain a list.

#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <time.h> //timers
#pragma warning(disable:4996) //disable deprecateds
using namespace std;
typedef unsigned char uchar;

long nonredundant_calls;
long redundant_calls;


int total_calls;
//Few code and works fine!. Do not need to assign flag[0]=0
void fill_flags8_1d(int y0, int y2, vector<uchar> &flag)
{
	//int y1;
	switch (y2 - y0)
	{
	default:
	{
		total_calls++;
		int y1 = (y0 + y2) / 2; flag[y1] = 0;
		//if (flag[y1] == 0) redundant_calls++; else flag[y1] = 0; //no redundant calls!
		fill_flags8_1d(y0, y1, flag);
		fill_flags8_1d(y1, y2, flag);
		break;
	}
	case 0:
		return;
	case 1:
		total_calls++;
		flag[y0] = 0;
		break;
	case 2:
		total_calls++;
		flag[y0] = flag[y0 + 1] = 0;
		break;
	}
}

void test_flag8()
{
	int ymax, y;
	int failures;

	//1d
	for (ymax = 2; ymax < 20; ymax++)
	{
		vector< uchar > f1(ymax, 1);//creates 1dvector and sets to 1
		total_calls = failures = redundant_calls = 0;
		//f1[0] = 0;//caution!
		fill_flags8_1d(0, ymax, f1);

		cout << "ymax=" << ymax << " calls=" << total_calls << " # ";
		for (y = 0; y < ymax; y++)
		{
			if (f1[y] == 1)
			{
				printf("%3i ", y); failures++;
			}
		}
		if (failures > 0)
			cout << "\n >>>failures=" << failures << endl;
		else
			cout << "NO FAILS!!  ";
		cout << endl;
	}
}


int main()
{
	test_flag8();
	//test_flag2_2d();
	cout << "=== END ===" << endl; getchar();
}

