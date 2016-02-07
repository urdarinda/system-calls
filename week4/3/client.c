#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#define serv "/tmp/fifo_serv"
#include<sys/stat.h>
#include<string.h>

int main()
{
    int fserv; 
    if((fserv=open(serv,1))<0)
         return printf("Error connecting with server\n"),-1;
    char fname[30]="Hello from pid ";
    char str[1155];
    char client[20]="/tmp/fifo_";
    sprintf(client,"%s%d",client,getpid());
    sprintf(fname,"%s%d\n",fname,getpid());
    if(mkfifo(client,0777)<0)
    {
         printf("Error, server cant process request\n");
         unlink(client);
         return -2;
    }
    int a=write(fserv,client,20);
    int d=write(fserv,fname,30);
    int fclient;
    if((fclient=open(client,0))<0)
    {
        printf("Cant handle request\n");
        unlink(client);
        return -3;
    }
    read(fclient,str,990);
    printf("Server response :\n%s\n",str);
    
    unlink(client);

    
}
