#ifndef LIST_INCLUDED
#define LIST_INCLUDED

// List_T 是 一个 指向 List_T 结构 的 指针 。
#define T List_T
// 使用 *T 代替 struct T 
typedef struct T *T;

struct T
{
   T rest;      // next_node
   void *first; // 存放 value
};
// 在 链表 中 添加 一个 链表  将 tail 赋值 给 list 链表的 最后 一个 节点 的 rest 字段 , 如果 list 为 空 ，则 返回 tail
extern T List_append(T list, T tail);
extern T List_copy(T list);
// 创建 并 返回 一个 链表
extern T List_list(void *x, ...);
// 将 链表 第一个 节点 的 first 字段 赋值 给 *x,如果 x 不为 空 ，
// 那么 删除 并 释放 第一个 节点
// 并 返回 剩下 的 链表
// 如果 给定 的 是 一个 空 链表 ，那么 List_pop仅仅 返回 空 链表 ，对 *x不做任何改变
extern T List_pop(T list, void **x);
extern T List_push(T list, void *x);
// 反转 链表  参数 中 节点 的 次序 并 返回 结果 链表
extern T List_reverse(T list);
extern int List_length(T list);
// 如果 *list 不为 空，那么 List_free 释放 *list 中 所有 的 节点 ，并 把 *list 设 为 空
// 如果 *list 为空 ，那么 List_free 将 不做 任何 操作
extern void List_free(T *list);
// 对list z中 的 每个 节点 调用 apply所指向 的函数
//*apply 连带 一个 指向 节点 的 first 字段 的 指针 和 c1 指针 一起 被 调用
// void apply(void **x,void *c1) 相当于 回调 ：(它们 一起 规定 了 一个 操作 ，以及
// 该操作 的 一些 上下 文 专用 的 数据 )
extern void List_map(T list, void apply(void **x, void *cl), void *cl);
// 返回 一个 指向 该 函数 组 第一个 元素 的 指针
extern void **List_toArray(T list, void *end);
// 在 一个 单链表 中 查找 一个 指定值 的 函数，
// 参数 由 一个 指向链表 第一个 节点 的 指针 
// 一个 指向 我们 需要 查找 的 值 的 指针 和 一个 函数 指针 ，它 所 指向 的 函数 用于 比较 存储 于 链表 中 的 类型 的 值 
// 第二个参数 必须 是 指向值的指针，而不是值本身，然后将这个值的指针传递给比较函数，这个修改 使 字符串和数组对象也可以被使用，
// 因为 字符串和数组无法作为参数传递给函数，但指向它们的指针却可以

T * search_list(T node,void const *value,int(* compare)(void const *,void const *));



#undef T
#endif