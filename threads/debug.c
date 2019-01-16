// GDB debug test

#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h>

#define N 10
int a,b,c;

int func1(int x);
int func2();

int main()
{
  a = 0;
  b = 8;
  c = 7;
  a = 0xFF;
  a = 127;

  c = func1(c);
  printf("c = %d", c);//3xC
  b = func2();
  printf("b = %d", b);//77

  return 0;
}

int func1(int x)
{
  x = x*3;
  return x;
}

int func2()
{
  return 77;
}
