#include<iostream>
#include<sys/ioctl.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<stdio.h>
using namespace std;
void fun(int);

int main()
{
	int vtl = -1 , readfd=0;//readfd轮询条件
	//1.创建套接字
	int sockid = socket(AF_INET,SOCK_STREAM,0);	
	if(sockid<0)
	{
		perror("create socket fail");
		return -1;
	}
	
	//设置地址复用
	int opt = sizeof(int);
	vtl = setsockopt(sockid,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	if(vtl<0)
	{
		perror("setsockopt fail");
		return -1;
	}
	//2.绑定套接字
	struct sockaddr_in myaddr;
	myaddr.sin_family	=AF_INET;
	myaddr.sin_addr.s_addr	=INADDR_ANY;
	myaddr.sin_port		=htons(7110);
	vtl = bind(sockid,(struct sockaddr*)&myaddr,sizeof(myaddr));
	if(vtl<0)
	{
		perror("bind fail");
		return -2;
	}
	
	//3.监听
	vtl = listen(sockid,20);
	if(vtl<0)
	{
		perror("listen fail");
		return -3;
	}
	//4.等待连接
	int newsock;
	//使用select模型:监听sockid 套接字
	fd_set rset,oldrset;//文件描述符集
	FD_ZERO(&rset);//清空每一个位置的文件描述符
	FD_SET(sockid,&rset);//设置sockid --> rset 中(监管sockid)
	while(1)
	{
		//调用select 监听 sockid 到来
		//先备份
		oldrset = rset;
		//监听事件到达-->事件到达直接返回	
		vtl = select(FD_SETSIZE,&oldrset,NULL,NULL,NULL);
		if(vtl<=0)//<0  异常 =0 超时
		{
			perror("select fail");
			break;
		}
		else//状态发生改变,数据到来
		{
			for(readfd = 0 ; readfd<FD_SETSIZE ; readfd++)
			{
				if(FD_ISSET(readfd,&oldrset))//监听给定位readfd是否被置位
				{
					if(readfd == sockid)//有客户端连接
					{
						newsock = accept(sockid,NULL,NULL);
						if(newsock<0)
						{
							perror("accept fail");
							break;
						}
						//添加到newsock文件描述符集中
						FD_SET(newsock,&rset);
					}
					else
					{
						//获取数据长度
						int ilen = -1;
						ioctl(readfd,FIONREAD,&ilen);//获取数据长度
						if(ilen<=0)
						{
							close(readfd);
							FD_CLR(readfd,&rset);
							cout<<"客户端断开..."<<endl;
						}
						else
						{
							//5.收发消息
							fun(readfd);
						}
					}
				}
			}
		}
	}
	
	//6.关闭
	close(sockid);
	return 0;
}

void fun(int newsock)
{
	char cmdline[100]="";
	//存放字符串
	char buf[100]="";
	int ilen = -1,i=0,j=0;
	while((ilen = recv(newsock,buf,99,0))>0)
	{
		buf[ilen]='\0';
		i=0;
		while(buf[i]!='\0')
		{
			if(buf[i]!='\n')
				cmdline[j++]=buf[i];
			else//i=='\n'
			{
				cmdline[j]='\0';
				j=0;
				char a[20],b[20],c[20];
				sscanf(cmdline,"%s %s %s",a,b,c);
				cout<<a<<" "<<b<<endl;	
				break;
			}
			i++;
		}
		break;
	}
	close(newsock);		
}
