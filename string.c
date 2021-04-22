#include <stdio.h>
#include <string.h>

struct Book
{
   int price;
   char *content;
};
int main()
{
   // 数组 初始化
   char test[4];
   char greeting[6] = {'H', 'e', 'l', 'l', 'o'};
   // printf(test);
   printf("Greeting message: %s\n", greeting);

   // printf(greeting);

   printf("test message: %s\n", test);

   struct Book book;
   book.content = "wer";
   memcpy(NULL, greeting, 3);
   // char *pp=greeting;  怎么 报错 
   strcpy(book.content, "hello world");
   printf("test message: %s\n", book.content);

   return 0;
}