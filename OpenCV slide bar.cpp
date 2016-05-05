/*
VS2008 y OpenCV2.1:
	Instalar la version windows VS2008!!!: son solo 28 megas, 128megas descomprimido :)
	https://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.1/OpenCV-2.1.0-win32-vs2008.exe/download 


  Proyecto > properties > C/C++ > general > Additional Include directories: D:\OpenCV2.1\include\opencv
  Linker > General > Additional Library Directories: D:\OpenCV2.1\lib
  Linker > Input > Additional dependencies:   ¡¡¡SIN punto y coma!!! ; 
  
  Modo release:
cv210.lib                      
cxcore210.lib
highgui210.lib

  ó 

  Modo debug:
  cv210d.lib
  cxcore210d.lib
  highgui210d.lib

SI no FUNCIONA!!!:   
1. Copiar toodas las dlls en el directorio de trabajo: 
		cv210d.dll,cv210.dll,cxcore210d.dll,cxcore210.dll, highgui210d.dll,highgui210.dll

2. ó Poner variable de entorno en el windows en linea de comandos:
		setx -m OPENCV_DIR D:\OpenCV2.1
*/


#include <cv.h>
//#include <cxcore.hpp>
#include <highgui.h>
#include <iostream>

using namespace std;
using namespace cv;





#define NCALLE 8
char calles[NCALLE][100]={
	"amsterdam.jpg",
	"madrid.jpg",
	"madrid1.jpg",
	"JesusM1.jpg",
	"JesusM2.jpg",
	"Mexico.jpg",
	"Ferraz.jpg",
	"Mayor.jpg"};


	
	
int main( int argc, char** argv )
{
     // Read original image 
	char fichero[200];
	strcpy(fichero,"data/");strcat(fichero,calles[0]);
     Mat src = imread(fichero);

     //if fail to read the image
     if (!src.data) 
     { 
          cout << "Error loading the image" << endl;
          return -1; 
     }

      // Create a window
     namedWindow("My Window", 1);

     //Create trackbar to change brightness
     int iSliderValue1 = 50;
     createTrackbar("Brightness", "My Window", &iSliderValue1, 100);

      //Create trackbar to change contrast
     int iSliderValue2 = 50;
     createTrackbar("Contrast", "My Window", &iSliderValue2, 100);

      while (true)
     {
          //Change the brightness and contrast of the image (For more infomation http://opencv-srf.blogspot.com/2013/07/change-contrast-of-image-or-video.html)
          Mat dst;
          int iBrightness  = iSliderValue1 - 50;
          double dContrast = iSliderValue2 / 50.0;
          src.convertTo(dst, -1, dContrast, iBrightness); 

           //show the brightness and contrast adjusted image
          imshow("My Window", dst);

          // Wait until user press some key for 50ms
          int iKey = waitKey(50);

          //if user press 'ESC' key
          if (iKey == 27)
          {
               break;
          }
     }

      return 0;
}	
	
	
	
