#include <stdio.h>
#include <stdlib.h>
 
#define FILE_PATH  "‪"  /*文件路径*/
 
int main(void)
{
	char buff[512];
	char string1[50];
	char string2[50];
 
	FILE *pFile = fopen(FILE_PATH, "w+");
	if (pFile == NULL) {
        system("dir");
        printf("file path is null");
		return -1;
	}
 
	while (!feof(pFile))  {                /*读取文档，直到文件结束*/
		fgets(buff, sizeof(buff), pFile);
		printf(" %s \n", buff);
	}
	fclose(pFile);
 
	return EXIT_SUCCESS;
}