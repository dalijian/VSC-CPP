#include "atom.h"
#include <string.h>
#include "assert.h"
#include <limits.h>
#include "mem.h"
// 数组中 元素 个数 等于 数组 的 大小 除以 每个 元素的 大小
#define NELEMS(x) ((sizeof(x)) / (sizeof((x)[0])))
// 散列表 显然 是 一个 针对 原子表 的 数据 结构 ，
//  散列表 是 一个 入口 表 的 指针 数组
// ，其中 的 每 一个 元素 都 存有 一个 原子
//buckets[i] 中 的 链表 存储 着 散列 值 为 i 的 原子 。

static struct atom
{
    struct atom *link;
    int len;
    char *str;

} * buckets[2048];

static unsigned long scatter[]={ };
// 调用 Atom_new 初始化 原子 类
const char *Atom_string(const char *str)
{
    assert(str);
    return Atom_new(str, strlen(str));
}
// 将 参数 转换 成 一个 字符 串
const char *Atom_int(long n)
{
    char str[43];
    char *s = str + sizeof str;
    // 使用 无符号 算术 避免 使用 有 符号 运算引起的不确定性
    unsigned long m;

    if (n == LONG_MIN)

    {
        m = LONG_MAX + 1UL;
    }
    else if (n < 0)
    {
        m = -n;
    }
    else
    {
        m = n;
    }
    do
    {
        *--s = m % 10 + '0';

    } while ((m /= 10) > 0);
    // 添加  负号 指针
    if (n < 0)
    {
        *--s = '-';
    }

    return Atom_new(s, (str + sizeof str) - s);
}
// 计算 由 str[0..len-1] 给定序列的散列值，并用buckets的元素个数对其取模，
//搜索由 buckets 中该散列值元素所指向的链表。如果发现str[0..len-1] 已存在于表中，
//它将只是简单地返回该原子

const char *Atom_new(const char *str, int len)
{
    unsigned long h;
    int i;
    struct atom *p;
    assert(str);
    assert(len >= 0);
    for(h=0,i=0;i<len;i++){
        h=(h<<1)+scatter[(unsigned char)str[i]];
    }
    // 拿到 buckets 中 元素 个数
    h &= NELEMS(buckets) - 1;
    // 使用 散列表 实现 原子 类
    for (p = buckets[h]; p; p = p->link)
    {
        if (len == p->len)
        {
            for (i = 0; i < len && p->str[i] == str[i];)
            {
                i++;
            }
            if (i == len)
            {
                return p->str;
            }
        }
    }
    // alloc 是 Mem 的基本分配函数，模拟标准库中的malloc, 请求参数是字节数
    p = ALLOC(sizeof(*p) + len + i);
    p->len = len;
    p->str = (char *)(p + 1);
    if (len > 0)
    {
        memcmp(p->str, str, len);
    }
    p->str[len] = '\0';
    p->link = buckets[h];
    buckets[h] = p;
    return p->str;
}

int  Atom_length(const char *str){
    struct  atom *p;
    int i;

    assert(str);
    for(i=0;i<NELEMS(buckets);i++){
        for(p=buckets[i];p;p=p->link){
            if(p->str==str){
                return p->len;
            }
        }
    }
    assert(0);
    return 0;
    
}