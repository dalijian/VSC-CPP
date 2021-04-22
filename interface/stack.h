// 如果 STACK_INCLUDED 没有 定义 则 定义 宏 
#ifndef STACK_INCLUDED
#define STACK_INCLUDED
// 定义了 Stack_T 类型， 该 类型 是 一个 指向 有 相同 名字 标签 的 结构 
// Stack_T  是 一个 隐式 的 指针 类型 ，客户端不能查看由该类型指针指向的结构的内部内容，只有实现具有这个特权 
typedef struct Stack_T *Stack_T;

// 用于为各种数据类型定义别名，为 Stack_T 定义 别名 T 
#define T Stack_T
// 您可以使用它来为类型取一个新的名字 
typedef struct T *T;
// 您可以使用 extern 关键字在任何地方声明一个变量
extern T Stack_new (void);
extern int Stack_empty(T stk);
extern void Stack_push(T stk,void *x);
extern void *Stack_pop(T stk);
extern void Stack_free(T *stk);

// 取消 定义 的 宏 T 
// 客户端 调用 程序 必须 使用 Stack_T, 因为 #undef 指令 取消了 这个 简写 
#undef T
#endif