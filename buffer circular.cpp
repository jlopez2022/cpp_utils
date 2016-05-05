//buffer circular de longitud LON
#include <stdio.h>
#define LON  6

int buffer[LON],ix_buffer=0;

void buf_in(int val)
{
	buffer[ix_buffer]=val;
	ix_buffer=(ix_buffer+1) % LON;
}

int buf_out(int index)
{
	//if (ix_buffer>=index) return buffer[ix_buffer-index];
	//else                  return buffer[LON+ix_buffer-index];
	return buffer[(LON+ix_buffer-index-1) % LON];
}


void main()
{

	int i,j;
	for (i=10;i<34;i++)
	{
		buf_in(i+1000);
		printf("\n%i:",i);
		for (j=0;j<LON-1;j++) printf("%4li ",buf_out(j));
	}


	getchar();getchar();
}