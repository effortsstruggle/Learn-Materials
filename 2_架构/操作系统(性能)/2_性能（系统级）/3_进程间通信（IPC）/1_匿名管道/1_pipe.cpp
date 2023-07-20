#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
using namespace std;

//匿名管道
int main()
{
	//fd[0]  fd[1]:读/写端
	int fd[2];
	//创建管道
	int pip = pipe(fd);
	//cout<<fd[0]<<" "<<fd[1]<<endl;//创建成功，fd[0]:3 fd[1]:4
	if(pip<0)
	{
		//创建失败(返回-1)
		cerr<<"pipe fail"<<endl;
		return -1;
	}

	//创建子进程
	int pid=fork();	
	int i=0;
	if(pid>0)//父进程-->读取信息
	{
		close(fd[1]);//关闭写入端

		//读取信息:
		char buf[20];
		int ilen=0;
		while((ilen=read(fd[0],buf,sizeof(buf)))>0)
		{
			//read读取时没有'\0'
			buf[ilen]='\0';
			cout<<"子进程想说:"<<buf<<endl;
		}
	
		close(fd[0]);//关闭读取端
		wait(NULL);
	}
	else if(pid==0)//子进程---》发送消息
	{
		close(fd[0]);//关闭读
	
		//写入信息
		char buf[20];
		while(1)
		{
			cin>>buf;
			write(fd[1],buf,strlen(buf));
		}

		close(fd[1]);//关闭写入端
		
	}
	
	return 0;
}
