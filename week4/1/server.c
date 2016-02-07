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

    unlink(serv);
    mkfifo(serv,0777);
    if( ( fserv=open(serv,0) )<0)
    {
        printf("Server Error\n");
        unlink(serv);
        return -1;
    }

    char client[20];
    read(fserv,client,20);
    char file_name[20];
    read(fserv,file_name,20);
    int fid;
    int fclient;
    if( (fclient=open(client,1)) <0)
        printf("Error connecting to client");
    else if( (fid=open(file_name,0)) <0)
        write(fclient,"File does not exist",30);
    else
    {
        char fcontents[1000];
        read(fid,fcontents,990);
        write(fclient,fcontents,strlen(fcontents)+1);
    }
    unlink(serv);
}
