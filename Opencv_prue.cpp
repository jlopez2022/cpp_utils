#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

/* ALL CONFIGURATIONS:
  Proyecto > properties > C/C++ > Additional Include directories: añadir D:\opencv\build\include
  Linker > General > Additional Library Directories  add: $(OPENCV_DIR)\lib   o mejor: D:\opencv\build\x64\vc12\lib
  Linker > Input > “Additional Dependencies” entry add:

  opencv_ts300d.lib
  opencv_world300d.lib
  opencv_ts300.lib
  opencv_world300.lib


Copiar en la misma carpeta del  .cpp que contiene el main  (y también en la carpeta del .exe cuando se compila en modo release):
msvcp120.dll
msvcp120d.dll
msvcr120.dll
msvcr120d.dll
opencv_world300.dll
opencv_world300d.dll
opencv_ffmpeg300_64.dll
*/



using namespace cv;
using namespace std;

int main()
{
	char fichero[1024] = "foto javier 154.jpg";

	Mat image;
	image = imread(fichero, IMREAD_COLOR); // Read the file

	if (!image.data) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image); // Show our image inside it.

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}