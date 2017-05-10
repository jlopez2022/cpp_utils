/*
Used SDL to display images
Install SDL 1.2 in the computer, CHANGE C:\SDL2-2.0.5 by  C:\SDL2-1.2.xxx here: !!

== == == == == == == == = INI INSTALL FFMPEG & SDL 2.0 WINDOWS & VS2015 == == == == == == == == =
Dlls are here : https ://ffmpeg.zeranoe.com/builds/win64/shared/ffmpeg-20160825-01aee81-win64-shared.zip
.lib and.h : https ://ffmpeg.zeranoe.com/builds/win64/dev/ffmpeg-20160825-01aee81-win64-dev.zip 

Settings windows x64 all :

C / C++->general->additional include directories :
c : \ffmpeg\include; C:\SDL2-2.0.5\include; $(AMDAPPSDKROOT)\include;

Linker->General->additional library directories :
c : \ffmpeg\lib;C:\SDL2-2.0.5; $(AMDAPPSDKROOT)\lib\x64

	Linker->input->additional dependencies :
	swscale.lib; avutil.lib; avformat.lib; avdevice.lib; avcodec.lib; SDL2.lib; SDL2main.lib; OpenCL.lib;      (otras:kernel32.lib; user32.lib; gdi32.lib; winspool.lib; comdlg32.lib; advapi32.lib; shell32.lib; ole32.lib; oleaut32.lib; uuid.lib; odbc32.lib; odbccp32.lib)

		Añadir a environment variable path :
c : \ffmpeg\bin; C:\SDL2-2.0.5\lib\x64;


CAUTION: place in the program: 
#include <SDL.h>
#include <SDL_thread.h>
#undef main 
== == == == == == == == = FIN INSTALL FFMPEG & SDL WINDOWS & VS2015 == == == == == == == == =
*/


#include <iostream>
#include <fstream>
typedef unsigned char uchar;
using namespace std;

extern "C"{
#include <SDL.h>
#include <SDL_thread.h>
#undef main
};//extern C
class c_SDL1
{
public:
	c_SDL1(int xmax1, int ymax1);
	~c_SDL1() { SDL_FreeSurface(surface); SDL_FreeSurface(image); SDL_Quit(); }

	void show(uchar *image1);
	void show_file(char *fichero);
	void bgr_flag(uchar *img);
	int xmax, ymax;
	long pixels;
private:
	SDL_Surface* surface;
	SDL_Surface* image;
};


c_SDL1::c_SDL1(int xmax1, int ymax1)
{
	xmax = xmax1; ymax = ymax1; pixels = 1L*xmax*ymax;
	surface = SDL_SetVideoMode(xmax, ymax, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (surface == NULL)
	{
		cout << "SDL_SetVideoMode() Failed: " << SDL_GetError() << endl; getchar();
		exit(1);
	}
	// Set the title bar
	SDL_WM_SetCaption("ECOSCALE, Acciona Construccion", "ECOSCALE, Acciona Construccion");
	//image = SDL_LoadBMP("Autopista.bmp");
	image = SDL_SetVideoMode(xmax, ymax, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (image == NULL)
	{
		cout << "c_SDL1::c_SDL1 SDL_SetVideoMode() Failed: " << SDL_GetError() << endl;
		exit(1);
	}
}

void c_SDL1::show(uchar *image1)
{
	uchar *ptr = (uchar *)image->pixels;
	uchar *ptr2 = image1;
	int x, y;
	for (y = 0; y < ymax;y++)
	{
		for (x = 0; x < xmax; x++)
		{
			*ptr++ = *ptr2++;//b
			*ptr++ = *ptr2++;//g
			*ptr++ = *ptr2++;//r
			*ptr++ = 0;      //A
		}
		for (x=4L*xmax; x < image->pitch; x++)
			*ptr++ = 0;
	}
	SDL_BlitSurface(image, NULL, surface, NULL);
	SDL_Flip(surface);
}


void c_SDL1::bgr_flag(uchar *ptr)
{
	//SDL_FreeSurface(image);
	//image = SDL_SetVideoMode(xmax, ymax, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	int x, y;
	memset(ptr, 0, 3L * xmax*ymax);
	for (y = 0; y < ymax/3; y++)
		for (x = 0; x < xmax; x++)
		{
			*ptr++ = 255;//b
			*ptr++ = 0;//g
			*ptr++ = 0;//r
		}
	for (; y < 2*ymax/3; y++)
		for (x = 0; x < xmax; x++)
		{
			*ptr++ = 0;//b
			*ptr++ = 255;//g
			*ptr++ = 0;//r
		}
	for (; y < ymax; y++)
		for (x = 0; x < xmax; x++)
		{
			*ptr++ = 0;//b
			*ptr++ = 0;//g
			*ptr++ = 255;//r
		}
}


void c_SDL1::show_file(char *fichero)
{
	image = SDL_LoadBMP(fichero);
	//uchar *ptr = (uchar *)image->pixels;
	//for (int i = 0; i < 1280 * 4 * 3; i++) ptr[i] = 255;
	SDL_BlitSurface(image, NULL, surface, NULL);
	SDL_Flip(surface);
}


int main()
{
	//Initialize SDL 
	SDL_Init(SDL_INIT_EVERYTHING);
	c_SDL1 sdl(1280, 720);
	uchar *ptr = new uchar[3L * 1280 * 720];
	sdl.bgr_flag(ptr);
	sdl.show(ptr);
	//sdl.show_file("Autopista.bmp");
	cout << "=== END ===" << endl; getchar();
	delete ptr;
	return 1;
} 