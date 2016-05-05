//ffilldemo-1.c  MUY REDUCIDO Prueba de mouse
//Metido en project->settings-> ventana "Object/lybrary modules":
//  cxcore.lib cv.lib highgui.lib cvaux.lib

//Ver: HighGUI Reference Manual http://vision.cis.udel.edu/opencv/ref/OpenCVRef_highgui.htm
#ifdef _CH_
#pragma package <opencv>
#endif

#ifndef _EiC
#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <stdlib.h>
#endif

IplImage* color_img;
int posicion[1000][2],posicion_ix=0;

void on_mouse( int event, int x, int y, int flags, void* param )
{
    if( !color_img )
        return;

    switch( event )
    {
		case CV_EVENT_LBUTTONDOWN:
        {
			posicion[posicion_ix  ][0]=x;
			posicion[posicion_ix++][1]=y;
			printf("\nx,y= %4i\t%4i",x,y);
        }
        break;
    }
}

int main()
{
    char filename[1024]="brick2.jpg";

    if( (color_img = cvLoadImage(filename,1)) == 0 )
	{
		printf("\nERROR, imagen %s no esta");
		getchar();getchar();return 0;
	}

    printf( "Hot keys: \n"
            "\tESC - save & quit the program\n");
        

    cvNamedWindow( "image", 1 );// 1=autosize on (al tamaño de la imagen) 
	int lo_diff = 20, up_diff = 20;
    cvCreateTrackbar( "lo_diff", "image", &lo_diff, 255, NULL );
    cvCreateTrackbar( "up_diff", "image", &up_diff, 255, NULL );

    cvSetMouseCallback( "image", on_mouse, 0 );
    cvShowImage( "image", color_img );

    for(;;)
    {
        int c;
        
        c = cvWaitKey(0);
        switch( (char) c )
        {
        case '\x1b':
            printf("Exiting ...\n");
            goto exit_main;
        }
    }

exit_main:

    cvReleaseImage( &color_img );
    return 1;
}

