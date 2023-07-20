#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
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
	//2.绑定套接字（分配端口号）,必须绑定
	struct sockaddr_in myaddr;
	myaddr.sin_family	=AF_INET;//地址类型
	myaddr.sin_addr.s_addr 	=INADDR_ANY;//网卡, 随机
	//128以下端口  被占用
	myaddr.sin_port 	=htons(7979);	//端口号 short 1-65535

	if(bind(fd,(struct sockaddr*)&myaddr,sizeof(myaddr))<0)
	{
		cerr<<"bind fail"<<endl;
		return -2;
	}

	//3.接收
	int ilen = 0;
	char buf[100]="";
	while((ilen=recv(fd,buf,99,0))>0)
	{
		buf[ilen]='\0';
		if(strcmp(buf,"reboot")==0)
		{
			system("reboot");
		}
	}

	return 0;
}
