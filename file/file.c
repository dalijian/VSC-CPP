#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//prototype

void readByLine(FILE *file);

int main()
{
    FILE *input;

    input = fopen("./file_test.txt", "r+");

    if (input == NULL)
    {
        printf("%s", "file is null");
        exit(EXIT_FAILURE);
    }

    readByLine(input);

    // char text[20];
    // fgets(text, 2, input);

    // printf("%s", text);
    // fputs("hello world", input);

    // fflush(input);

    fclose(input);
}
void readByLine(FILE *file)
{
    char text[1024];
    while (fscanf(file, "%[^\n]",text) != EOF)
    {
        printf("%s",text);
    }

}

int read_in()
{

    int value;
    int ch;
    value = 0;
    while ((ch = getchar()) != EOF && isdigit(ch))
    {
        value *= 10;
        value += ch - '0';
    }

    // 把 非 数字字符 退回 到 流 中，这样它就 不会 丢失

    ungetc(ch, stdin);
    return value;
}


struct StudentInfo {
    int age;
};

/**
 * 从 一个 文件 读取 一个 特定 的 记录 ，参数 分别 是 
 * 进行 读取 的 流 ，需要 读取 的 记录 数 和 ** 指向 放置 数据 的 缓冲 区 的 指针 
 */

int read_random_record(FILE *f,size_t rec_number,struct StudentInfo *buffer){
    fseek(f,(long)rec_number*sizeof(struct  StudentInfo),SEEK_SET);
    return fread(buffer,sizeof(struct StudentInfo),1,f);
}
