#include <stdio.h>
#include <stdlib.h>
// macro
#define TRUE 1
// prototype

void process_standard_input(void);
void process_file(char *file_name);


// data
int option_a,option_b;

int main(int argc,char **argv)
{
     while (argv++!=NULL)
    {
        printf("%s\n",*argv);
    }
    // 处理 选项 参数 ：跳到 下一个 参数 ，并 检查 它 是否 以 一个 横杠开头 

    // 命令 行 参数 可能 只能 处理 一次 ，因为 指向 参数 的 指针 在 内层 的 循环 中 被 破坏，如果 必须 多次 处理 参数 ，
    // 当 你 挨个 访问 列表 时，对 每个 需要 增值的 指针 都 作 一份 拷贝 。
    while( *++argv!=NULL && **argv=='-'){
        // 检查 横杠 后面 的 字母 
        // *++*argv 
        // 第一个 间接 访问 操作 访问 argv 所 指的 位置 ， *argv 
        // 然后 这个 位置 执行 自增 操作 。  ++*argv 
        // 最后 一个 间接 访问 操作 根据 自增后 的 指针 进行 访问  *++*argv 
        // switch (*++*argv)
        // {
        // case 'a':
        //     option_a=TRUE;
        //     break;
        // case 'b':
        //     option_b=TRUE;
        //     break;
        // default:
        //     break;
        // }

        while((opt=*++*argv)!='\0'){
            switch (opt)
            {
            case 'a':
                option_a=TRUE;
                break;
            
            default:
                break;
            }
        }
    }
    if(*argv==NULL){
        process_standard_input();
    }else{
        do{
            process_file(*argv);
        }while(*++argv!=NULL);
    }
    return EXIT_SUCCESS;
}

void process_standard_input(){
    printf("%s","filename is null");
}

void process_file(char *file_name){
    printf("filename=,%s\n",file_name);
}


void remain(){
    remainder =value %16;
    if(remainder<10){
        putchar(remainder+'0');
    }else{
        putchar(remainder-10+'A');
    }
}

void mystery(int n){
    n+=5;
    n/=10;
    printf("%s\n","****************************"+10-n);
}

void binary_to_ascii(unsigned int value){
    unsigned int quotient;

    quotient =value/10;
    if(quotient!=0){
        binary_to_ascii(quotient);
    }
    putchar(value % 10+'0');
}