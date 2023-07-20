#include<iostream>
#include<pthread.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
using namespace std;


//初始化锁
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void* fun(void* arg)
{	
	int newsock = *(int*)arg;
	pthread_mutex_unlock(&lock);

	//线程分离
	pthread_detach(pthread_self());	
	
	//收发消息
	char buf[100]="";
	int ilen = -1;
	struct sockaddr_in saddr;
	socklen_t length = sizeof(saddr);
	while((ilen = recvfrom(newsock,buf,99,0,(struct sockaddr*)&saddr,&length))>0)
	{
		buf[ilen]='\0';
		cout<<buf<<endl;
		sendto(newsock,"copy",4,0,(struct sockaddr*)&saddr,sizeof(saddr));
	}
	cout<<"客户端连接关闭"<<endl;
	close(newsock);
}


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
	myaddr.sin_port		=htons(7979);
	
	vtl = bind(sock,(struct sockaddr*)&myaddr,sizeof(myaddr));
	if(vtl<0)
	{
		perror("bind fail");
		return -2;
	}
	//3.监听
	vtl = listen(sock,100);
	if(vtl<0)
	{
		perror("listen fail");
		return -3;
	}
	//4.等待连接--连接成功，就返回一个新的描述符
	//sock -- 用来监听的,accept:阻塞函数
	//并发:
	//传统模式:为每一个客户端分配一个线程
	int newsock ;//公共量
	pthread_t tid;
	
	while(1)
	{
		pthread_mutex_lock(&lock);
		newsock=accept(sock,NULL,NULL);//公共量  污读污写
		cout<<"有一个客户端连接成功"<<endl;
		if(newsock < 0)
		{
			pthread_mutex_unlock(&lock);
			perror("accept fail");
			break;
		}
		
		if(pthread_create(&tid,NULL,fun,&newsock)<0)//污读污写
		{
			pthread_mutex_unlock(&lock);//失败，解锁
		}
	}
	//6.关闭
	close(sock);
	return 0;
}


