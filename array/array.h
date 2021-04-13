#ifndef ARRAY_INCLUDED
#define ARRAY_INCLUDED
// 把 T 替换成 Array_T
#define T Array_T
//  使用 typedef  来 创建 新的 类型名， #define 无法 正确 地 处理 指针 类型 
typedef struct T *T;

extern T Array_new(int length, int size);
extern void Array_free(T *array);

extern int Array_length(T array);
extern int Array_size(T array);

extern void *Array_get(T array, int i);
// 不能 返回 第i个 元素 先前的 值，因为 该 元素 没有 所必需 的 指针 ，并且 它们长度 可以 为 任意 字节

extern void *Array_put(T array, int i, void *elem);

extern void Array_resize(T array, int length);
extern T Array_copy(T array, int length);

#undef T
#endif
