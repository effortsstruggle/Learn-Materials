#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
using namespace std;

void* recvMsg(void* arg)
{
	int sock = *(int*)arg;
	char buf[100]="";
	int ilen = -1;
	while((ilen=recv(sock,buf,99,0))>0)
	{
		buf[ilen]='\0';
		cout<<buf<<endl;
	}
}

//客户端
int main()
{
	int vtl ; 
	//1.创建套接字(流式套接字)
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("opne fail");
		return -1;
	}

	//地址复用:SO_REUSEADDR
	int opt = sizeof(int);
	vtl = setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	if(vtl<0)
	{
		perror("setsocketopt fail");
		return -1;
	}
	
	//2.绑定套接字
	struct sockaddr_in myaddr;
	myaddr.sin_family 	=AF_INET;
	myaddr.sin_addr.s_addr  =INADDR_ANY;
	myaddr.sin_port		=htons(7980);
	
	vtl = bind(sock,(struct sockaddr*)&myaddr,sizeof(myaddr));
	if(vtl<0)
	{
		perror("bind fail");
		return -2;
	}
	
	//3.连接服务器(主动连接)
	struct sockaddr_in saddr;
	saddr.sin_family	=AF_INET;
	saddr.sin_addr.s_addr	=inet_addr("192.168.1.134"); 
	saddr.sin_port		=htons(7979);
	if(connect(sock,(struct sockaddr*)&saddr,sizeof(saddr))<0)
	{
		perror("connect fail");
		return -1;
	}
	//开线程
	pthread_t tid;
	pthread_create(&tid,NULL,recvMsg,&sock);
	char buf[100]="";
	while(1)
	{
		cout<<"please input:";
		cin>>buf;
		if(strcmp(buf,"exit")==0)
			break;
		send(sock,buf,strlen(buf),0);
	}
	//6.关闭
	close(sock);
	return 0;
}
