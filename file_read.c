#include <stdio.h>

int main()
{
   FILE *fp = NULL;
   char buff[25500];

   fp = fopen("‪C:\\Users\\lijian\\Desktop\\context2.xml", "w+");
   fscanf(fp, "%s", buff); //写入的时候和平常没有区别，还是只有字符串变量前不加‘&’，其他int、double等类型前都要加‘&’符号
   printf("1: %s\n", buff);

   fgets(buff, 25500, (FILE *)fp); //scanf遇到空格就会断开，gets会读取空格，遇到换行就结束
   printf("2: %s\n", buff);        //255是限制最大读取内容长度

   fgets(buff, 255, (FILE *)fp);
   printf("3: %s\n", buff);
   fclose(fp);
}