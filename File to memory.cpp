#include <iostream>
using namespace std;
typedef unsigned char uchar;
#pragma warning(disable:4996) //disable deprecateds Allows using fopen and so on

void external_memory_allocation_function(char **data,int size)
{
	*data=new char[size];
}

void external_memory_allocation_function2(char *&data,int size)
{
	data=new char[size];
}

int load_file_to_memory(const char *filename, char *&result)
{
  size_t size = 0;
  FILE *f = fopen(filename, "rb");
  if (f == NULL)
  {
    result = NULL;cout<<"file opening fail file="<<filename<<endl;
    return -1; // -1 means file opening fail
  }
  //obtain filesize:
  fseek(f, 0, SEEK_END); size = ftell(f);fseek(f, 0, SEEK_SET);

  result = new char[size+1];
  if (size != fread(result, sizeof(char), size, f))
  {
    free(result);cout<<"file reading fail file="<<filename<<endl;
    return -2; // -2 means file reading fail
  }
  fclose(f);
  result[size] = 0;
  return (int) size;
}


void main()
{
	char *data=NULL;//=NULL to avoid error if the following memory allocation fails
	char *filename="External memory allocation.cpp";
	cout<<"Opening file: "<<filename<<":"<<endl;
	int size1=load_file_to_memory(filename,data);
	if (size1>1)
		cout<<data;
	else
		cout<<"Could not find the file. Check its name!"<<endl;
	delete[] data;data=NULL;
	cout<<endl<<endl<<"=== END ==="<<endl;getchar();
}