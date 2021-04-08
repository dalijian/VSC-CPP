
#include "except.h"

typedef struct  Except_Frame Except_Frame;

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
// 指向 异常 栈顶 的 异常 帧 
extern Except_Frame *Except_stack;

enum {
    Excpet_entered=0,Except_raised,Except_handled,Except_finalized
};
#define TRY do{
    volatile int Except_flag;
    Except_Frame Except_frame;

    Except_flag =setjmp(Except_frame.env);
    if (Except_flag==Except_entered)
    {
        S
        if (Except_flag==Except_entered)
        {
            Except_stack =Except_stack->prev;
        }else if(Except_frame.exception==&(e1)){
            Except_flag=Except_handled;
            S1
            if (Except_flag==Except_entered)
            {
                Except_stack=Except_stack->prev;
            }else if(Except_frame.exception==&(e2)){
                Except_flag=Except_handled;
                S2
                if (Except_flag==Except_entered)
                {
                   Except_stack=Except_stack->prev;
                }
                
            }else if(Except_frame.exception==&(en)){
                Except_flag=Except_handled;
                Sn
                if (Except_flag==Except_entered)
                {
                   Except_stack=Except_stack->prev;
                }
                else{
                    Except_flag=Except_handled;
                    S0
                    if (Except_flag==Except_entered)
                    {
                        Except_stack=Except_stack->prev;
                    }
                    
                }
                if (Except_flag==Except_raised)
                {
                    Except_raise(Except_frame.exception,Except_frame.file,Except_frame.line);
                }
            }
            while(0);
        }
        
    }
    
}

