#ifndef ATOM_INCLUDED
#define ATOM_INCLUDED
// 若 找到 原子 返回 原子 长度 
extern int Atom_length(const char *str);
// 接收 一个 指向 字节序列 的 指针 以及 序列 的 字节 数 作为 输入  
// 在 原子表 中 增加一个 该 序列 的拷贝 
extern const char *Atom_new(const char *str,int len);
extern const char *Atom_string(const char *str);
// 类似 static long 
extern const char *Atom_int(long n);

#endif