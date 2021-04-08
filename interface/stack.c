#include "stack.h"
#include "mem.h"
#include "assert.h"
#include <stddef.h>

#define T Stack_T
struct T
{
    // 指针的 计数
    int count;
    // 栈内指针的 链表
    struct elem
    {
        void *x;
        struct elem *link;
    } * head;
};
T Stack_new(void)
{
    T stk;
    NEW(stk);
    // 为了使用指向该结构的指针访问结构的成员，您必须使用 -> 运算符
    stk->count = 0;
    stk->head = NULL;
    return stk;
}
int Stack_empty(T stk)
{
    // assert 实现了 可 检查 的 运行 期 错误 ， 禁止 空指针 传给 Stack 中 的 任何 函数
    // assert(e) 是 一个 断言，它确保 表达式 e 不为 0.
    assert(stk);
    return stk->count == 0;
}
void Stack_push(T stk, void *x)
{
    struct elem *t;
    assert(stk);
    NEW(t);
    t->x = x;
    t->link = stk->head;
    stk->head = t;
    stk->count++;
}

void *Stack_pop(T stk)
{
    void *x;
    struct elem *t;
    assert(stk);
    assert(stk->count > 0);
    t = stk->head;
    stk->head = t->link;
    stk->count--;
    x = t->x;
    FREE(t);
    return x;
}
void Stack_free(T *stk)
{
    struct elem *t, *u;
    assert(stk && *stk);

    for (t = (*stk)->head; t; t = u)
    {
        u = t->link;
        FREE(t);
    }
    FREE(*stk);
}
