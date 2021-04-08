#include<stdio.h>

#define BUFSIZE 100
char buf [BUFSIZE];
int bufp=0;
int getch(void){
    return (bufp>0)?buf[--bufp]:getchar();
}
void ungetch(int c){
    if(bufp>=BUFSIZE){
        printf("ungetch: too many characters\n");

    }else{
        buf[bufp++]=c;
        
    }
}


int power(int m,int n);
int main()
{
 int i;
 for ( i = 0; i < 10; i++){
    printf("%d %d %d \n",i,power(2,i),power(-3,i));

 }
 return 0;

int power(int base,int n){
    int i,p;
    p=1;
    for ( i = 0; i < =n; i++)
    {
        p=p*base;

    }
    return p;
    
}
 {
     /* code */
 }
 
}
