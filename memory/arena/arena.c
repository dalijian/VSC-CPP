#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "except.h"
#include "arena.h"
#define T Arena_T


const Except_T Arena_NewFailed={"Arena Creation Failed"};
const Except_T Arena_Failed={"Arena Allocation Failed"};


struct T{
    T prev; // 指向 储存块 的 头，该 存储块 
    char *avail; // 指向 该 存储块 的 第一个 空闲 位置 ，从 avail  直到 limit 的 空间 是 可以 分配 的 
    // 当 N 不 超过 limit-avail 时，为了 分配 N 个 字节 的 存储 块，avail 将 增加 N,并 返回 保存 在 新 存储 块 的 头部 。
    // 因此 实存块 结构 实际 是 一个 存储块 链表，该 链表 通过 每个 存储 块 头部 的 实存块 结构 副本中 的 prev 字段 连接起来
    char *limit; // 指向 紧靠 存储块 末尾 的 下一个 内存 单元 
};

T Arena_new(void){
    T arena = malloc(sizeof(*arena));
    if(arena==NULL){
        RAISE(Arena_NewFailed);
    }
    arena->prev=NULL;
    arena->limit=arena->avail=NULL;
    return arena;
}
void Arena_dispose(T *ap){
    assert(ap&& *ap);
    Arena_free(*ap);
    free(*ap);
    *ap=NULL;
}
void *Arena_alloc(T arena,long nbytes,const char *file,int line){
    assert(arena);
    assert(nbytes>0);

    nbytes =((nbytes+sizeof(union align)-1)/(sizeof (union align)))*(sizeof(union align));

    while (nbytes>arena->limit-arena->avail)
    {
        T ptr;
        char *limit;

if((ptr=freechunks)!=NULL){
    freechunks =freechunks->prev;
    nfree--;
    limit=ptr->limit;
}else{
    long m= sizeof(union header )+nbytes +10*1024;
    ptr= malloc(m);
    if (ptr==NULL){
        if (file==NULL)
        {
             RAISE(Arena_Failed);
        }else{
            Except_raise(&Arena_Failed,file,line);
        }
        
       
    }
    limit =(char * ) ptr +m;
    
}

        *ptr=*arena;
        arena->avail=(char *)((union header *) ptr+1);
        arena->limit=limit;
        arena->prev=ptr;

    }
    arena->avail+=nbytes;
    return arena->avail-nbytes;
    
}

void *Arena_calloc(T arena,long count,long nbytes,const char *file,int line){
    void *ptr;

    assert(count>0);
    ptr=Arena_alloc(arena,count*nbytes,file,line);
    memset(ptr,'\0',count*nbytes);
    return ptr;
}

void Arena_free(T arena){
    assert(arena);
    while (arena->prev)
    {
       struct T tmp=*arena->prev;
      
      if (nfree<THRESHOLD)
      {
          arena->prev->prev=freechunks;
          freechunks=arena->prev;
          nfree++;
          freechunks->limit=arena->limit;
      }else{
          free(arena->prev);
      }
      

      *arena=tmp;
    }
    assert(arena->limit==NULL);
    assert(arena->avail==NULL);
    
}
#define THRESHOLD 10 
union align{
    int i;
    long l;
    long *lp;
    void *p;
    void (*fp)(void);
    float f;
    double d;
    long double ld;
};
union header {
    struct T b;
    union align a;
};
static T freechunks;
static int nfree;
