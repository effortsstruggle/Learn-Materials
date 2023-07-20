#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/wait.h>
using namespace std;

int main(int argc , char* argv[])
{
	if(argc!=2)
	{
		cerr<<"形参不匹配"<<endl;
		return -1;
	}
	int fd[2];
	//创建匿名管道
	if(pipe(fd)<0)
	{
		cerr<<"create pipe fail"<<endl;
		return -3;
	}

	pid_t pid = fork();
	if(pid>0)
	{
		close(fd[1]);
		char ch;
		char buf[100],spid[20],tty[20],time[20],cmd[20];
		int index=0;
		//解析字符串
		while(read(fd[0],&ch,1)>0)
		{
			if(ch!='\n')
				buf[index++]=ch;
			else
			{
				buf[index]='\0';
				index=0;
				sscanf(buf,"%s %s %s %s",spid,tty,time,cmd);
				if(!strcmp(cmd,argv[1]))
					kill(atoi(spid),SIGKILL);
			}
		}
		
		close(fd[0]);
		wait(NULL);
	}
	else if(pid==0)
	{
		close(fd[0]);
		dup2(fd[1],1);
		
		if(execlp("ps","ps","-e",NULL)<0)
		{
			cerr<<"execlp shell fail"<<endl;
			return -4;
		}
		close(fd[1]);
	}
	else
	{
		cerr<<"create process fail"<<endl;
		return -2;
	}
	


	return 0;
}
