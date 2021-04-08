
#include <stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<ctype.h>
int linenum;



int main(int argc, char *argv[]){
    int i;
    for(i=1;i<argc;i++){
        FILE *fp = fopen(argv[i],"r");
        if (fp==NULL){
            fprintf(stderr,"%s: can't open '%s' (%s) \n", argv[0],argv[i],strerror(errno));
            return EXIT_FAILURE;
            
        }else{
            doubleword(argv[i],fp);
            fclose(fp);
        }
       
        
    }
    if (argc==1){
        douleword(NULL,stdin);
    }
    return EXIT_SUCCESS;
}
 int getword(FILE *,char *,int );

int getword(FILE *fp, char *buf,int size){
    int c;
    c=getc(fp);
    if (c!=EOF)
    {
        ungetc(c,fp);
            }
            return ;

    
}