//stb_image.cpp usa la famosa libreria stb para conversion de formatos ppm, jpg, png, TGA, PSD, GIF, HDR, PIC y bmp empleando de libreria un solo fichero "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_JPEG
#include <iostream>
#include "stb_image.h"
using namespace std;
#pragma warning(disable:4996) 
/*
STBI_NO_JPEG
STBI_NO_PNG
STBI_NO_BMP
STBI_NO_PSD
STBI_NO_TGA
STBI_NO_GIF
STBI_NO_HDR
STBI_NO_PIC
STBI_NO_PNM(.ppm and.pgm)

STBI_ONLY_JPEG
*/


void main()
{
	// Basic usage (see HDR discussion below for HDR usage):
	//    int x,y,n;
	//    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
	//    // ... process data if not NULL ...
	//    // ... x = width, y = height, n = # 8-bit components per pixel ...
	//    // ... replace '0' with '1'..'4' to force that many components per pixel
	//    // ... but 'n' will always be the number that it would have been if you said 0
	//    stbi_image_free(data)
	//
	// Standard parameters:
	//    int *x       -- outputs image width in pixels
	//    int *y       -- outputs image height in pixels
	//    int *comp    -- outputs # of image components in image file
	//    int req_comp -- if non-zero, # of image components requested in result
	char filename[1024];
	strcpy(filename, "1920_1080_elefante.jpg");
	int xmax,ymax,n;
	//Conversion jpeg file to RGB data:
	unsigned char *data = stbi_load(filename, &xmax, &ymax, &n, 3);
	unsigned char *data3 = new unsigned char[xmax*ymax * 3L];
	FILE *str = fopen(filename, "rb");
	long jpeg_length=fread(data3, xmax * 3L, ymax,  str);
	cout << "Reading file:" << filename << " size=" << 3.0*jpeg_length*xmax / 1024.0 << "kb" << endl;
	fclose(str);
	//Conversion from jpeg data to RGB data::
	unsigned char *data2 = stbi_load_from_memory(data3,n*xmax*ymax,&xmax,&ymax,&n,3);
	long distintos = 0;
	for (long i = 0; i < xmax * 3L * ymax; i++)
		if (data2[i] != data[i])
			distintos++;
	cout << " xmax,ymax=" << xmax << " " << ymax << " n=" << n << " distintos=" << distintos << endl;
	stbi_image_free(data);
	stbi_image_free(data2);
	delete data3;
	cout << "\n\n======end========\n"; getchar(); getchar();
}

