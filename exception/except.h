#ifndef EXCEPT_INCLUDED
#define EXCEPT_INCLUDED
// 用来 设置 异常 信号 
#include <setjmp.h>
// 这个指令告诉 CPP 定义 T 为 Except_T。
// Except_T 类型 的 一个 全局 或 静态变量 
#define T Except_T
// 标识符 T  可作为类型 struct T  的缩写
typedef struct T
{
    // 异常 原因 
    char *reason;
} T;
// types

// variables 

// functions

//macros 
#define RAISE(e) Except_raise(&(e), __FILE__, __LINE__);

#define RERAISE Except_raise(Except_frame.exception, Except_frame.file, Except_frame.line);
// 可以 将 RETURN 或是 RETURN e 扩展 成 句法 上 正确 的 c 语句 
#define RETURN swith(Except_stack=Except_stack->prev,0) default : return;

// void Except_raise(const T *e, const char *file, int line);



#undef T

#endif

// 异常 捕获 格式 
// TRY
//     S
// EXCEPT(e1)
//     S1
// EXCEPT(e2)
//     S2
// EXCEPT(e3)
//     S3
//     .
//     .
//     .
// EXCEPT(en)
//     Sn
// ELSE
//     S0
// END_TRY