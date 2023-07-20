#include<iostream>
#include<signal.h>
using namespace std;

void showlist(sigset_t& block)
{
	for(int i=1;i<32;i++)
	{
		//判定i信号 是否存在屏蔽集中
		if(sigismember(&block,i))
			cout<<"1";
		else
			cout<<"0";
	}
	cout<<endl;
}
void fun(int signum)
{
	if(SIGINT==signum)
		cout<<"ctrl+c被按下了"<<endl;
}

int main()
{
	//定义信号集
	sigset_t pset,oldpset;
	//清空屏蔽集:必须清空
	sigemptyset(&pset);
	
        //往屏蔽集中添加需要的信号
         sigaddset(&pset,SIGINT);
         //修改-->只屏蔽SIGINT
         
	sigprocmask(SIG_BLOCK,&pset,&oldpset);

	signal(SIGINT,fun);
	int i=0;
	while(i<100)
	{
		//获取进程的未决
		sigpending(&pset);
		showlist(pset);
		sleep(1);
		if(i==10)
			sigprocmask(SIG_SETMASK,&oldpset,NULL); //解除屏蔽
		i++;
	}
	return 0;
}
