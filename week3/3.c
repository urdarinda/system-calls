/*
 * 
 * The program returns an error 1 if no argument is passed to it for giving man page
 * The program returns an error 2 if a command which does not exist is passed for man page
 * The program prints the man page of the given command if it exists with an exit status 0
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
int main(int argc,char * argv[])
{
    pid_t p;

    int f[2];   //  original pipe
    pipe(f);

    int g[2];   //  to hold the actual stdout
    pipe(g);
    
    int h[2];   // to send the output of type command away from screen
    pipe(h);
    
    if(argc==1)  // No argument has been passed 
    {
        printf("Error, no argument found\n");
        exit(1);
   	}
    
    char lo[100]="type ";
    int len=strlen(argv[1]); 
    for(int i=5;i<len+5;i++) // lo will hold "type argv[1]"
        lo[i]=argv[1][i-5];

    
    dup2(1,g[1]);   // g[1] points to original stdout
    dup2(h[1],2);   // stderr redirected to h[1]
    dup2(h[1],1);   // stdout redirected to h[1]
    int l=system(lo);   // executes type argv[1] , checking if command exists
    dup2(g[1],1);   // stdout restored to terminal

    if(l)   // if command does not exist print and exit
    {
       printf("Command %s does not exist\n",argv[1]);
       exit(2);
    }

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
