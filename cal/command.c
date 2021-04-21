#include<stdio.h>
#include<stdlib.h>

int main(int argc,char **argv){

    // while(*++argv!=NULL){
    //     printf("%s\n",*argv);
    // }
    // printf("%s\n",**argv);
    while (argv++!=NULL)
    {
        printf("%s\n",*argv);
    }

    // perror("hello world");
    
    return EXIT_SUCCESS;
}