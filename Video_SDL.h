//outputs video using SDL
#ifndef  __VIDEO_Vx_H
#define  __VIDEO_Vx_H


#include <stdio.h>
#include <string.h> //memcpy
/*
================  COMPILATE LINUX =================
COMPILATION LINE:
gcc  -std=c++11 -lstdc++ -o opencl_exe Algoritmo_BCP.cpp Algoritmo_KNP.cpp Algoritmo_BCN.cpp Main.cpp Parallel.cpp Video_v1.cpp processing.cpp -Wall -ggdb $(pkg-config --cflags --libs libavformat libavcodec libswresample libswscale libavutil sdl) -lm -lOpenCL

All those files can be loaded from: https://drive.google.com/drive/folders/0B-pAHNkXnHF9d216NGxsRTVaeXc?usp=sharing




=================  INSTALL FFMPEG & SDL LINUX =================
Download from: https://ffmpeg.zeranoe.com/builds/


=================================================
Windows SDL2.0:
Copy from from here https://buildbot.libsdl.org/sdl-builds/sdl-visualstudio/?C=M;O=D and paste here C:\SDL2-3223\lib\win32;
Add to path environment variable: C:\SDL2-3223\lib\win32;
Linker->system: Console (/SUBSYSTEM:CONSOLE)
C/C++->general->additional include directories: C:\SDL2-3223\include
Linker->General->additional library directories: C:\SDL2-3223\lib\win32
Linker->input->additional dependencies: SDL2.lib; SDL2main.lib
=================================================

*/

typedef unsigned char uchar;
extern "C"{
#ifndef inline
#define inline __inline
#endif

#ifndef __linux__
#pragma warning(disable:4996) //to use fopen
#endif


#include <SDL.h>
#include <SDL_thread.h>

};//extern "C"

class c_video 
{
public:
	c_video(int xmax1, int ymax1) { init(); xmax = xmax1; ymax = ymax1; xmax3 = 3 * xmax; pixels = xmax*ymax; }

	void clone(uchar *imagen_dst, uchar *imagen_ori) { memcpy(imagen_dst, imagen_ori, xmax3*ymax*sizeof(uchar)); }
	//Retornan 0 al finalizar el video!

	void save_frames(long ini_frame, long fin_frame);

	void show(uchar *frame);

	//mete uchar en data1 para sacar videos
	void mete1(uchar *imagen1) 	{ this->clone(this->data1, imagen1); }

	//sets video screen name
	void set_screen_name(char *screen_name) { SDL_SetWindowTitle(window, screen_name); }
	bool read_image_ppm(char *filename, uchar  *data);
	bool save_image_ppm(char *filename, uchar  *data);
	bool save_image_ppmBGR(char *filename, uchar  *data);

	~c_video();//Must delete data2???
	double fps;
private:
	int xmax, ymax, xmax3;
	long pixels;
	void init(void);
	//returns 0 when ending video

	//Private data:
	uchar *data0, *data1, *data2;



	//SDL ones:
	SDL_Window   *window;
	SDL_Surface  *screen, *screen2;//If a second screen is wanted, it must be initiated and bmp2 and screen2 must be used
	SDL_Event    event;
	uchar *bgry;
};
//================= class c_video          ==================




#endif
