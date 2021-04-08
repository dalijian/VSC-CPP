#include <stdio.h>

const int MAX = 3;

int main ()
{
   int  var[] = {10, 100, 200};
   int  i, *ptr;
   /* 指针中的数组地址 */
   ptr = var;
   for ( i = 0; i < MAX; i++)
   {
       // 拿指针的 地址 
      printf("Address of var[%d] = %x\n", i, ptr );
      //   拿指针变量的值
      printf("Value of var[%d] = %d\n", i, *ptr );
      /* 移动到下一个位置  因为变量指针可以递增，而数组不能递增*/
      ptr++;
   }
   return 0;
}