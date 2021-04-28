#include<stdio.h>
#include<stdlib.h>

extern char **environ;

int main(){
    // environ 可以 直接访问 系统 环境 变量 
    char **env = environ;

    while(*env){
        printf("%s\n",*env);
        env++;
    }
    exit(0);
}