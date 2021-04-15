#include<stdarg.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>
#include<float.h>
#include<ctype.h>
#include<math.h>
#include"assert.h"
#include"except.h"
#include"fmt.h"
#include"mem.h"
#define T Fmt_T 

// type

struct buf{
    char *buf;
    char *bp;
    int size;
};
//macros

// conversion functions
void Fmt_fmt(int put(int c,void *),void *cl,const char *fmt,...){
    va_list ap;
    va_start(ap,fmt);
    Fmt_vfmt(put,cl,fmt,ap);
    va_end(ap);
}

void Fmt_print(const char *fmt,...){
    va_list ap;
    va_start(ap,fmt);
    Fmt_vfmt(outc,stdout,fmt,ap);
    va_end(ap);
}

void Fmt_fprint(FILE *stream,const char *fmt,...){
    va_list ap;
    va_start(ap,fmt);
    Fmt_vfmt(outc,stream,fmt,ap);
    va_end(ap);

}

int Fmt_sfmt(char *buf,int size,const char *fmt,...){
    va_list ap;
    int len;

    va_start(ap,fmt);
    len=Fmt_vsfmt(buf,size,fmt,ap);
    va_end(ap);
    return len;
}

int Fmt_vsfmt(char *buf,int size,const char *fmt,va_list ap){
    struct buf cl;
    assert(buf);
    assert(size>0);
    assert(fmt);
    cl.buf=cl.bp=buf;
    cl.size=size;
    Fmt_vfmt(insert,&cl,fmt,ap);
    insert(0,&cl);
    return cl.bp-cl.buf-1;
}

char *Fmt_string(const char *fmt,...){
    char *str;
    va_list ap;

    assert(fmt);
    va_start(ap,fmt);
    str= Fmt_vstring(fmt,ap);

    va_end(ap);
    return str;
}

char *Fmt_vstring(const char *fmt,va_list ap){
    struct buf cl;

    assert(fmt);
    cl.size=256;
    cl.buf=cl.bp=ALLOC(cl.size);
    Fmt_vfmt(append,&cl,fmt,ap);
    append(0,&cl);
    return RESIZE(cl.buf,cl.bp-cl.buf);
}
// data
const Except_T Fmt_Overflow={"Formatting Overflow"};
//static functions
static int outc(int c, void *cl){
    FILE *f=cl;
    return putc(c,f);
}

static int insert(int c,void *cl){
    struct buf *p=cl;

    if(p->bp>=p->buf+p->size){
        RAISE(Fmt_Overflow);
    }
    *p->bp++=c;
    return c;
}
static int append (int c ,void *cl){
    struct buf*p=cl;
    if (p->bp>=p->buf+p->size)
    {
        RESIZE(p->buf,2*p->size);
        p->bp=p->buf+p->size;
        p->size*=2;
    }
    *p->bp++=c;
    return c;
}

void Fmt_vfmt(int put(int c,void *cl),void *cl,const char *fmt,va_list ap){
    assert(put);
    assert(fmt);
    while(*fmt){
        if(*fmt!='%'||*++fmt=='%'){
            put((unsigned char )*fmt++,cl);
        }
        else{
            unsigned char c,flags[256];
            int width=INT_MIN,precision=INT_MIN;
            memset(flags,'\0',sizeof flags);
        }
    }
}
//functions

