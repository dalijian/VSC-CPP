#include <stdio.h>

//读
int main(int argc,char *argv[])
{
    FILE *p = fopen("C:\\Users\\lijian\\Desktop\\context2.xml", "r");
    if (p == NULL)
    {
        printf("文件打开失败\n");
    }
    else
    {
        char s[1024] = { 0 };
        fgets(s, sizeof(s), p);
        printf("%s",s);
        fclose(p);
    }
    return 0;
}

