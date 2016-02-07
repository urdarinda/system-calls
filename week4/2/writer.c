#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
int main()
{
     
     
    printf("Hello, %d will write ls -l to the fifo\n",getpid());
    unlink("/tmp/shell2");

    if( mkfifo("/tmp/shell2",0666)<0) printf("Cant create fifo");

    //linking /tmp/shell2 with stdout
    dup2(open("/tmp/shell2",1),1); //1 writeonly
    
    system("ls -l");
}
