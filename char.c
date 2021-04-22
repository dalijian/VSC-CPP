#include <stdio.h>
int main (){

    char str[]="hello world";

    
    printf("size=%d\n",sizeof str);
    printf("size=%d\n", str);

    printf("size=%d",str + sizeof str);
}