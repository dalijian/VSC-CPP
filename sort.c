#include <stdio.h>
#include <string.h>
// 进行排序的最大文本行数
#define MAXLINES 5000
// 指向文本行 的 指针 数组
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
// 对 输入 的 文本 行 进行 排序
main()
{
    // 读取的输入 行 数目
    int nlines;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return;
    }
    else
    {
        printf("error:input too big to sort \n");
        return 1;
    }
}
// 每个 输入 文本行 的 最大 长度
#define MAXLEN 1000;
int getline(char *, int);
char *alloc(int);
//  readlines 函数 ， 读取 输入行
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0)
    {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
        {
            return -1;
        }
        else
        {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}
// writelines 函数：写输出 行 
void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
    {
        printf("%s\n", lineptr[i]);
    }
}

// qsort 函数：按递增顺序对 v[left]...v[right] 进行 排序 

void qsort(char *v[],int left,int right){
    int i,last;
    void swap(char *v[],int i,int j);
    // 如果 数组 元素 的个数 小于 2 ， 则 返回 
    if (left>= right){
        return ;
    }
    swap(v,left,(left+right)/2);
    last = left;
    for ( i = left+1; i < right; i++)
    {
        if (strcmp(v[i],v[left])<0){
            swap(v,++last,i);
        }
    }
    swap(v,left,last);
    qsort(v,left,last-1);
}

void swap(char *v[],int i,int j){
    char *temp;
    temp=v[i];
    v[i]=v[j];
    v[j]=temp;
}