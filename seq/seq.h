#ifndef SEQ_INCLUDED
#define SEQ_INCLUDED

#define T Seq_T

typedef struct  T *T;

// 创建 并 返回 一个 空 序列 
// hint 是 对 这个 新 序列 所 容纳 的最大 值 的 估计 
extern T Seq_new(int hint);

// 创建 并 返回 一个 序列 ，支持 初始化 
extern T Seq_seq(void *x,...);

extern int Seq_length(T seq);

extern void *Seq_get(T seq,int i);

extern void *Seq_put(T seq,int i,void *x);

//扩展 序列 
// 将 x 加 到 低端 并 返回 x 值 
extern void *Seq_addlo(T seq,void *x);
// 将 x 加 到 seq 的 高端 并 返回 x 值 
extern void *Seq_addhi(T seq,void *x);


// 缩减 seq

extern void *Seq_remlo(T seq);
extern void *Seq_remhi(T seq);

#endif
