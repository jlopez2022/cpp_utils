/* fwrite example : write buffer */
#include <stdio.h>

class c_clase
{
public:
	double xyz[20][3];
	int pos;
};


int main ()
{
	c_clase clase1,clase2,clase3,clase4;
	int i,j;
	for (i=0;i<20;i++) for (j=0;j<3;j++) { clase1.xyz[i][j]=11000*i+j;clase2.xyz[i][j]=22000*i+j;}

	FILE *str;
	str = fopen ("myfile.bin", "wb");
	fwrite (&clase1 , 1, sizeof(c_clase), str);
	fwrite (&clase2 , 1, sizeof(c_clase), str);
	fclose (str);

	str = fopen ("myfile.bin", "rb");
	fread (&clase3 , 1, sizeof(c_clase), str);
	fread (&clase4 , 1, sizeof(c_clase), str);
	fclose (str);

	printf("\nEND");getchar();getchar();
	return 0;
}