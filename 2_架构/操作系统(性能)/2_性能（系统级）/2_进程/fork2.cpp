#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>

using namespace std;

int main()
{
	int i=100;
	int pid = fork();
	if(pid>0)
	{
		i=200;	
		cout<<"父进程:"<<i<<endl;	
		wait(NULL);
	}
	else if(pid==0)
	{
		cout<<"子进程:"<<i<<endl;
		
	}

	return 0;
}
