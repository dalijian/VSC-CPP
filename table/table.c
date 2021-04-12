#include <limits.h>
#include <stddef.h>
#include "mem.h"
#include "assert.h"
#include "table.h"

#define T Table_T

struct T
{
    // cmp 和 hash 函数 与 某个 特定 的 表 关联 ， 因此 它们 都 存储 在 buckets 结构 中 的 元素
    int size;
    int (*cmp)(const void *x, const void *y);
    unsigned (*hash)(const void *key);

    int length;
    unsigned timestamp;
    struct binding
    {
        struct binding *link; // 处理 hash冲突
        const void *key;
        void *value;
    } * *buckets; // 指向 有 适当 元素 数目 的 数组
};
// 用 它 的 hint 参数 来 选择 一个 素数 作为 buckets 的 大小 ，
// 并且 保存 cmp 和 hash 或 保存 指向 静态函数 的 指针
// 用来 比较 和 散列 原子
T Table_new(int hint, int cmp(const void *x, const void *y), unsigned hash(const void *key))
{
    T table;
    int i;
    // table 用 素数 来 作为 其散列表的大小是 因为 它 无权 决定 关键字的散列值 的 计算方式
    // primes 中的值 都是 最 靠近 2^n 的 素数 ，使得 散列表的大小范围很广
    static int primes[] = {509, 509, 1021, 2053, 4093, 8191, 16381, 32771, 65521, INT_MAX};

    assert(hint >= 0);
    // for 循环 中 将 i 设置 为 primes 中 的 第一个 等于 或 大于 hint 的 元素 的 下标
    for (i = 1; primes[i] < hint; i++)
    {
    };
    // 而 primes[i-1] 给 出了 buckets 中 元素 个数
    table = ALLOC(sizeof(*table) + primes[i - 1] * sizeof(table->buckets[0]));

    table->size = primes[i - 1];
    table->cmp = cmp ? cmp : cmpatom;
    table->hash = hash ? hash : hashatom;
    table->buckets = (struct binding **)(table + 1);
    for (i = 0; i < table->size; i++)
    {
        // 填充 buckets
        table->buckets[i] = NULL;
    };
    table->length = 0;
    table->timestamp = 0;

    return table;
}
// cpmatom 并 不需要 测试 x和 y 的 相对 次序
static int cmpatom(const void *x, const void *y)
{
    return x != y;
}
// 一个 原子 就是 一个 地址 并且 这个 地址 本身 就 可以 作为 散列值，
// 它总是 循环 右移 两位，因为 每个 原子很有 可能 都以某个单词的词头边界开始，
// 因此 最后 两位很有可能 为 0

static unsigned hashatom(const void *key)
{
    return (unsigned long)key >> 2;
}

void *Table_get(T table, const void *key)
{
    int i;
    struct binding *p;
    assert(table);
    assert(key);
    //1.hash_result=  (*table->hash)(key) // 先散列它的关键字，
    //2.hash_result %(table->size)          // 将 它 对 buckets 的 元素 个数 取 余
    i = (*table->hash)(key) % table->size;
    for (p = table->buckets[i]; p; p = p->link)
    {
        //  在 查找 列表 中 查找 与 key 相等 的 关键字
        if ((*table->cmp)(key, p->key) == 0)
        {
            break;
        }
    }

    return p ? p->value : NULL;
}

void *Table_put(T table, const void *key, void *value)
{
    int i;
    struct binding *p;
    void *prev;

    assert(table);
    assert(key);
    i = (*table->hash)(key) % table->size;
    for (p = table->buckets[i]; p; p = p->link)
    {
        //  在 查找 列表 中 查找 与 key 相等 的 关键字
        if ((*table->cmp)(key, p->key) == 0)
        {
            break;
        }
    }

    if (p == NULL)
    {
        NEW(p);
        p->key = key;
        p->link = table->buckets[i];
        table->buckets[i] = p;
        table->length++;
        prev = NULL;
    }
    else
    {
        prev = p->value;
    }
    p->value = value;
    table->timestamp++;
    return prev;
}

int Table_length(T table)
{
    assert(table);
    return table->length;
}

void Table_map(T table, void apply(const void *key, void **value, void *cl), void *cl)
{

    int i;
    unsigned stamp;
    struct binding *p;

    assert(table);
    assert(apply);
    stamp = table->timestamp;

    for (i = 0; i < table->size; i++)
    {
        for (p = table->buckets[i]; p; p = p->link)
        {
            apply(p->key, &p->value, cl);
            assert(table->timestamp == stamp);
        }
    }
}

void *Table_remove(T table, const void *key)
{
    int i;
    struct binding **pp;
    assert(table);
    assert(key);
    table->timestamp++;
    i = (*table->hash)(key) % table->size;
    for (pp = table->buckets[i]; *pp; pp = &(*pp)->link)
    {
        //  在 查找 列表 中 查找 与 key 相等 的 关键字
        if ((*table->cmp)(key, (*pp)->key) == 0)
        {
            struct binding *p = *pp;
            void *value = p->value;
            *pp = p->link;
            FREE(p);
            table->length--;
            return value;
        }
    }
    return NULL;
}

void **Table_toArray(T table,void **end){
    int i,j=0;
    void **array;
    struct binding *p;
    assert(table);
    array =ALLOC((2*table->length+1)*sizeof (*array));

    for(i=0;i<table->size;i++){
        for(p=table->buckets[i];p;p=p->link){
            array[j++]=(void *)p->key;
            array[j++]=p->value;

        }
        array[j]=end;
        return array;
    }
}

void Table_free(T *table){
    assert(table&&*table);
    if ((*table)->length>0)
    {
       int i;
       struct binding *p,*q;
       for(i=0;i<(*table)->size;i++){
           for(p=(*table)->buckets[i];p;p=q){
               q=p->link;
               FREE(p);
           }
       }
    }
    FREE(*table);
}