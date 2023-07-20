#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;

#define GET(S) (((S)&0xff00)>>8)

int main()
{
	cout<<"当前进程pid号:"<<getpid()<<endl<<"当前进程父进程pid号:"<<getppid()<<endl;
	
	//获取pid
	//创建子进程(创建方法:将父进程空间拷贝一份给子进程)
	//父进程，返回的是子进程的pid号
	int pid=fork();//指令寄存器(会记录上面代码已经执行完毕)
	
	if(pid>0) //父进程代码区
	{
		cout<<"当前进程pid:"<<getpid()<<" 父进程pid:"<<getppid()<<endl;

		cout<<"我是父进程:"<<getpid()<<endl;
		cout<<"等待子进程退出"<<endl;
		//wait(NULL);//解决僵尸进程问题(当子进程退出时，父进程不为之"善后处理",称为僵尸进程）
		
		
		//孤儿进程:父进程先于子进程执行完，子进程就成为孤儿进程，那么孤儿进程的父进程为1
		int status;
		wait(&status);
		
		//第二个字节记录了status状态
		//cout<<GET(status)<<endl;
		if(GET(status))
		{
			cout<<"正常退出"<<endl;
		}
		else 
			cout<<"异常退出"<<endl;
	}
	else if(pid==0) //子进程代码区
	{
		cout<<"当前进程pid:"<<getpid()<<" 父进程pid:"<<getppid()<<endl;
		return 100/0;
		//return 0;
	}

	return 0;
}
