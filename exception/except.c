
#include "except.h"
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#define T Except_t
Except_Frame *Except_stack = NULL;

typedef struct Except_Frame Except_Frame;
// 定义 异常 结构
struct Except_Frame
{
    // 指向 它的 前 一 帧
    Except_Frame *prev;
    jmp_buf env;
    // 异常 产生 的 文件
    const char *file;
    // 异常 所在 行号
    int line;
    // 异常 信息
    const T *exception;
};
// 指向 异常 栈顶 的 异常 帧 , 这个 是 个 全局 属性 
extern Except_Frame *Except_stack;

enum
{
    Excpet_entered = 0, // 表示 进入 TRY语句 ，并且 将 某个 异常 帧 压入 异常 栈
    Except_raised,      // 表示 发生 了 异常
    Except_handled,     // 表示 异常 已 处理
    Except_finalized
};


// macros

#define EXCEPT(e)                      \
    if (Except_flag == Except_entered) 
    {
    Except_stack = Except_stack->prev;
}

else if (Except_frame.exception == &(e))
{
    // 异常 已 处理 
    Except_flag = Except_handled;
}

#define ELSE                           \
    if (Except_flag == Except_entered) 
    {
Except_stack = Except_stack->prev;
}
else
{
    Except_flag = Except_handled;
}

#define FINALLY                        \
    if (Except_flag == Except_entered) 
    {
Except_stack = Except_stack->prev;
    }
    {
        if (Except_flag == Except_entered)
        {
        Except_flag = Except_finalized;
        }
    }

#define END_TRY                        \
    if (Except_flag == Except_entered) 
    {
Except_stack = Except_stack->prev;
}
if (Except_flag == Except_raised){
    RERAISE;
}
while (0);

#define TRY \
    do      
    {
// 异常 标识
volatile int Except_flag;
// 异常 结构
Except_Frame Except_frame;

Except_frame.prev = Except_stack;
Except_stack = $Except_frame;

// 设置 信号 值
Except_flag = setjmp(Except_frame.env);
if (Except_flag == Except_entered)
{
    S if (Except_flag == Except_entered)
    {
        Except_stack = Except_stack->prev;
    }
    else if (Except_frame.exception == &(e1))
    {
        Except_flag = Except_handled;
        S1 if (Except_flag == Except_entered)
        {
            Except_stack = Except_stack->prev;
        }
        else if (Except_frame.exception == &(e2))
        {
            Except_flag = Except_handled;
            S2 if (Except_flag == Except_entered)
            {
                Except_stack = Except_stack->prev;
            }
        }
        else if (Except_frame.exception == &(en))
        {
            Except_flag = Except_handled;
            Sn if (Except_flag == Except_entered)
            {
                Except_stack = Except_stack->prev;
            }
            else
            {
                Except_flag = Except_handled;
                S0 if (Except_flag == Except_entered)
                {
                    Except_stack = Except_stack->prev;
                }
            }
            if (Except_flag == Except_raised)
            {
                Except_raise(Except_frame.exception, Except_frame.file, Except_frame.line);
            }
        }
        while (0)
            ;
    }
    }
}

void Except_raise(const T *e, const char *file, int line)
{
    Except_Frame *p = Except_stack;

    assert(e);
    if (p == NULL)
    {

        fprintf(stderr, "Uncaught exception");
        if (e->reason)
        {
            fprintf(stderr, " %s", e->reason);
        }
        else
        {
            fprintf(stderr, " at 0x%p", e);
        }
        if (file && line > 0)
        {
            fprintf(stderr, " raised at %s:%d \n", file, line);
        }
        fprintf(stderr, "aborting...\n") : fflush(stderr);
        abort();
    }
    p->exception = e;
    p->file = file;
    p->line = line;

    Except_stack = Except_stack->prev;
    longjmp(p->env, Except_raised);
}

// do {
//     create and push and Except_Frame
//     if (first return from setjmp){
//         S
//     }else if(exception is e1){
//         S1
//     }else if(exception is en){
//         Sn
//     }else {
//         S0
//     }
//     if(an exception occurred and wasn't handled)
//         RESAISE;
// } while(0)