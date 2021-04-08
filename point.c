#include <stdio.h>

void testtest(void *a);
int main()
{
    int var1;
    char var2[10];
    int dd = 65;
    printf("var1 变量的地址： %x\n", &var1);
    printf("var2 变量的地址： %x\n", &var2);

    testtest(&dd);
    return 0;
}

void testtest(void *a)
{
    printf("dd  变量的值： %d\n", a);

    printf(a);
}