#include<iostream>
#include<string.h>
#include<stdio.h>
#include <arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include"threadPool.h"
using namespace std;
//客户端 
int main()
{
	int vtl = -1;
	//1.创建套接字	
	int sid = socket(AF_INET,SOCK_STREAM,0);//0，同步
	if(sid<0)
	{
		perror("create socket fail");
		return -1;
	}

	//设置地址复用
	int opt = sizeof(int);
	vtl = setsockopt(sid,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	if(vtl<0)
	{
		perror("setsockopt fail");
		return -2;
	}
	//2.绑定套接字
	struct sockaddr_in myaddr;
	myaddr.sin_family 	=AF_INET;
	myaddr.sin_addr.s_addr	=INADDR_ANY;
	myaddr.sin_port		=htons(7100);
	vtl = bind(sid,(struct sockaddr*)&myaddr,sizeof(myaddr));
	if(vtl<0)
	{
		perror("bind fail");
		return -3;
	}
	//3.主动连接(连接服务器)
	struct sockaddr_in saddr;
	saddr.sin_family 	=AF_INET;
	saddr.sin_addr.s_addr	=inet_addr("192.168.1.153");
	saddr.sin_port		=htons(7110);

	vtl = connect(sid,(struct sockaddr*)&saddr,sizeof(saddr));
	if(vtl<0)
	{
		perror("bind fail");
		return -4;
	}
	//5.收发信息
	char buf[100]="";
	int length = 0;
	while(1)
	{
		cout<<"please input:";
		cin>>buf;
		length = strlen(buf);
		//1.先发送长度
		send(sid,&length,sizeof(length),0);
		//2.在发送数据
		send(sid,buf,length,0);	

		if(!strcmp(buf,"exit"))
			break;
	}
	//6.关闭
	close(sid);
	return 0;
}
