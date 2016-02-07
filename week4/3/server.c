#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#define serv "/tmp/fifo_serv"
#include<sys/stat.h>
#include<string.h>
int main(int argc,char *argv[])
{
    int fserv;
    if(argc!=2)
    	return printf("Usage : server [no. of clients] \n"),0;
    unlink(serv);
    mkfifo(serv,0777);
    char client[20];
    char content[2000];
    int i=atoi(argv[1]);
    while(i--)
    {	
    	sleep(1);

    	if( ( fserv=open(serv,0) )<0)
    	{
        	printf("Server Error\n");
       	 	unlink(serv);
        	return -1;
    	}
    	read(fserv,client,20);
    	read(fserv,content,2000);
    	int fclient;
    	if( (fclient=open(client,1)) <0)
        	printf("Error connecting to client");
    	else
    		write(fclient,content,strlen(content)+1);
    	close(fserv);
    }		
    unlink(serv);
}
