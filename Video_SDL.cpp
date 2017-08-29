#include "Video_SDL.h"


void c_video::init(void)//si *video=0 entonces abro la camara por defecto
{
	set_screen_name("ECOSCALE project video screen. Acciona Infraestructuras");


	//=============== SDL===================
	window = NULL; screen = NULL;


	//SDL output display setup:
	//=============== SDL===================
	window = NULL; screen = NULL;
	//SDL output display setup:
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
	{
		printf("Could not initialize SDL - %s\n", SDL_GetError()); getchar(); getchar();
		exit(1);
	}
	window = SDL_CreateWindow("Acciona Infraestructuras S.A. ECOSCALE project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, xmax, ymax, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError()); getchar(); getchar();
		exit(1);
	}
	//Get window surface
	screen = SDL_GetWindowSurface(window);
	//Fill the surface white
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));

	bgry = (uchar *)screen->pixels;//4 bytes/pixel, ojo!
	//	struct SwsContext * img_convert_ctx = NULL; img_convert_ctx = sws_getCachedContext(img_convert_ctx, w, h, (PixelFormat) PIX_FMT_YUV420P, w, h, (::PixelFormat) PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);
}

c_video::~c_video()
{
	set_screen_name("=============== END video. ACCIONA INFRAESTRUCTURAS SA ================");
	// Free the RGB image;
	SDL_Quit();
}

//Retorna 0 al finalizar el video


void c_video::show(uchar *frame)
{
	uchar *ptr1 = bgry, *ptr2 = frame;
	for (long i = 0; i < pixels; i++)
	{
		*ptr1++ = *ptr2++;//b
		*ptr1++ = *ptr2++;//g
		*ptr1++ = *ptr2++;//r
		ptr1++;//Y
	}
	SDL_UpdateWindowSurface(window);
}


// save image as a PPM
bool c_video::save_image_ppm(char *filename, uchar  *data)
{
	long xmax1 = xmax;
	long ymax1 = ymax;
	FILE *output = fopen(filename, "wb");
	if (output == NULL)
	{
		printf("Couldn't open %s for writing!\n", filename);
		return false;
	}
	fprintf(output, "P6\n%d %d\n%d\n", (int)xmax1, (int)ymax1, 255);
	for (long j = 0; j < ymax1; j++) {
		for (long i = 0; i < xmax1; i++) {
			fwrite(&data[3L * (j*xmax1 + i)], 1, 3, output);
		}
	}
	fclose(output);
	return true;
}

bool c_video::save_image_ppmBGR(char *filename, uchar  *data)
{
	long xmax1 = xmax;
	long ymax1 = ymax;
	FILE *output = fopen(filename, "wb");
	if (output == NULL)
	{
		printf("Couldn't open %s for writing!\n", filename);
		return false;
	}
	fprintf(output, "P6\n%d %d\n%d\n", (int)xmax1, (int)ymax1, 255);
	for (long j = 0; j < ymax1; j++) {
		for (long i = 0; i < xmax1; i++)
		{
			fputc(data[3L * (j*xmax + i) + 2], output);
			fputc(data[3L * (j*xmax + i) + 1], output);
			fputc(data[3L * (j*xmax + i)], output);
		}
	}
	fclose(output);
	return true;
}

// read image as a PPM
bool c_video::read_image_ppm(char *filename, uchar  *data)
{
	long xmax1 = xmax;
	long ymax1 = ymax;
	long kaka;
	FILE *str = fopen(filename, "rb");
	if (str == NULL)
	{
		printf("Couldn't open %s for reading!\n", filename);
		return false;
	}
	fscanf(str, "P6\n%d %ld\n%ld\n255\n", &xmax1, &ymax1, &kaka);
	for (long j = 0; j < ymax1; j++) {
		for (long i = 0; i < xmax1; i++) {
			fread(&data[3L * (j*xmax1 + i)], 1, 3, str);
		}
	}
	fclose(str);
	return true;
}



