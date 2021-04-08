#include <stdio.h>
int strcmp(char *s, char *t);
int main()
{
    printf("storage size for int:%d \n",sizeof(int));
    printf("begin \n");

   char  *v = "lijian";
    while (*v)
    {   
        printf("hello"+1);
        printf("v=" +(int) *v);
        printf("\n");
        *v++;
    }

    while ('\0')
    {
        printf(" '\0' is empty");
    }
    printf("end");
}