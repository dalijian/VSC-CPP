#include <stdio.h>
#include <string.h>
void testtest(void *a);
int find_char(char **strings, char value);
int find_char2(char **strings, char value);

int main()
{

    
    // char array = {"hello", "world"};
      char *array [] = {"hello", "world"}; //2个元素保存了2个内存地址，这2个地址中就代表了2个字符串的首地址，而不是字符串本身
    // char **s=array; // 因为 数组名 array 代表 数组 元素 内存 单元 的 首地址，即 a=&a[0]=0012FF38,而 0x12FF38 即 a[0]
    // 中保存的又是00422FBB，这个地址，00422FB8 为 字符串“hello" 的首地址 即 *s=00422FB8="hello"
    char **point =array; // 二维数组不支持  ** 访问 
        // while ((point++)!=NULL)
        // {
        //     printf("address:%x",array);
        //     printf("address:%s",*point);
        // }
        

    find_char(array, 'd');
    // find_char2(array,'d');
    return 0;
}
// strings 指向指针数组的指针，value 查找的字符值
// 指针数组以 一个NULL 指针 结束
int find_char(char **strings, char value)
{
    // 当前 正在查找的字符串
    char *string;
    // printf("\n+++%s", *strings);

    /**
     * 1. 把 strings 当前所指向的 指针 复制 到 变量 string 中
     * 2. 增加 strings 的 值，使它指向下一值
     * 3. 测试string 是否 为NULL,当 string 指向 当前 字符串 中 作为 终止 标志 的NULL字节 时，
     * 内层的while循环终止
     */
    while ((string =*strings++) != NULL)
    {
        // string 指向 "hello" 
        printf("++%s\n", string);
        while (*string != '\0')
        {
            // *string =**strings 指向 'h' 
            printf("\n==%c", *string);
            if (*string++ == value)
            {
                return 1;
            }
        }
    }
    return 0;
}

int find_char2(char **strings,char value){
    while (*strings!=NULL)
    {   
    printf("++%s\n",*strings);
        while(**strings!='\0'){
            printf("--%c\n",**strings);
            if(*(*strings)++==value){
                return 1;
            }
        }
        strings++;
    }
    return 0;
}