#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
using namespace std;

int main()
{
	//1.创建套接字
	int fd = socket(AF_INET,SOCK_DGRAM,0);//形参1: 协议簇Ipv4 -->AF_INET , 形参2：传输协议, 形参3： 0，同步，你不发，我死等，异步：各管各
	if(fd<0)
	{
		cerr<<"scoket fail"<<endl;
		return -1;
	}
	//2.绑定套接字（分配端口号）,不需要绑定
/*
	struct sockaddr_in myaddr;
	myaddr.sin_family	=AF_INET;//地址类型
	myaddr.sin_addr.s_addr 	=INADDR_ANY;//网卡, 随机
	//128以下端口  被占用
	myaddr.sin_port 	=htons(7979);	//端口号 short 1-65535
*/

	//3.发送
	struct sockaddr_in myaddr;
	myaddr.sin_family	=AF_INET;//地址类型
	myaddr.sin_port 	=htons(7979);	//端口号 short 1-65535
	myaddr.sin_addr.s_addr 	=inet_addr("192.168.1.109");//网卡, 指定地址

	int ilen = 0;
	char buf[100]="";
	while(1)
	{
		cout<<"Please input:";
		//cin>>buf;
		gets(buf);
		if(strcmp(buf,"exit")==0)
			break;
		sendto(fd,buf,strlen(buf),0,(struct sockaddr*)&myaddr,sizeof(myaddr));//套接字，内容 ， 内容长度 , 0 地址
	}

	//4.关闭
	close(fd);
	return 0;
}
