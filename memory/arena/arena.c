#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "except.h"
#include "arena.h"
#define T Arena_T
// 为 避免 收集 太多 的 内存 空间 ，Arena_free 使得 在 freechunks 中 存储 不超过 THRESHOLD
#define THRESHOLD 10
const Except_T Arena_NewFailed = {"Arena Creation Failed"};
const Except_T Arena_Failed = {"Arena Allocation Failed"};

static T freechunks;
static int nfree; // 标识 链表 中 存储块 的 数目
// 内存 存储块  类似 于 NIO 的  bytebuffer ，avail~limit 为 可用 区间
struct T
{
    T prev;      // 指向 储存块 的 头，该 存储块
    char *avail; // 指向 该 存储块 的 第一个 空闲 位置 ，从 avail  直到 limit 的 空间 是 可以 分配 的
    // 当 N 不 超过 limit-avail 时，为了 分配 N 个 字节 的 存储 块，avail 将 增加 N,并 返回 保存 在 新 存储 块 的 头部 。
    // 因此 实存块 结构 实际 是 一个 存储块 链表，该 链表 通过 每个 存储 块 头部 的 实存块 结构 副本中 的 prev 字段 连接起来
    char *limit; // 指向 紧靠 存储块 末尾 的 下一个 内存 单元
};
// 生成 一个 空 实存块
T Arena_new(void)
{
    T arena = malloc(sizeof(*arena));
    if (arena == NULL)
    {
        RAISE(Arena_NewFailed);
    }
    arena->prev = NULL;
    arena->limit = arena->avail = NULL;
    return arena;
}

void Arena_dispose(T *ap)
{
    assert(ap && *ap);
    Arena_free(*ap);
    free(*ap);
    // 清除 指向 实存块 的 指针
    *ap = NULL;
}
void *Arena_alloc(T arena, long nbytes, const char *file, int line)
{
    assert(arena);
    assert(nbytes > 0);

    nbytes = ((nbytes + sizeof(union align) - 1) / (sizeof(union align))) * (sizeof(union align));
    // 当 要 分配 的 nbytes 大于 limit-avail 时 ，申请 新的 chunk
    // while 循环 会 尝试 再次 分配 ，但他 任然 有 可能 失败 ，如果 新的 存储块 来自 freechunks,
    // 它 就 可能 太小 以至于 不能 满足 需求 ，所以 用 while 循环 代替 if
    while (nbytes > arena->limit - arena->avail)
    {
        T ptr;
        char *limit;

        if ((ptr = freechunks) != NULL)
        {
            // 从 freechunks 链表 中 拿到 chunk
            freechunks = freechunks->prev;
            nfree--;
            limit = ptr->limit;
        }
        else
        {
            // 如果 必须 分配 一个 新的 存储块，那么 需要 分配 存储块 足够 大，可以 保存 一个 实存块 结构 加上 nbytes 空间，
            // 并 还 留有 10K 字节 的 可用 空间
            long m = sizeof(union header) + nbytes + 10 * 1024;
            ptr = malloc(m);
            if (ptr == NULL)
            {
                if (file == NULL)
                {
                    RAISE(Arena_Failed);
                }
                else
                {
                    Except_raise(&Arena_Failed, file, line);
                }
            }
            limit = (char *)ptr + m;
        }
        // 分配 一个 新的 存储块 后， *arena 的 当前 值 保存 在 新的 存储 块 的 开头 ，
        // 并且 arena 的 字段 已被 初始化 ，使得 分配 可以 继续

        *ptr = *arena;
        arena->avail = (char *)((union header *)ptr + 1);
        arena->limit = limit;
        arena->prev = ptr;
    }
    arena->avail += nbytes;
    return arena->avail - nbytes;
}

void *Arena_calloc(T arena, long count, long nbytes, const char *file, int line)
{
    void *ptr;

    assert(count > 0);
    ptr = Arena_alloc(arena, count * nbytes, file, line);
    // 复制字符 '\0' （一个无符号字符）到参数 ptr 所指向的字符串的前 count*nbytes  个字符。
    memset(ptr, '\0', count * nbytes);
    return ptr;
}
// 将 存储块 添加 到 空闲 的 存储块 链表 中，
// 同时 在 遍历 链表 时 也把 *arena 恢复 到 初始状态

void Arena_free(T arena)
{
    assert(arena);
    while (arena->prev)
    {
        // arena->prev 指向 的 实存块 结构 中 的 所以 字段 复制 到 tmp 中 ，
        // *arena=tmp 相当于 有 存储块链表 形成 的 实存块结构栈 的 出栈操作
        // 一旦 整个 链表 被 遍历 ，那么 arena 的 所有 字段 都 应该 为 空
        struct T tmp = *arena->prev;
        if (nfree < THRESHOLD)
        {
            arena->prev->prev = freechunks;
            freechunks = arena->prev;
            nfree++;
            freechunks->limit = arena->limit;
        }
        else
        {
            // nfree 到达了 THRESHOLD，以后 的 存储块 通过 调用 free 来 释放 
            free(arena->prev);
        }
        *arena = tmp;
    }
    assert(arena->limit == NULL);
    assert(arena->avail == NULL);
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
// 共用体 header 保证 arena->avail 的 值 是在 这个 新 存储 块 中 第一次 分配 时 进行 过适当 边界 调整 的 地址
union header
{
    struct T b;
    union align a;
};
