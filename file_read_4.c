#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_file_list(const char *path, char **filename);

int main()
{
    char path[100] = "d:\\upload";
    printf("请输入路径（例如d:\\install):");
    scanf("%s", path);
    char filename[100][100];
    char *pfn[100];
    for (int i = 0; i < 100; i++)
    {
        filename[i][0] = 0;
        pfn[i] = filename[i];
    }
    get_file_list(path, pfn);
    for (int i = 0; i < 100; i++)
    {
        if (filename[i][0] == 0)
            break;
        printf("%s\n", filename[i]);
    }
    system("pause");
    return 0;
}

void get_file_list(const char *path, char **filename)
{
    char cmd[150] = "";
    FILE *fptr;
    strcat(cmd, "dir ");
    strcat(cmd, path);
    strcat(cmd, " /s /b > a.log");
    system(cmd);
    fptr = fopen("a.log", "r+");
    if (fptr == NULL)
    {
        printf("path '/s' is not exit/n", path);
        return;
    }
    char temp[100] = "";
    int i = 0;
    while (fgets(temp, 100, fptr) != NULL)
    {
        strcpy(filename[i], strrchr(temp, '\\') + 1);
        filename[i][strlen(filename[i]) - 1] = 0;
        i++;
    }
    fclose(fptr);
}
