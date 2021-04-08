#ifndef EXCEPT_INCLUDED
#define EXCEPT_INCLUDED
#include <setjmp.h>

#define T Except_T
typedef struct T
{
    char *reason;
} T;

#define RAISE(e) Except_raise(&(e), __FILE__, __LINE__)

void Except_raise(const T *e, const char *file, int line);
#define RERAISE Except_raise(Except_frame.exception, Except_frame.file, Except_frame.line);
#define RETURN swith(0) default : return

#undef T
#endif