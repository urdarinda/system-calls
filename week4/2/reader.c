#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
int main()
{
    printf("Hello from the reader %d, here is the sorted ls -l\n",getpid());
    dup2(open("/tmp/shell2",0),0); //0 readonly
    system("sort");
    unlink("/tmp/shell2"); // deleting the fifo
}
