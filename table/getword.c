#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "assert.h"
#include "getword.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include "atom.h"
#include "table.h"
#include "mem.h"
#include "getword.h"
void wf(char *, FILE *);
int first(int c);
int rest(int c);

#include <string.h>
int compare(const void *x, const void *y);

void vfree(const void *, void **, void *);

int getword(FILE *fp, char *buf, int size, int first(int c), int rest(int c))
{
    int i = 0, c;
    assert(fp && buf && size > 1 && first && rest);
    //getc  从指定的流 stream 获取下一个字符
    c = getc(fp);
    for (; c != EOF; c = getc(fp))
    {
        // 字符 c 满足 first 函数
        if (first(c))
        {
            if (i < size - 1)
            {
                buf[i++] = c;
            }
            c = getc(fp);
        }
        break;
    }
    // 字符 c 满足 rest 函数
    for (; c != EOF && rest(c); c = getc(fp))
    {

        if (i < size - 1)
        {
            buf[i++] = c;
        }
    }
    // 当 i <size 时 填充 0
    if (i < size)
    {
        buf[i] = 0;
    }
    else
    {
        buf[size - 1] = 0;
    }
    if (c != EOF)
    {
        // 把字符 c（一个无符号字符）推入到指定的流 stream 中
        ungetc(c, fp);
    }
    return i > 0;
}
// 使用 原子 使得 wf 采用 默认 表格 的 hash 函数 和 比较 函数
// 虽然 wf 的 值 都是 指针 ，但 是 它 任然 需要 把 一个 整数 计数 与 每个 关键字 关联 起来
// 因此 它 分配 一个 空间 给 计数器，并 在 表格 中 存储 指向 该 区域 的 指针
void wf(char *name, FILE *fp)
{
    Table_T table = Table_new(0, NULL, NULL);
    char buf[128];

    while (getword(fp, buf, sizeof buf, first, rest))
    {
        const char *word;
        int i, *count;
        for (i = 0; buf[i] != '\0'; i++)
        {
            buf[i] = tolower(buf[i]);
        }
        // 创建 key
        word = Atom_string(buf);
        count = Table_string(buf);
        count = Table_get(table, word);
        if (count)
        {
            (*count)++;
        }
        else
        {
            NEW(count);
            *count = 1;
            Table_put(table, word, count);
        }
    }
    if (name)
    {
        printf("%s:\n", name);
    }

    int i;
    void **array = Table_toArray(table, NULL);
    //  数组 ，
    // 元素 的 个数
    // ，每个 元素 所占的字节数以及 
    // 比较 两个 元素 的 函数 
    // 为了 把 N 个 关键字 -值 对 当作 一个 单一 的 元素 来 处理 ，wf 告诉 qsort 有 N个 元素，
    // 且 每个 元素 的 空间 有 两个 指针 占用 
    qsort(array, Table_length(table), 2 * sizeof(*array), compare);

    for (i = 0; array[i]; i += 2)
    {
        printf("%d\t%s\n", *(int *)array[i + 1], (char *)array[i]);
    }
    FREE(array);

    Table_map(table, vfree, NULL);
    Table_free(&table);
}
// 关键字 不被 释放 ，因为 它们 是 原子 ，因此 关键字 一定 不能 被 释放 
void vfree(const void *key, void **count, void *cl)
{
    FREE(*count);
}
int compare(const void *x, const void *y)
{
    // 把 str1 所指向的字符串和 str2 所指向的字符串进行比较。
    return strcmp(*(char **)x, *(char **)y);
}

int first(int c)
{
    return isalpha(c);
}

int rest(int c)
{
    return isalpha(c) || c == '_';
}

int main(int argc, char *argv[])
{
    int i;
    for (i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            fprintf(stderr, "%s:can't open '%s'(%s)\n", argv[0], argv[i], strerror(errno));
            return EXIT_FAILURE;
        }
        else
        {
            wf(argv[i], fp);
            fclose(fp);
        }
    }
    if (argc == 1)
    {
        // 如果 没有 任何 参数 ，那么 main 以 空 文件 名 和 标准 输入 文件 指针 作为 参数 调用 wf,
        // 空 文件 名 告诉 wf 不用 打印 出 文件 的 名字
        wf(NULL, stdin);
    }
    return EXIT_SUCCESS;
}