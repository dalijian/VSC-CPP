#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
void jmpfunction(jmp_buf env_buf);
int main()
{
    int val;
    jmp_buf env_buffer;

    /* 保存 longjmp 的调用环境 */
    val = setjmp(env_buffer);
    if (val != 0)
    {
        printf("从 longjmp() 返回值 = %s\n", val);
        exit(0);
    }
    printf("跳转函数调用===\n");
    jmpfunction(env_buffer);

printf("%s","******************");
 /* 保存 longjmp 的调用环境 */
    val = setjmp(env_buffer);
    if (val != 0)
    {
        printf("从 longjmp() 返回值 = %s\n", val);
        exit(0);
    }
    return (0);
}

void jmpfunction(jmp_buf env_buf)
{
    longjmp(env_buf,1);
}