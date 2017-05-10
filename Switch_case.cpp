#include <stdio.h>
//Do not pass through all cases!!: run in debug mode 
//Not needed braquets {} 

#pragma warning(disable:4996) //o cualquier otro 

int main()
{
	printf("Seguir en modo debug\n");
	long i,j=0;
	for (i=0;i<5;i++)
	{
		switch (i)
		{
		case 0:
			printf("i==0\n");
			j+=i;
			break;
		case 1:
			printf("i==1\n");
			j+=i;
			break;
		case 2:
			printf("i==2\n");
			j+=i;
			break;
		default:
			printf("i>3\n");
			j++;
			break;
		}
	}
	printf("j=%li\n  FIN \n",j);
	getchar();getchar();
	return 1;
}

