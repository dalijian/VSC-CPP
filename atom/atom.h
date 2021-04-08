#ifndef ATOM_INCLUDED
#define ATOM_INCLUDED

extern int Atom_length(const char *str);
// 接收 一个 指向 字节序列 的 指针 以及 序列 的 字节 数 作为 输入  
extern const char *Atom_new(const char *str,int len);
extern const char *Atom_string(const char *str);
extern const char *Atom_int(long n);

#endif