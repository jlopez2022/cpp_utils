#include <iostream>
#include <thread> //sleep_for, threads
#include <mutex>
#include <chrono> //to measure time dif only
#define MUTEX_DELAY microseconds(10)  //milliseconds(4)

std::mutex m;
#define SIZE 100

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

typedef unsigned char uchar;

class c_video
{
public:
	c_video() { xsize = 100; bgr = new uchar[SIZE]; frame_ready = 0; num_frame = 0; }
	void adquiere(uchar **mat1) { m.lock(); *mat1 = bgr; m.unlock(); }
	void assign(uchar **ptr) { *ptr = bgr; }
	long num_frame;
	long xsize,pixels;
	int frame_ready;//0=mo frame dieponible,1=frame pendiente
	uchar *bgr;
};


void write_video(c_video *vid1)
{
	uchar *bgr1 = vid1->bgr;
	uchar valor = 10;
	while (1)
	{
		m.lock();
		if (vid1->frame_ready == 0)//si no hay frame disponible lo saco del video del disco duro o camara y lo meto en bgr
		{
			for (long j = 0; j < SIZE; j++)
				bgr1[j] = valor;
			sleep_for(microseconds(70));//tiempo de sacar datos del disco duro (3Mb /60Mbps =50ms)
			valor++;
			vid1->frame_ready = 1;//available frame
			vid1->num_frame++;//frame counter increasing
		}
		m.unlock();
		//sleep_for(MUTEX_DELAY); //to give time to read_video() function
	}
}

void read_video(c_video *vid1)
{

	auto start = system_clock::now();
	auto stop = system_clock::now();
	auto diff = duration_cast<nanoseconds>(stop - start).count();

	uchar *bgr1 = vid1->bgr;
	long ant=vid1->bgr[99], frame_ant = vid1->num_frame;
	long errores=0;
	while (1)
	{
		m.lock();
		if (vid1->frame_ready == 1)//si hay frame disponible lo proceso
		{
			sleep_for(microseconds(80));//tiempo de tratar el frame
			vid1->frame_ready = 0;//no hay frame disponible
			if (vid1->num_frame != frame_ant + 1)
			{
				errores++;
				cout << "ERROR de captura en frame numero:" << vid1->num_frame << " errores="<<errores<<endl;
			}
			if (vid1->num_frame % 2000 == 0)
			{
				cout << " FRAME NUM:" << vid1->num_frame << " errores=" << errores;
				stop = system_clock::now(); diff = duration_cast<nanoseconds>(stop - start).count();
				cout << " time diff=" << diff*1e-6 << "ms" << endl;
			}
			frame_ant = vid1->num_frame;
		}
		m.unlock();
		//sleep_for(MUTEX_DELAY); //to give time to write_video() function
	}
}



int main()
{
	c_video clase1;
	thread t1,t2;
	t1 = thread(write_video, &clase1);
	t2 = thread(read_video, &clase1);

	if (t1.joinable())
		t1.join(); 
	if (t2.joinable())
		t2.join();
	return 1;
}

