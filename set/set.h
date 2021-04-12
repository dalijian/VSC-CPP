#ifndef SET_INCLUDED
#define SET_INCLUDED

#define T Set_T
typedef struct T *T;

extern T Set_new (int hint,int cmp(const void *x,const void *y),unsigned hash(const void *x));

extern void Set_free(T *set);


extern int Set_length(T set);
extern int Set_member(T set,const void *member);
extern void Set_put(T set,const void *member);
extern void *Set_remove(T set,const void *memeber);
// 把 成员 和 由 客户 调用 程序定义 的 指针 cl 传递 给 apply, 但是 它 并 不 检查 cl
// 与 Table_map 不同，apply 不能 改变 存储 在 集合中 的成员 ，
// 把 一个 空 apply 函数 或者 空集 传递 给 Set_map和 apply,通过 调用 
//Set_put 或 Set_remove 来改变 set 都将 产生可 检查 的 运行期 错误 
extern void Set_map(T set,void apply(const void *member,void *cl),void *cl);

extern void **Set_toArray(T set,void *end);



extern T Set_union(T s,T t);
extern T Set_inter(T s,T t);
extern T Set_minus(T s,T t);
extern T Set_diff(T s,T t);


#undef T 
#endif

