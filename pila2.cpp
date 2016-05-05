/*
Pila que se crea y destruye en la clase cellc
Prueba pila. No funciona borracell:
Habria que ir destruyendo por bloques de la misma forma que se crearon
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#define PILASIZE 1024  //Tamaño de la pila de datos
#define TOPCELLS 40000
#define MAXDATOS 10


class cellc //Arbol de donde cuelgan los puntos
{
public:
	double valor;//Suma de todos los valores. El valor medio es valor/datos
	double *x;   // x[0..MAXDATOS]  
	short datos; //como maximo datos=MAXDATOS
	long indice;    //indice general

	//Variables globales:
	static cellc *pila_cell;//pila de cells
	static long indexc;     //indice de la pila
	static long indice_generalc;//indice general

	cellc *sig0,*sig1;

	void ini();  
	void nuevacell(); //mete nuevas cells en cell.sig0 y cell.sig1
	void copy(cellc *point); //copia desde point
};

cellc *cellc::pila_cell;
long cellc::indexc=PILASIZE;
long cellc::indice_generalc=0;

void cellc::copy(cellc *cell)//copia desde point
{
	memcpy(this,cell,sizeof(cellc));
}

void cellc::ini()
{
	datos=0; x=new double[MAXDATOS]; sig0=sig1=NULL;
	indexc++;
	indice=(indice_generalc++);
}

void cellc::nuevacell() //mete nuevas cells en cell.sig0 y cell.sig1
{
	if (indexc>=PILASIZE)//Si se han gastado todos los puntos, crear otro grupo
	{
		indexc=0;
		pila_cell=new cellc[PILASIZE];
	}
	sig0=pila_cell + indexc;sig0->ini();indexc++;
	sig1=pila_cell + indexc;sig1->ini();indexc++;
}

class cellmanager
{
public:
	cellc cell0,*cellx;//cell0 es la celula inicial y cellx es la ultima
	
	cellmanager();
	void borracells(); //NO FUNCIONA Borra todas las cells
private:
	void borracell(cellc *cell); //Borra las cells desde sig0 y sig1
};

cellmanager::cellmanager()
{
	cell0.indice_generalc=0;
	cell0.ini();
	cellx=&cell0;
}

void cellmanager::borracells() //borra todas las cells
{
	borracell(&cell0);
}

void cellmanager::borracell(cellc *cell) //borra todas las cells desde sig0 y sig1
{
	if (cell->sig0!=NULL) 
	{
		cellc *ptr;
		ptr=cell->sig0;
		borracell(ptr);
		delete[] ptr->x;
		delete ptr;
		cell->sig0=NULL;
		ptr=cell->sig1;
		borracell(ptr);
		delete[] ptr->x;
		delete ptr;
		cell->sig1=NULL;
		cell0.indice_generalc-=2;
	}
}

void main()
{

	//0. Prueba de copy
	{
		cellc cell[23];
		long i,j;
		for (i=0;i<20;i++)
		{
			cell[i].ini();
			for(j=0;j<10;j++)
				cell[i].x[j]=100000.0+i+j/100.0;
			cell[i].valor=800000.0+i;
			cell[i].indice=i;
			cell[i].sig0=&cell[i+1];
			cell[i].sig1=&cell[i+2];
		}
		cell[5].copy(&cell[15]);
		cell[6].copy(&cell[16]);
		cell[7].copy(&cell[17]);
	}
	
	cellmanager *manager=new cellmanager();
	cellc *cell0=&manager->cell0;


	//1. Creacion de cells
	{
		manager->cell0.nuevacell();
		cellc *ptr;
		for (long nivel=1;nivel<1000;nivel++)//menos de 1000 niveles
		{
			long top=1<<nivel;
			for (long j=0;j<top;j++) //se crean tantos elementos como 2^nivel
			{
				ptr=cell0;
				for (long niv2=0;niv2<nivel;niv2++)
				{
					if ( (j>>(nivel-niv2-1) ) & 1)
						ptr=ptr->sig1;
					else
						ptr=ptr->sig0;
				}
				ptr->nuevacell();
				if (ptr->indice_generalc>=(TOPCELLS-1))
				{
					j=nivel=2000000000;break;
				}
			}
		}
	}
	printf("\nStep 1. Creados: %li cells", manager->cell0.indice_generalc);
	double memoria;
	memoria=sizeof(cellc);
	printf("\nSize de cellc= %g bytes",memoria);
	memoria=(0.0+TOPCELLS*sizeof(cellc)+MAXDATOS*sizeof(double)*TOPCELLS ) /1024.0/1024.0;
	printf("\nMemoria gastada= %g megas",memoria);

	//2. Chequeo de los cells:

	{
		cellc *ptr;
		long nivmax;nivmax=(long) (log(TOPCELLS)/log(2));
		long oks=0;

		for (long nivel=0;nivel<(nivmax);nivel++)//menos de 1000 niveles
		{
			long top=1<<nivel;
			for (long j=0;j<top;j++) //se crean tantos elementos como 2^nivel
			{
				ptr=cell0;
				for (long niv2=0;niv2<nivel;niv2++)
				{
					if ( (j>>(nivel-niv2-1) ) & 1)
						ptr=ptr->sig1;
					else
						ptr=ptr->sig0;
				}
				if (ptr->sig0==NULL) continue;
				if (ptr->sig0->indice!= (2*ptr->indice+1))
				{
					printf("\nError en indice: %li sig0 indice:%li", ptr->indice,ptr->sig0->indice);
					char c;scanf("%c%c",&c,&c);
				}
				else oks++;
				if (ptr->sig1->indice!= (2*ptr->indice+2))
				{
					printf("\nError en indice: %li sig1 indice:%li", ptr->indice,ptr->sig1->indice);
					char c;scanf("%c%c",&c,&c);
				}
				else oks++;
			}
		}
		printf("\nChequeados y okeys = %li",oks);
	}

	//3. Destruccion de cells: NO FUNCIONA
	//manager->borracells();
	printf("\nStep 3. Quedan: %li cells", manager->cell0.indice_generalc);
	char c;scanf("%c%c",&c,&c);
}

