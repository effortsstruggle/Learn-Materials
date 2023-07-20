#include<iostream>
#include<string.h>
#include<stdio.h>
#include <arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include"threadPool.h"
using namespace std;


void* fun(void*);
pthread_mutex_t  lock = PTHREAD_MUTEX_INITIALIZER;

//服务器端 
int main()
{
	ThreadPool pool(5);
	
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
	myaddr.sin_port		=htons(7110);
		
	vtl = bind(sid,(struct sockaddr*)&myaddr,sizeof(myaddr));
	if(vtl<0)
	{
		perror("bind fail");
		return -3;
	}
	//3.监听
	vtl = listen(sid,20);
	if(vtl<0)
	{
		perror("listen fail");
		return -4;
	}

	int newsock ;
	struct sockaddr_in saddr;
	socklen_t len = sizeof(saddr);
	//4.等待连接
	while(1)
	{
		//上锁 
		pthread_mutex_lock(&lock);
		newsock = accept(sid,(struct sockaddr*)&saddr,&len);	
		cout<<inet_ntoa(saddr.sin_addr)<<"/"<<ntohs(saddr.sin_port)<<":建立连接"<<endl;
		if(newsock<0)
			break;
		//每个用户创建一个线程
		pool.addTask(fun,&newsock);
	/*
		pthread_t tid;
		vtl=pthread_create(&tid,NULL,fun,&newsock);
		if(vtl<0)
		{
			perror("create thread fail");
			pthread_mutex_unlock(&lock);
			continue;
		}
	*/
	}	
	//5.收发信息
	//6.关闭
	close(sid);
	return 0;
}

void* fun(void* arg)
{
	int newsock = *(int*)arg;
	//解锁
	pthread_mutex_unlock(&lock);
	
	char buf[100]="";
	int ilen = -1, size , total;
	while(1)
	{
		total = sizeof(int);
		//1.先接收长度
		while((ilen=recv(newsock,buf+sizeof(int)-total,total,0))>0)
			total -= ilen;
		size = total = *(int*)buf;	
		buf[total]='\0';	
		//2.在接收数据
		while(total>0)
		{
			//从头开始，没接收完，从后面开始
			ilen=recv(newsock,buf+size-total,total,0);
			total -= ilen;	
		}		
		if(!strcmp(buf,"exit"))
			break;

		cout<<"收到:"<<buf<<endl;
	}
	cout<<"客户端断开..."<<endl;
	//关闭
	close(newsock);
}
