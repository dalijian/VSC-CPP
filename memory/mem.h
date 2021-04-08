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

// 分配 了 一个 未 初始化 的 存储 块 来 存储 *p,并 把 存储块 的 地址 赋 给 p 
#define NEW(p) ((p)=ALLOC((long)sizeof *(p)))
// 不同 的 是 它 同时 也 清除了 存储 块 中 的 内容 
#define NEW0(p)((p)=CALLOC(1,(long)sizeof *p)))

extern void Mem_free(void *ptr,const char *file,int line);
#define FREE(ptr)((void)(Mem_free((ptr),__FILE__,__LINE__),(ptr)=0))
// 第一个参数 存放 需要 改变 大小 的 存储块 的 地址 的 指针 。
// Mem_resize 扩充或 缩小 该 存储块 ，使他 至少 有 nbytes 的 存储 单元 ，进行 适当 的边界 调整，并 返回 一个 指向 调整 过 的 存储 块 的 指针 。
//因此 逻辑上 Mem_resize 等价 于 分配 一个 新 的 存储 块 ，从 ptr 复制 一 部分 或 所有 的 数据 到 新的 存储 块 中 ，并 释放 ptr.
//如果 Mem_resize 不能 分配 一个 新的 存储 块 ，那么 它 将 会 产生 异常 Mem_Failed,file 和 line 为 异常 产生 的 位置 。 
// 如果 nbytes 超过了 ptr 指向 的 存储 块 的 大小，那么 多余 的 字节 将 不 被 初始化，否则 ，从 ptr 开始 的 nbytes 将 被 复制到 新的存储块 中 
extern void *Mem_resize(void *ptr,long nbytes,const char *file,int line);
#define RESIZE(ptr,nbytes)((ptr)=Mem_resize((ptr),(nbytes),__FILE__,__LINE__))


#endif