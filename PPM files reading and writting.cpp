
#include <iostream>
#pragma warning(disable:4996) //disable deprecateds
using namespace std;
typedef unsigned char uchar;

//Lee de ficheros:
void leelin(FILE *strin, char *linea);

bool read_image_ppm(char *filename, uchar  *&data, int &xmax1,int &ymax1);
bool save_image_ppm(char *filename, uchar  *data,int xmax,int ymax);

void main()
{
	uchar *data=NULL;
	int xmax,ymax;
	read_image_ppm("2944_1.ppm",data,xmax,ymax);
	save_image_ppm("out.ppm",data,xmax,ymax);
	delete data;
	cout<<"===END==="<<endl;getchar();
}


bool read_image_ppm(char *filename, uchar  *&data, int &xmax1,int &ymax1)
{
	xmax1=ymax1=0;
	FILE *str = fopen(filename, "rb");
	if (str == NULL) 	{ 		printf("Couldn't open %s for reading!\n", filename);getchar(); 		return false; 	}
	char linea[1024];
	leelin(str,linea);if(linea[0]!='P'||linea[1]!='6')  { 		printf("%s PPM file not type P6, so couldn't read! \n", filename);getchar();		return false; 	}
	leelin(str,linea);if(linea[0]=='#') leelin(str,linea);
	char *ptr=linea;xmax1=strtol(ptr,&ptr,10);ymax1=strtol(ptr+1,&ptr,10);leelin(str,linea);
	if (xmax1<1||xmax1>90000||ymax1<1||ymax1>90000) { 		printf("%s PPM file xmax or ymax is wrong= %i %i, so couldn't read! \n", filename,xmax1,ymax1);getchar();		return false; 	}
	data=new uchar[xmax1*ymax1*3];
	for (int j = 0; j < ymax1; j++) 
		fread(&data[3*j*xmax1], 1, 3*xmax1, str);
	fclose(str);
	return true;
}



bool save_image_ppm(char *filename, uchar  *data,int xmax1,int ymax1)
{
	FILE *output = fopen(filename, "wb");
	if (output == NULL)
	{
		printf("Couldn't open %s for writing!\n", filename);
		return false;
	}
	fprintf(output, "P6\n%d %d\n%d\n", xmax1, ymax1, 255);
	for (int j = 0; j < ymax1; j++) 
		fwrite(&data[3*j*xmax1], 1, 3*xmax1, output);
	fclose(output);
	return true;
}


void leelin(FILE *strin,char *linea)
{
	//removes 0x0D and 0x0A
	int i;
	linea[0]='\0';
	char *ptr=linea;
	for (i=0;(i<1024 && !feof(strin)); i++)
	{
		*ptr++ = fgetc(strin);
		//fscanf(strin, "%c", ptr++);  //OLD!!
		if (ptr[-1] == 10)
			break;
	}
	if (i>=1)
		ptr[-1]='\0';
	else
		linea[0]='\0';
	if (i>2 && ptr[-2]==0x0D)
		ptr[-2]='\0';
}
