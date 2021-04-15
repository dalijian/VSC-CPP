#ifndef FMT_INCLUDED
#define FMT_INCLUDED
#include <stdarg.h>
#include <stdio.h>
#include "except.h"

//Macro
#define T Fmt_T

typedef void (*T)(int code, va_list *app, int put(int c, void *cl), void *cl, unsigned char flags[256], int width, int precision);

#define pad(n,c)do{ int nn=(n); while(nn-->0) put((c),cl);while(0)}
//prototype

//data
extern char *Fmt_flags;

extern const Except_T Fmt_Overflow;

//function

extern void Fmt_fmt(int put(int c, void *cl), void *cl, const char *fmt, ...);

extern void Fmt_vfmt(int put(int c, void *cl), void *cl, const char *fmt, va_list ap);

extern void Fmt_print(const char *fmt, ...);

extern void Fmt_fprint(FILE *stream, const char *fmt, ...);

extern int Fmt_sfmt(char *buf, int size, const char *fmt, ...);

extern int Fmt_vsfmt(char *buf, int size, const char *fmt, va_list ap);

extern char *Fmt_string(const char *fmt, ...);

extern char *Fmt_vstring(const char *fmt, va_list ap);

extern T Fmt_register(int code, T cvt);

extern void Fmt_putd(const char *str, int len, int put(int c, void *cl), void *cl, unsigned char flags[256], int width, int precision);

extern void Fmt_puts(const char *str, int len, int put(int c, void *cl), void *cl, unsigned char flags[256], int width, int precision);

//static method
static void cvt_s(int code, va_list *app, int put(int c, void *cl), void *cl, unsigned char flags[], int width, int precision)
{
    char *str = va_arg(*app, char *);
    assert(str);
    Fmt_puts(str, strlen(str), put, cl, flags, width, precision);
}

void Fmt_puts(const char *str, int len, int put(int c, void *cl), void *cl, unsigned char flags[], int width, int precision)
{

    assert(str);
    assert(len >= 0);
    assert(flags);
    if (width==INT_MIN)
    {
        width=0;
    }
    if (width<0)
    {
        flags['-']=1;
        width=-width;
    }
    if (precision>=0)
    {
        flags['0']=0;
    }
    
    
    if (precision >= 0 && precision < len)
    {
        len = precision;
    }
    if (!flags['-'])
    {
        pad(width - len, ' ');
    }

    {
        int i;
        for(i=0;i<len;i++){
            put((unsigned char )*str++,cl);
        }
    }
    if (flags['-'])
    {
        pad(width - len, ' ');
    }
}

#undef T
#endif