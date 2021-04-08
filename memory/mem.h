#ifndef MEM_INCLUDED
#define MEM_INCLUDED
#include "except.h"

extern const Except_T Mem_Failed;

extern void *Mem_alloc(long nbytes,const char *file,int line);
// 分配足够 大的 存储 块，使得 可以 存下 count 个 元素 的 数组 ，
// 每个 元素 的 大小 为 nbytes,并 返回 一个 指向 第一个 元素 的 指针 
extern void *Mem_calloc(long count,long nbytes,const char *file,int line);

#define ALLOC(nbytes) Mem_alloc((nbytes),__FILE__,__LINE__)
#define CALLOC(count,nbytes) Mem_calloc((count),(nbytes),__FILE__,__LINE__)

#define NEW(p) ((p)=ALLOC((long)sizeof *(p)))
#define NEW0(p)((p)=CALLOC(1,(long)sizeof *p)))

extern void Mem_free(void *ptr,const char *file,int line);
#define FREE(ptr)((void)(Mem_free((ptr),__FILE__,__LINE__),(ptr)=0))

extern void *Mem_resize(void *ptr,long nbytes,const char *file,int line);
#define RESIZE(ptr,nbytes)((ptr)=Mem_resize((ptr),(nbytes),__FILE__,__LINE__))


#endif