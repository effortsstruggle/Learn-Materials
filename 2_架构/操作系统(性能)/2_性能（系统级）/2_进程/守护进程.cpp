#include<iostream>
#include<stdio.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
using namespace std;

void time()
{
	//打开文件
	close(1);
	int fd=open("/home/gjj/desktop/0825/work/time.data",O_WRONLY|O_CREAT|O_TRUNC,0664);	
	if(fd<0)
	{
		cerr<<"open fail"<<endl;
		return ;
	}
	//复制制定文件描述符，并关闭
//	dup2(fd,1);
	//写入文件
	while(true)
	{
		time_t t;
		time_t tt=time(&t);
		struct tm* st=localtime(&t);
		cout<<st->tm_hour<<":"<<st->tm_min<<":"<<st->tm_sec<<endl;
		sleep(1);
	}
	//关闭文件
	close(fd);
}


int main()
{	
	//创建子进程，1.不受终端影响
	int pid=fork();
	if(pid>0)
		exit(0);
	else if(pid==0)
	{
		//不受用户影响（另立山头）
		setsid();//运行一个程序在新的会话中
		
		//2.修改文件掩码
		umask(0222);

		//3.修改制定工作目录
		chdir("/home/gjj/desktop");//切换工作目录
		
		time();

		//4.关闭不在需要的文件描述符
		int i=0;
		//cout<<_SC_OPEN_MAX<<endl;	
		long max=sysconf(_SC_OPEN_MAX);	//获取打开文件夹数的最大数量
		for(i=0;i<max;i++)
		{
			close(i);
		}
	}
	return 0;
}
