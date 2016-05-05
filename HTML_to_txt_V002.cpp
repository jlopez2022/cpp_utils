// Ver: http://www.codeproject.com/Articles/11902/Convert-HTML-to-Plain-Text  Convert HTML to Plain Text
//Falla los acentos


#include "stdio.h"
#include <string.h>
#include <stdlib.h>     /* atol */
#include <ctype.h>


//Extrae todo lo que hay entre <p....> y </p>. Si encontrara en medio <...> lo elimina
void extrae_2(char *ptr1,char *ptr2);


//quita de ptr11 el texto que empieza en "desde" hasta "hasta", ambos incluidos y lo mete en ptr2
void elimina(char *ptr1,char *ptr2,char *desde,char *hasta);
//quita de ptr11 el texto que empieza el char "desde" hasta "hasta", ambos incluidos y lo mete en ptr2
void elimina(char *ptr1,char *ptr2,char desde,char hasta);
//quita de ptr11 el texto "texto" y lo mete en ptr2
void elimina(char *ptr1,char *ptr2,char *texto);


//sustitute en ptr11 el texto "antes" por el texto "despues" y lo mete en ptr2
void sustituye(char *ptr1,char *ptr2,char *antes,char *despues);

//cambia &#xxx; por ascii xxx
void sustituyeascii(char *ptr1,char *ptr2);

//Se queda con ascii 9,10,13 (\t,\n,\r), 32-128 y 145-253 incluidos
void eliminararos(char *ptr1,char *ptr2);

//Elimina doble \t,\n,\r y espacios
void eliminaduplicados(char *ptr1,char *ptr2);

int main()
{
	//"Texto del que se eliminan cosas a escribir como quotoes y demas"
	//char p1[]="Texto del que se elimi&quot;&quot;&quot;na&quot;n co&quot;sas a es&quot;cribir como&quot; quotoes y de&quot;mas",p2[1024];
	//elimina(p1,p2,"&quot;");
	//char p1[]="Text<kaka>o del que se el<kaka><kaka>iminan cosas a escri<a>bir como quotoes y<kakakaka><><a> demas",p2[1024];
	//elimina(p1,p2,'<','>');



	FILE *strin,*strout;   errno_t err,err1;
//	err= fopen_s(&strin,"data/prueba.htm","r");
	err= fopen_s(&strin,"data/Yahoo.htm","r");
	err1=fopen_s(&strout,"data/out.htm","w");
	if ((err)||(err1)) 	{  printf("ERROR en ficheros");getchar();getchar(); return -1;  }
	char ch;
	long size_buffer1=0,size_buffer2,sizeant=0;
	while(!feof(strin))
	{
		ch=fgetc(strin);
		size_buffer1++;
	}
	printf("Tamano buffer1=%li",size_buffer1);sizeant=size_buffer1;
	rewind(strin);
	char *buffer1=new char[size_buffer1];
	char *buffer2=new char[size_buffer1];
	char *buffer3;
	long i;
	for (i=0;i<(size_buffer1-1);i++)
	{
		buffer1[i]=fgetc(strin);
	}
	buffer1[i]='\0';
	extrae_2(buffer1,buffer2);buffer3=buffer1;buffer1=buffer2;buffer2=buffer3;
	sizeant=size_buffer1;size_buffer1=strlen(buffer1);printf("\nTamano buffer2 1=%li %li",size_buffer1,size_buffer1-sizeant);

	elimina(buffer1,buffer2,"&quot;");buffer3=buffer1;buffer1=buffer2;buffer2=buffer3;
	sizeant=size_buffer1;size_buffer1=strlen(buffer1);printf("\nTamano buffer2 2=%li %li",size_buffer1,size_buffer1-sizeant);

	elimina(buffer1,buffer2,"(EFE)");buffer3=buffer1;buffer1=buffer2;buffer2=buffer3;
	sizeant=size_buffer1;size_buffer1=strlen(buffer1);printf("\nTamano buffer2 3=%li %li",size_buffer1,size_buffer1-sizeant);

	eliminaduplicados(buffer1,buffer2);buffer3=buffer1;buffer1=buffer2;buffer2=buffer3;
	sizeant=size_buffer1;size_buffer1=strlen(buffer1);printf("\nTamano buffer2 4=%li %li",size_buffer1,size_buffer1-sizeant);

	//Imprimo el ultimo buffer. ¡¡OJO!! pudiera ser buffer1 ó 2, el último válido
	printf("\nTamano buffer1 FIN=%li",strlen(buffer1));
	char *ptr;
	ptr=buffer1;
	while(*ptr)
	{
		fputc(*ptr++,strout);
	}
	fputc(*ptr++,strout);//El null del final
	_fcloseall( );
	getchar();getchar();
	return 0;

}


void elimina(char *ptr1,char *ptr2,char *desde,char *hasta)
{
	char *ptr;
	while(1)
	{
		ptr=strstr(ptr1,desde);
		if (!ptr)//no existe
		{
			while (*ptr1!='\0')
			{
				*ptr2++=*ptr1++;
			}
			break;//se sale
		}
		while(ptr1<ptr)//copio hasta "desde"
		{
			*ptr2++=*ptr1++;
		}
		ptr1=ptr1+strlen(desde);//elimino desde que queda excluido
		ptr=strstr(ptr1,hasta);
		if (!ptr)
			break;
		ptr+=strlen(hasta);//elimino "hasta" que queda excluido
		while(ptr1<ptr)//Elimino "hasta" incluido
		{
			ptr1++;
		}
	}
	*ptr2='\0';//añado el null del final
}

//quita de ptr11 el texto que empieza el char "desde" hasta "hasta", ambos incluidos y lo mete en ptr2
void elimina(char *ptr1,char *ptr2,char desde,char hasta)
{
	char *ptr,*k1=ptr1,*k2=ptr2;
	while(*ptr1)
	{
		if (*ptr1==desde)
		{
			while(*ptr1&&*ptr1!=hasta) 
				ptr1++;
			if (*ptr1) 
				ptr1++;
		}
		else
			*ptr2++=*ptr1++;
	}
	*ptr2='\0';
}


//quita de ptr11 el texto "texto" y lo mete en ptr2
void elimina(char *ptr1,char *ptr2,char *texto)
{
	char *ptr;long z=strlen(texto);
	while(1)
	{
		ptr=strstr(ptr1,texto);
		if (!ptr) break;
		while (*ptr1 && ptr1<ptr)
			*ptr2++=*ptr1++;
		if (!ptr1) break;
		ptr1+=z;
	}
	while(*ptr1)
		*ptr2++=*ptr1++;
	*ptr2='\0';
}



//sustitute en ptr11 el texto "antes" por el texto "despues" y lo mete en ptr2
void sustituye(char *ptr1,char *ptr2,char *antes,char *despues)
{
	char *ptr,*k1=ptr1,*k2=ptr2;
	while(1)
	{
		ptr=strstr(ptr1,antes);
		if (!ptr)//no existe
		{
			while (*ptr1!='\0')
			{
				*ptr2++=*ptr1++;
			}
			break;//se sale
		}
		while(ptr1<ptr)//copio hasta "antes"
		{
			*ptr2++=*ptr1++;
		}
		ptr1=ptr1+strlen(antes);//elimino "hasta" que queda excluido
		*ptr2='\0';
		strcat(ptr2,despues); //añado trozo nuevo
		ptr2+=strlen(despues);
	}
	*ptr2='\0';//añado el null del final
}

//cambia &#xxx; por ascii xxx
void sustituyeascii(char *ptr1,char *ptr2)
{
	char *ptr,*k1=ptr1,*k2=ptr2;
	while(1)
	{
		ptr=strstr(ptr1,"&#");
		if (!ptr)//no existe
		{
			while (*ptr1!='\0')
			{
				*ptr2++=*ptr1++;
			}
			break;//se sale
		}
		while(ptr1<ptr)//copio hasta "antes"
		{
			*ptr2++=*ptr1++;
		}
		if (ptr1[2]!='x') //si no es &#x
		{
			char ch;
			ch=(char) atol(ptr1+2);
			*ptr2++=ch;
		}
		while(*ptr1++!=';');
	}
	*ptr2='\0';//añado el null del final
}


//Se queda con ascii 9,10,13 (\t,\n,\r), 32-128 y 145-253 incluidos
void eliminararos(char *ptr1,char *ptr2)
{
	char *ptr,*k1=ptr1,*k2=ptr2;
	while(*ptr1)
	{
		if (  (*ptr1=='\t')||(*ptr1=='n')||(*ptr1=='r')||(*ptr1==(char) 128)||( (*ptr1>=32)&&(*ptr1<=(char) 127) )||( (*ptr1>=(char) 145)&&(*ptr1<=(char) 253) )  )
		{
			*ptr2++=*ptr1++;
		}
		else ptr1++;
	}
	*ptr2='\0';//añado el null del final
}

//Elimina doble \t,\n,\r, espacio
void eliminaduplicados(char *ptr1,char *ptr2)
{
	char ant=(char) 255;
	while(*ptr1)
	{
		if (  (*ptr1==ant) && ( (*ptr1=='\t')||(*ptr1=='\n')||(*ptr1=='\r')||(*ptr1==' ') ) )
		{
			ant=*ptr1++;
		}
		else ant=*ptr2++=*ptr1++;
	}
	*ptr2='\0';//añado el null del final
}


//Extrae todo lo que hay entre <p....> y </p>. Si encontrara en medio <...> lo elimina
void extrae_2(char *ptr1,char *ptr2)
{
	char *ptr;
	while(*ptr1)
	{
		//1. Busco <p...
		ptr1=strstr(ptr1,"<p");
		if (!ptr1) break;
		while ((*ptr1++!='>')&& (*ptr1) ); //ahora busco ">"
		if (!ptr1) break;
		ptr=strstr(ptr1,"</p");//ahora busco </p>
		if (!ptr) break;
		while( (ptr1<ptr)&& (*ptr1) )
		{
			if (*ptr1=='<')
				while(*ptr1 && *ptr1++!='>');//Quito <...> de en medio
			else 
				*ptr2++=*ptr1++;//falta quitar <> de en medio
		}
	}
	*ptr2='\0';//añado el null del final
}


