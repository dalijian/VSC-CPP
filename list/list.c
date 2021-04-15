#include <stdarg.h>
#include <stddef.h>
#include "assert.h"
#include "mem.h"
#include "list.h"

#define T List_T
// 分配 一个 节点 ，初始化 ，然后 返回 一个 指向 它的 指针
T List_push(T list, void *x)
{

    T p;
    NEW(p);
    p->first = x;
    p->rest = list;
    return p;
}
// 为 每个 非空 的 指针 参数 添加 一个 新的 节点 到 正在 变化 的 链表 中
// 为了 做到 这些，它使用了 一个 指针 ，它 所 指向 的 指针 指向 新的 节点 且 应该 被 赋过值

T List_list(void *x, ...)
{
    // 接收 可变 参数
    va_list ap;
    T list, *p = &list;

    va_start(ap, x);
    for (; x; x = va_arg(ap, void *))
    {
        NEW(*p);
        (*p)->first = x;
        // 将 p 赋值 为 p->rest
        p = &(*p)->rest;
    }
    *p = NULL;
    // 释放 可变参数 
    va_end(ap);
    return list;
}
T List_append(T list, T tail)
{
    // &返回变量的地址。  拿到 list 地址 
    T *p = &list;
// 拿到 list 的 最后 一个 节点 ，将 节点 的 rest 指向 tail 
    while (*p)
    {
        p = &(*p)->rest;
    }

    *p = tail;
    return list;
}
// 复制 list 
T List_copy(T list)
{
    T head, *p = &head;
    for (; list; list = list->rest)
    {
        NEW(*p);
        (*p)->first = list->first;
        p = &(*p)->rest;
    }
    *p = NULL;
    return head;
}

T List_pop(T list, void **x)
{
    if (list)
    {
        T head = list->rest;
        if (x)
        {
            //  将 list 的 第一个 元素  指向一个变量 *x 
            *x = list->first;
        }
        FREE(list);
        return head;
    }
    else
    {
        return list;
    }
}
// 反转 链表 
T List_reverse(T list)
{
    T head = NULL, next;
    for (; list; list = next)
    {
        next = list->rest;
        list->rest = head;
        head = list;
    }
    return head;
}

int List_length(T list)
{
    int n;
    for (n = 0; list; list = list->rest)
    {
        n++;
    }
    return n;
}
void List_free(T *list)
{
    T next;
    assert(list);
    for (; *list; *list = next)
    {
        next = (*list)->rest;
        FREE(*list);
    }
}
// List_map 只需要 遍历 list 链表 ，使用 指向 每个 节点 的 first 字段 的 指针 以及 
// 调用 程序 专用 的 指针 cl 来 调用 闭包 函数   
void List_map(T list, void apply(void **x, void *cl), void *cl)
{
    assert(apply);
    for (; list; list = list->rest)
    {
        apply(&list->first, cl);
    }
}
// 分配 一个 有 N+1 个 元素 的 数组 来 保存 N个 元素 链表 的 指针
//  ，并 把 这些 指针 复制 到 数组 中 
void **List_toArray(T list, void *end)
{
    int i, n = List_length(list);
    void **array = ALLOC((n + 1) * sizeof(*array));
    for (i = 0; i < n; i++)
    {
        array[i] = list->first;
        list = list->rest;
    }
    array[i] = end;
    return array;
}

T *search_list(T node,void const *value,int (*compare)(void const *,void const *)){
    while(node!=NULL){
        if(compare(node->first,value)==0){
            break;
        }
        node=node->rest;
    }
    return node;
}