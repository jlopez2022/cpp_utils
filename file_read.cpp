
#include <iostream>
#pragma warning(disable:4996) //disable deprecateds
using namespace std;
typedef unsigned char uchar;

bool read_kernel(const char *filename,char *&source);


void main()
{
	char *sourcekernel=NULL;
	if (read_kernel("file_read.cpp",sourcekernel))
	{
		cout<<sourcekernel<<endl;
		delete sourcekernel;
	}
	else
		cout<<"ERROR:Kernel not loaded!!!<<endl;

	cout<<"===END==="<<endl;getchar();
}




bool read_kernel(const char *filename,char *&source)
{
	FILE *fp;size_t program_size;
	fp = fopen(filename, "rb");	if (!fp) { 	printf("Failed to load kernel file %s\n",filename); 	return false; }
	fseek(fp, 0, SEEK_END);	program_size = ftell(fp);rewind(fp);
	source = new char[program_size + 1]; fread(source, sizeof(char), program_size, fp); source[program_size] = '\0';
	fclose(fp);return true;
}