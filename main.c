#include <stdio.h>
 
int count ;
// 声明 外部 函数 
extern void write_extern();
 
 void main()
{
   count = 5;
   write_extern();
}