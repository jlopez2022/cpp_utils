//Converts RGB to YUV and opposite. There is some error because it is uses byte vars instead of float or double. 
#include <iostream>
#include <stdlib.h>

using namespace std;
typedef unsigned char byte;
#define UDIF(a,b) ((a) > (b) ? (a-b) : (b-a))
//converts anything to byte:
#define TOBYTE(x) ( (x)<0 ? 0 : ((x)<=255 ? ((byte)(x)) : (255)    ))
//Not use this, it is 1.5 times slower than the function at release mode. Speed=2.56 Gigaops/s (gflop):
#define _BGR_TO_Y(rgb) ( (byte)(0.299*(rgb)[2] + 0.587*(rgb)[1] + 0.114*(rgb)[0])   )
#define _RGB_TO_Y(rgb) ( (byte)(0.299*(rgb)[0] + 0.587*(rgb)[1] + 0.114*(rgb)[2])   )


/*
Y:	0.299	0.587	0.114
U:	-0.16881817	-0.331142009	0.500269978
V:	0.500015942	-0.418704406	-0.081311536
*/
//bgr to y:
byte BGR_Y(byte *bgr) { return	(byte)(0.114*bgr[0] + 0.587*bgr[1] + 0.299*bgr[2]); }
//version int:
//byte BGR_Y(byte *bgr) { return	(byte)(   (29*bgr[0] + 150*bgr[1] + 76*bgr[2])/256   ); }


//BGR to YUV:
void BGR_YUV(byte *bgr, byte *yuv)
{
	yuv[0] = (byte)(0.299*bgr[2] + 0.587*bgr[1] + 0.114*bgr[0]);//Y
	yuv[1] = (byte)(127.5 - 0.16881817*bgr[2] - 0.33114200*bgr[1] + 0.500269978*bgr[0]);//U
	yuv[2] = (byte)(127.5 + 0.500015942*bgr[2] - 0.418704406*bgr[1] - 0.081311536*bgr[0]);//V
}

//YUV to BGR:
void YUV_RGB(byte *yuv, byte *bgr)
{
	double x;
	x = -178.7475467 + 1.00000000318589*yuv[0] - 1.02837E-05*yuv[1] + 1.401951827*yuv[2]; bgr[2] = TOBYTE(x);//R
	x = 134.9157006 + 1.000106565*yuv[0] - 0.343980938*yuv[1] - 0.71418142*yuv[2];       bgr[1] = TOBYTE(x);//G
	x = -225.8771912 + 0.999451273*yuv[0] + 1.771227064*yuv[1] + 0.000358749*yuv[2];     bgr[0] = TOBYTE(x);//B
}










//rgb to y:
byte RGB_Y(byte *rgb) { return	(byte)(0.299*rgb[0] + 0.587*rgb[1] + 0.114*rgb[2]); }

//RGB to YUV:
void RGB_YUV(byte *rgb, byte *yuv)
{
	yuv[0] = (byte)(0.299*rgb[0] + 0.587*rgb[1] + 0.114*rgb[2]);//Y
	yuv[1] = (byte)(127.5 - 0.16881817*rgb[0] - 0.33114200*rgb[1] + 0.500269978*rgb[2]);//U
	yuv[2] = (byte)(127.5 + 0.500015942*rgb[0] - 0.418704406*rgb[1] - 0.081311536*rgb[2]);//V
}
/*
R:	1.000000003	-1.02837E-05	1.401951827	-178.7475467
G:	1.000106565	-0.343980938	-0.71418142	134.9157006
B:	0.999451273	1.771227064	0.000358749	-225.8771912
*/
//YUV to RGB:
void YUV_RGB(byte *yuv, byte *rgb)
{
	double x;
	x = -178.7475467 + 1.00000000318589*yuv[0] - 1.02837E-05*yuv[1] + 1.401951827*yuv[2]; rgb[0] = TOBYTE(x);//R
	x = 134.9157006 + 1.000106565*yuv[0] - 0.343980938*yuv[1] - 0.71418142*yuv[2];       rgb[1] = TOBYTE(x);//G
	x = -225.8771912 + 0.999451273*yuv[0] + 1.771227064*yuv[1] + 0.000358749*yuv[2];     rgb[2] = TOBYTE(x);//B
}


void main()
{
	byte RGB0[8][3] = {
		{ 0, 0, 0 },
		{ 0, 0, 255 },
		{ 0, 255, 0 },
		{ 0, 255, 255 },
		{ 255, 0, 0 },
		{ 255, 0, 255 },
		{ 255, 255, 0 },
		{ 255, 255, 255 }
	};
	byte YUV0[8][3]{
		{ 0, 127, 127 },
		{ 29, 255, 106 },
		{ 149, 43, 20 },
		{ 178, 170, 0 },
		{ 76, 84, 255 },
		{ 105, 212, 234 },
		{ 225, 0, 148 },
		{ 255, 127, 127 }
	};
	byte yuv[3], rgb2[3];
	int i, error;
	for (i = 0; i < 8; i++)
	{
		RGB_YUV(RGB0[i], yuv);
		error = UDIF(YUV0[i][0], yuv[0]) + UDIF(YUV0[i][1], yuv[1]) + UDIF(YUV0[i][2], yuv[2]);
		cout << "Step-" << i << ": error RGB-YUV = " << error;
		YUV_RGB(yuv, rgb2);
		error = UDIF(RGB0[i][0], rgb2[0]) + UDIF(RGB0[i][1], rgb2[1]) + UDIF(RGB0[i][2], rgb2[2]);
		cout << " error RGB-YUV-RGB = " << error << endl;
	}
	getchar();
}
