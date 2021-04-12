#include <stdio.h>

// 从 fp 打开 的 文件 中 读取 下一个 单词 ，把 它 当作 一个 以 null 结束 的 字符串 存储 在
// buf[0..size-1] 中 ，并 返回 1 . 当 它 达到 文件 末尾 ，而 没 找到 单词 ，返回 0
// 函数 first 和 rest 测试 某个 字符 是否 是 first 和 rest 集合 中 的 成员 
// 一个 单词 是 字符 的 相邻序列，它以字符开始，对该字符first函数返回 一个非 0值，
//外加 由函数 rest 返回 非 0 值 的 字符 组成 。 
// 如果 一个 单词 长于 size-2 个 字符，那么 超过 的 字符 被 截断。
//size 必须 大于1，并且 fp,buf,first 以及 rest 必须 不为空 。
extern int getword(FILE *fp,char *buf,int size,int first(int c),int rest(int c));

