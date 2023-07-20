
//执行shell命令
#include <stdlib.h>
int system(const char *command);

popen
#include <stdio.h>
		FILE *popen(const char *command, const char *type);
		int pclose(FILE *stream);


exec 系列


#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
using namespace std;
		l: 可变形参   
	   int execl(const char *path, const char *arg, ...);
       int execlp(const char *file, const char *arg, ...);
       int execle(const char *path, const char *arg,
                  ..., char * const envp[]);
				  
		v:固定形参   p : 环境变量    没有 p : 固定路径
       int execv(const char *path, char *const argv[]);
       int execvp(const char *file, char *const argv[]);

//本程序
int main()
{
/*
	char* path="/home/LF/0822";
	cout<<"获取"<<path<<"下的文件的属性"<<endl;
//顺序  选择  循环	
	//通过ls来执行该路径下的文件属性	
	if(execlp("ls","ls","-l",path,NULL)<0)//环境变量
	{
		cerr<<"execlp fail"<<endl;
	}

	cout<<"程序结束"<<endl;
*/
	char* argv[5]={"/bin/ls","-l","/home/LF/0822"};
	//因为execv函数族会替换本进程空间，但是只需要执行一次但不希望影响本进程指令，可以交给子进程来执行，并等待子进程运行结束
	int pid=fork();
	if(pid>0)//父进程
	{
		//等待子进程并善后处理
		wait(NULL);
		cout<<"等待子进程运行结束"<<endl;
	}
	else if(pid==0)//子进程执行
	{
		execv(argv[0],argv);
	}	
	

	return 0;
}




