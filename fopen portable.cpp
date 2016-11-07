//fopen portable version:
#include <stdio.h>

FILE *fileopen1(string fileName, const char * mode)
{
#if _MSC_VER >= 1400
	FILE * fp;
	if (fopen_s(&fp, fileName.c_str(), mode) == 0) {
		return fp;
	}
	return NULL;
#else
	return fopen(fileName.c_str(), mode);
#endif
}