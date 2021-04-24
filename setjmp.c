#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <assert.h>
void jmpfunction(jmp_buf env_buf);
int main()
{
    int val;
    jmp_buf env_buffer;

    /* 保存 longjmp 的调用环境 */
    val = setjmp(env_buffer);
    if (val != 0)
    {
        printf("从 longjmp() 返回值 = %d\n", val);
        // exit(0);
    }
    printf("tiao function ===\n");
    // assert(0); // 断言 抛出 异常 
    // assert(1); // 断言 不抛出 异常 
    // assert(1==2); // assert(expression) , 当 expression 为 false 时 抛出 异常 为 true 不抛出 
    jmpfunction(env_buffer);
}

void jmpfunction(jmp_buf env_buf)
{
    // 设置 env_buf  在 setjmp 会 自动 回调 
    longjmp(env_buf, 1);
}