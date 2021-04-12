#ifndef TABLE_INCLUDED
#define TABLE_INCLUDED
#define T Table_T

// 使用 隐式 指针 类型 来 表示 一个 关联 表格 
typedef struct  T *T;

// hint 是对 新表 中 期望存储 的 记录 项 数目 的估计 ， 不管 hint 的 值 是 多少 ，
// 所有 的 表格 都可以 存储 任意 数目 的 记录 项 ，但是 如果 hint 的 值 很 精准 的 话,
// 有 可能 会 提高 性能 ，如果 hint 的 值 为 负数 ，也会 产生 可检查 的 运行 期 错误 。
// cmp(x,y) 必须 返回 一个 小于 0，等于 0，或者 大于 0 的 整数，
// 标准的库函数 strcmp 就是 一个 以 字符串 为 关键字 的比较函数 的例子
// hash 函数 必须 返回 一个 key 的 散列值 ，如果 cmp (x,y) 返回 0， 那么 hash(x) 必须 等于 hash(y)
extern T Table_new (int hint,int cmp(const void *x,const void *y),unsigned hash(const void *key));

extern void Table_free(T *table);

extern int Table_length(T table);

extern void *Table_put(T table,const void *key,void *value);

extern void *Table_get(T table,const void *key);

extern void *Table_remove(T table,const void *key);

// 以 不确定 的 次序 对 table 中 的 每个 关键字-值对 调用 apply 指向 的 函数 ，
// apply 和 cl 指定了 一个 闭包：客户调用 程序 可以 传递 一个 应用 程序 专用 的 指针 cl 给 Table_map,并且这个 指针 在 每次 调用 时 又 传递 给 apply.
// 对 table 中 的 每个 关键字-值对，apply 时 同 它的 关键字，指向他的值的指针以及 cl 一起调用。
// 因为 apply 是 同指向 它的 值的 指针 一起 调用 的，因此 它 可以 改变 它 的 值 。
// Table_map 同时 也 可以 在 释放表格 之前 用来 释放 关键字或值 。
extern void Table_map(T table,void apply(const void *key,void **value,void *cl),void *cl);
// Table_toArray 构建 一个 有 2N+1 个 元素 的 数组 并 返回 一个 指向 其 第一个 元素 的 指针 
// 关键字 和 值 交替 出现，关键字 出现 在 奇数号 元素，而 它们 关联 的 值 在 接下来 的 偶数 号 元素 中 
// 最后 一个 偶数 号 元素 ，即 索引 号 2N 赋值 end,通常 是 个 空指针 
// 数组 中 关键字- 值 对 的 次序 是 不确定 的 


extern void **Table_toArray(T table,void *end);


#undef T
#endif
