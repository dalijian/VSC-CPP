#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "except.h"
#include "mem.h"

// 永 不释放 某个 分配函数 先前返回的地址 中 的 字节

// 链表 的 表头 是 一个 虚拟的 描述符 ， 是 链表 中 的 最后 一个 描述符 ， 它的 free 指向 第一个 描述符。
static struct descriptor freelist = {&freelist};

static struct descriptor
{
     struct descriptor *free; // 指向 第一个 描述符
     struct descriptor *link;
     const void *ptr;  // 存储 块 的 地址 ，用于 其他 地方 分配
     long size;        // 存储块 的 大小
     const char *file; // 分配 位置
     int line;
} * htab[2048];

//给定 一个 地址，查找 它 的 描述 符，返回 一个 指向 描述 符 的 指针 或者 返回 一个 空 指针
static struct descriptor *find(const void *ptr)
{
     struct descriptor *bp = htab[hash(ptr, htab)];
     while (bp && bp->ptr != ptr)
     {
          bp = bp->link;
     }
     return bp;
}
// hash 宏 指令 以 位模式 来 处理 地址 ，右移三位，然后 减去 它 并 对 htab 大小 取模，查询 在 htab 中 的 位置
#define hash(p, t) ((unsigned long)(p) >> 3) & (sizeof(t) / sizeof((t[0]) - 1))

void Mem_free(void *ptr, const char *file, int line)
{
     // 如果 ptr 非空 且是 一个 有效 的 地址 ，那么 存储块 是 通过 把它添加到空闲的列表中来完成存储空间的释放
     if (ptr)
     {
          struct descriptor *bp;
          // 避免 了 对 无效地址调用 find 函数 ，这些地址不是最严格 的地址边界的倍数 ，因此 不可能 是 有效 的 存储块 指针
          if (((unsigned long)ptr) % (sizeof(union align)) != 0 || (bp = find(ptr)) == NULL || bp->free)
          {
               Except_raise(&Assert_Failed, file, line);
          }

          bp->free = freelist.free;
          freelist.free = bp;
     }
}

union align
{
     int i;
     long l;
     long *lp;
     void *p;
     void (*fp)(void);
     float f;
     double d;
     long double ld;
};

void *Mem_resize(void *ptr, long nbytes, const char *file, int line)
{
     struct descriptor *bp;
     void *newptr;
     assert(ptr);
     assert(nbytes > 0);
     newptr = Mem_alloc(nbytes, file, line);
     memcpy(newptr, ptr, nbytes < bp->size ? nbytes : bp->size);
     Mem_free(ptr, file, line);
     return newptr;
}
void *Mem_calloc(long count, long nbytes, const char *file, int line)
{
     void *ptr;
     assert(count > 0);
     assert(nbytes > 0);
     ptr = Mem_alloc(count * nbytes, file, line);
     memset(ptr, '\0', count * nbytes);
     return ptr;
}

static struct descriptor *dalloc(void *ptr, long size, const char *file, int line)
{
     static struct descriptor *avail;
     static int nleft;
     if (nleft <= 0)
     {
          //    分配所需的内存空间，并返回一个指向它的指针。
          // 调用 malloc 可能 会 返回 一个 空 指针，而 dalloc 又 把 这个 空指针 传递 给 dalloc 的 调用者
          avail = malloc(NDESCRIPTORS * sizeof(*avail));
          if (avail == NULL)
          {
               return NULL;
          }
          nleft = NDESCRIPTORS;
     }
     // 封装 descriptor 
     avail->ptr = ptr;
     avail->size = size;
     avail->file = file;
     avail->line = line;
     avail->free = avail->link = NULL;
     nleft--;
     return avail++;
};
#define NDESCRIPTORS 512

// 使用 first-fit 算法 （搜索 freelist 链表 ，找到 第一个 能够 满足分配要求的存储块，然后 从 该 存储块 中 划分 出 所 需要 的 存储块
// 如果 freelist  链表 中 没有 合适 的 存储 块， 然后 从 该 存储 块 中 划分 出 所 需要 的 存储 块 并 把 它 添加 到 空闲 的 链表 中 ，然后 再次 查询 freelist 列表

void *Mem_alloc(long nbytes, const char *file, int line)
{
     struct descriptor *bp;
     void *ptr;
     assert(nbytes > 0);
     // 先 把 nbytes 向上 取整，使得 它 返回 的 每个 指针 都是 共用体 align 大小 的 倍数 
     nbytes = ((nbytes + sizeof(union align) - 1) / (sizeof(union align))) * (sizeof(union align));
     // freelist.free 指向 空闲存储块链表 的 起始 地址 ，也是 循环开始的地方
     // 第一个 大小超过nbytes 的 存储块 被 用来 进行 分配 。
     // 该 空闲 存储块 底部 的 nbytes 个 字节 被分隔出来，分割出来的存储块的描述符被创建，初始化并添加到htab中 后， 返回 该 存储块的地址 

     for (bp = freelist.free; bp; bp = bp->free)
     {
          // 保证 bp->ptr 的值 从 不会 被 重复 使用 ， 大的 空闲 存储块 被 划分 成 小的 存储 块 分配 给 小 的 需求，
          // 直到存储 块 的 大小 减小 到 sizeof(union align)个 字节 ，在 bp->size 小于 nbytes 的 时候 就 不再 分配 了
          // 每个 存储 块 的 前 sizeof(union align)个 字节 是 从 不 进行 分配 的 。   
          if (bp->size > nbytes)
          {
               bp->size -= nbytes;
               ptr = (char *)bp->ptr + bp->size;
               if ((bp = dalloc(ptr, nbytes, file, line)) != NULL)
               {
                    unsigned h = hash(ptr, htab);
                    bp->link = htab[h];
                    htab[h] = bp;
                    return ptr;
               }
               else
               {
                    RAISE(Mem_Failed);
               }
          }
          // 如果 bp 已到达 freelist (即 已 搜索到 链表的 最后 一个 存储 块),而 链表 中 没有 一个 存储块 的 大小 超过 nbytes,
          // 在 这种 情况 下，一个 新 的 大小 为 NALLOC + nbytes 个 字节 的 存储 块 ，被 添加 到 空闲 存储块链表的 表头 ，
          // 在 下一次 循环 的迭代中，它将 会被访问，并用来进行所需要的分配。
          //这个 新的存储块也有一个描述符，就好像它先前已被分配和释放过一样   
          if (bp == &freelist)
          {
               struct descriptor *newptr;

               if ((ptr = malloc(nbytes + NALLOC)) == NULL || (newptr = dalloc(ptr, nbytes + NALLOC, __FILE__, __LINE__)) == NULL)
               {
                    RAISE(Mem_Failed);
               }
               newptr->free = freelist.free;
               freelist.free = newptr;
               freelist.free = newptr;
          }
     }
     assert(0);
     return NULL;
}
#define NALLOC 4096;
