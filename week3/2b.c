#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
int main()
{
    int f[2];
    pipe(f);
    pid_t p=fork();

    if(p==-1) 
        printf("fork error");

    else if(p==0)
    {
        //I am the child
        

        close(f[1]);
        dup2(f[0],0); //stdin is now f[0];
        system("sort");
    }

    else
    {
        //This is the parent here
        

        close(f[0]);
        dup2(f[1],1); //stdout is now f[1] 
        system("ls -l");
    }
    return 0;
}
