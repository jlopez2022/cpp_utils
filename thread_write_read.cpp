// linux compilation:         g++ -std=c++11 -pthread -o throw_threads throw_V001.cpp
#include <iostream>
#include <thread>

//looks for decomposition in prime numbers
#include <iostream>

#ifdef __linux__ 
#include <unistd.h>    //usleep()
int Sleep(int sleepMs) { return usleep(sleepMs * 1000); }
#else
#include <Windows.h> //Sleep
#endif

using namespace std;
typedef unsigned char uchar;

class c_exchange
{
public:
	c_exchange(int xmax1, int ymax1){ xmax = xmax1; ymax = ymax1; rgb = new uchar[3L * xmax*ymax]; Y = new uchar[xmax*ymax]; }
	~c_exchange(){ delete rgb; delete Y; }
	enum class e_flag{ NC = 100, DATA_VALID = 101, EMPTY = 102 };
	void generate_data();
	void reads_data();

	void rgb_in(uchar *rgb1);
	uchar *rgb_in();
	uchar *rgb_out();
	void imageY_in(uchar *Y1);
	uchar *imageY_in();
	uchar *imageY_out();
	void speed_in(double speed1[2]);
	void density_in(double density1[2]);
	bool speed_out(double speed1[2]);
	bool density_out(double density1[2]);

private:
	int xmax, ymax;
	static e_flag flag_speed, flag_density, flagRGB, flagY;
	static double speed[2], density[2];
	uchar *rgb, *Y;//no size, warning!!
};




c_exchange::e_flag c_exchange::flag_speed = e_flag::EMPTY, c_exchange::flag_density = e_flag::EMPTY, c_exchange::flagRGB = e_flag::EMPTY, c_exchange::flagY = e_flag::EMPTY;
double c_exchange::speed[2], c_exchange::density[2];

void c_exchange::generate_data()
{
	int i = 0;
	while (1)
	{
		double speed[2] = { (double)i, (double)(i + 1) };
		this->speed_in(speed);
		double density[2] = { (double)i + 1000, (double)(i + 1001) };
		this->density_in(density);
		i = (i + 10) % 1000;
		Sleep(100);
	};
}
void c_exchange::reads_data()
{
	while (1)
	{
		double speed[2], density[2];
		if (this->speed_out(speed))
			cout << "speed:" << speed[0] << " " << speed[1] << endl;
		if (this->density_out(density))
			cout << "density:" << density[0] << " " << density[1] << endl;
		Sleep(5);
	};

}

void c_exchange::rgb_in(uchar *rgb1)
{
	if (flagRGB == e_flag::EMPTY)
	{
		memcpy(rgb,rgb1,xmax*ymax); flagRGB = e_flag::DATA_VALID;
	}
}

uchar *c_exchange::rgb_in()
{
	if (flagRGB == e_flag::EMPTY)
	{
		flagRGB = e_flag::DATA_VALID; return rgb;
	}
	return NULL;
}

void c_exchange::imageY_in(uchar *Y1)
{
	if (flagY == e_flag::EMPTY)
	{
		memcpy(Y,Y1,xmax*ymax); flagY = e_flag::DATA_VALID;
	}
}

uchar *c_exchange::imageY_in()
{
	if (flagY == e_flag::EMPTY)
	{
		flagY = e_flag::DATA_VALID; return Y;
	}
	return NULL;
}


void c_exchange::speed_in(double speed1[2])
{
	if (flag_speed == e_flag::EMPTY)
	{
		speed[0] = speed1[0]; speed[1] = speed1[1]; flag_speed = e_flag::DATA_VALID;
	}
}
void c_exchange::density_in(double density1[2])
{
	if (flag_density == e_flag::EMPTY)
	{
		density[0] = density1[0]; density[1] = density1[1]; flag_density = e_flag::DATA_VALID;
	}
}
bool c_exchange::speed_out(double speed1[2])
{
	if (flag_speed == e_flag::DATA_VALID)
	{
		speed1[0] = speed[0]; speed1[1] = speed[1]; flag_speed = e_flag::EMPTY; return true;
	}
	return false;
}
bool c_exchange::density_out(double density1[2])
{
	if (flag_density == e_flag::DATA_VALID)
	{
		density1[0] = density[0]; density1[1] = density[1]; flag_density = e_flag::EMPTY; return true;
	}
	return false;
}

uchar *c_exchange::rgb_out()
{
	if (flagRGB == e_flag::DATA_VALID)
	{
		flagRGB = e_flag::EMPTY; return this->rgb;
	}
	return NULL;
}

uchar *c_exchange::imageY_out()
{
	if (flagY == e_flag::DATA_VALID)
	{
		flagY = e_flag::EMPTY; return this->Y;
	}
	return NULL;
}


int main() 
{
	c_exchange writes(640, 320), reads(640, 320);
	double speed_out[2];
	{
		double speed[2] = { 100.1, 101.2 };
		double density[2] = { 200.1, 201.2 };
		if (reads.speed_out(speed_out))
			cout << "speed:" << speed[0] << " " << speed[1] << endl;

		writes.speed_in(speed);
		writes.speed_in(speed);
		if (reads.speed_out(speed_out))
			cout << "speed:" << speed[0] << " " << speed[1] << endl;
		if (reads.speed_out(speed_out))
			cout << "speed:" << speed[0] << " " << speed[1] << endl;
	}
	{
		double speed[2] = { 110.1, 111.2 };
		double density[2] = { 210.1, 211.2 };
		writes.speed_in(speed);
		writes.speed_in(speed);
		if (reads.speed_out(speed_out))
			cout << "speed:" << speed[0] << " " << speed[1] << endl;
	}
	cout << "=== END test1 ===" << endl;

	//CAUTION!! if a parameter "Param_x" has to be passed to generate_data, do at the end!!: thread th_write(&c_exchange::generate_data, writes,Param_x);
	thread th_write(&c_exchange::generate_data, writes);
	thread th_read(&c_exchange::reads_data, reads);

	cout << "=== END ===" << endl;
	getchar();
	return 1;
}


