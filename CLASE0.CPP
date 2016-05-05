#include <stdio.h>
#include "prue.h"



void main(void)
{
  char c;
  clase1 c1(10,11);
  printf("Control=%i\n",c1.CONTROL);
c1.min();
printf("Mínimo=%i\n",c1.res()); 
c1.max();
printf("Maximo=%i\n",c1.res()); 
scanf("%c%c",&c,&c);
}

clase1::clase1(int x,int y)
{m_x=x;m_y=y;CONTROL=333;} 

void clase2::in(int x)
{
  m_valor=x;
}


void clase1::min()				    
{
  result=min1(m_x,m_y);
}

void clase1::max()
{
  if (m_x>m_y) 
	result=m_x; 
  else 
	result=m_y;
}

int  clase1::res()
{return result;}

void clase1::inx(int x)
{m_x=x;}

void clase1::iny(int y)
{m_y=y;}

int min1(int x,int y)
  {
   if (x>y)
	return y;
   else
	return x;
  }
