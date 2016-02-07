#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
int main()
{
    int f[2];
    if(pipe(f)!=-1)
        if(fork()>0)
        {
            char a[100];
            printf("I am the parent \n");
            printf("Enter a string : ");
            gets(a);
            close(f[0]);
            write(f[1],a,strlen(a)+1);
        }
        else
        {
            close(f[1]);
            char b[100];
            read(f[0],b,100);
            printf("\n\nI am the child \n My parent gave me  %s",b);

        }
    else
     printf("fork error");   
    return 0;
}
