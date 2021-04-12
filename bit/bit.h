#ifndef BIT_INCLUDED
#define BIT_INCLUDED
#define T Bit_T
typedef struct  T *T;

extern T Bit_new(int length);
extern int Bit_length(T set);
extern int Bit_count(T set);
#undef T
#endif 
