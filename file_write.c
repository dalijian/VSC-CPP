#include <stdio.h>

int main()
{
   FILE *fp;

   fp = fopen("‪C:\\Users\\lijian\\Desktop\\file_write.txt", "w+");
//    一个字符串写入到文件中
   fprintf(fp, "This is testing for fprintf...\n");
//    一个以 null 结尾的字符串写入到流中
   fputs("This is testing for fputs...\n", fp);
   fclose(fp);
}