#include "atom.h"
#include <string.h>
#include "assert.h"
#include <limits.h>
#include <stdlib.h>
#include "mem.h"
#include <stdio.h>
// 数组中 元素 个数 等于 数组 的 大小 除以 每个 元素的 大小
#define NELEMS(x) ((sizeof(x)) / (sizeof((x)[0])))
// 散列表 显然 是 一个 针对 原子表 的 数据 结构 ，
//  散列表 是 一个 入口 表 的 指针 数组
// ，其中 的 每 一个 元素 都 存有 一个 原子
//buckets[i] 中 的 链表 存储 着 散列 值 为 i 的 原子 。
//

// buckets 相当于 map
static struct atom
{
    struct atom *link;
    int len;
    char *str;

} * buckets[2048];
// 用于 散列 操作
static unsigned long scatter[] = {207817053, 143302914, 1027100827};
// 调用 Atom_new 初始化 原子 类
const char *Atom_string(const char *str)
{
    assert(str);
    return Atom_new(str, strlen(str));
}
// 将 参数 转换 成 一个 字符 串 ， 再 调用 Atom_new
const char *Atom_int(long n)
{
    //
    char str[43];
    // str 存储 字节 大小 +str  地址
    char *s = str + sizeof str;
    // 使用 无符号 算术 避免 使用 有 符号 运算引起的不确定性
    unsigned long m;

    if (n == LONG_MIN)

    {
        m = LONG_MAX + 1UL; // 1UL 为 无符号 长 整型  处理 二进制 补码数的不对称范围
                            // 和 取余运算 的 不确定 性
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
        // 数组 指针 , s 在 str 中 是 向 后 移动 的
        *--s = m % 10 + '0';

    } while ((m /= 10) > 0);
    // 添加  负号 指针
    if (n < 0)
    {
        // 如果 n 为 负数 ，则 存入 -
        *--s = '-';
    }
    // 字符串 有 &str[43]-s 个 字符
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

    // 散列 操作
    // scatter 是 一个 256 入口 的 数组，将 字节 映射 为 随机数 ，这些 随机数 通过 调用 标准库 中 的 函数 rand 生成
    // (unsigned char)str[i] 能够 避免 无格式 字符 的 不确定 性，没有 这种 转换 在 使用 有 符号 字符 的 机器上 ，值 超过 127 的 str[i] 将 变为 负数
    for (h = 0, i = 0; i < len; i++)
    {
        h = (h << 1) + scatter[(unsigned char)str[i]];
    }
    // 拿到 buckets 中 元素 个数
    // & 位运算 都为 1 时 结果 才 为 1
    h &= NELEMS(buckets) - 1;
    // 使用 散列表 实现 原子 类
    // 不用 循环 buckets 数组， 根据 str 和 散列 算法  就 直接 定位 到了 buckets 数组 下标
    // 接着 处理 hash 冲突 就 行了
    for (p = buckets[h]; p; p = p->link)
    {
        // 如果 new 的 string  已存在 则 返回
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
    // 分配 atom 和 附加 空间 来 存储 序列
    p = malloc(sizeof(*p) + len + 1);
    p->len = len;
    // 将 p+1 强转成 指向 char 的 指针
    p->str = (char *)(p + 1);
    if (len > 0)
    {
        // 将 str 复制 到 p->str
        memcpy(p->str, str, len);
    }
    // 设置 终止 标志
    p->str[len] = '\0';
    // 添加 新 的 入口 到 buckets[h] 中 链表 的表头
    p->link = buckets[h];
    buckets[h] = p;
    return p->str;
}

int Atom_length(const char *str)
{
    struct atom *p;
    int i;

    assert(str);
    // 由于 不知道 参数 长度 ，所以 不能 对 参数 进行 散列 操作 ，
    // 所以 只能 双重循环 查找 str
    for (i = 0; i < NELEMS(buckets); i++)
    {
        for (p = buckets[i]; p; p = p->link)
        {
            if (p->str == str)
            {
                return p->len;
            }
        }
    }
    assert(0);
    return 0;
}
int main()
{
    const char *result = Atom_new("hello", 5);
    printf("result's %s", result);
    return 0;
}