#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
int main(int argc,char * argv[])
{
    pid_t p;
    int f[2];
    pipe(f);
    p=fork();

    if(p==-1)
        printf("fork error");
    
    else if(p==0)
    {
        //child
    
        close(f[1]);
        dup2(f[0],0);
        char a[50];
        scanf("%s",a); // using dup2 to take argument rather than argv
        execl("/usr/bin/xterm","xterm","-e","man",a,0);
    }
    else
    {
        //parent
    
        close(f[0]);
        dup2(f[1],1);
        write(1,argv[1],strlen(argv[1]));
    }
    return 0;
}
