#ifndef ARENA_INCLUDED
#define ARENA_INCLUDED
#include"except.h"
#define T Arena_T
typedef struct  T *T;

extern const Except_T Arena_NewFailed;
extern const Except_T Arena_Failed;

// 定义 创建 和 销毁
// 创建 一个 新 的 实存块，并 返回 一个 指向 实存块 的隐式 指针 
// 这些 指针然后 被 传递给 其他实存块的函数 
extern T Arena_new (void);
// 释放与某个实存块*ap 相关的内存单元，然后销毁实存块本身，并清除*ap
extern void Arena_dispose(T *ap);

extern void *Arena_alloc(T arena,long nbytes,const char *file,int line);
extern void *Arena_calloc(T arena,long count,long nbytes,const char *file,int line);
extern void Arena_free(T arena);

#undef T
#endif
