#ifndef EXCEPT_INCLUDED
#define EXCEPT_INCLUDED
// 用来 设置 异常 信号 
#include <setjmp.h>
// 这个指令告诉 CPP 定义 T 为 Except_T。
#define T Except_T
// 标识符 T  可作为类型 struct T  的缩写
typedef struct T
{
    // 异常 原因 
    char *reason;
} T;

#define RAISE(e) Except_raise(&(e), __FILE__, __LINE__)

void Except_raise(const T *e, const char *file, int line);
#define RERAISE Except_raise(Except_frame.exception, Except_frame.file, Except_frame.line);
#define RETURN swith(0) default : return

#undef T
#endif