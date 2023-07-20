#include<iostream>
#include<signal.h>
using namespace std;

void fun(int signum)
{
	if(signum==SIGUSR1)
	{
		cout<<"除数为5"<<endl;
	}
}

int main()
{
	//
	signal(SIGUSR1,fun);
	int i=0;
	for(i=1;i<=100;i++)
	{
		if(i%5==0)
			raise(SIGUSR1);
		cout<<i<<endl;
		sleep(1);
	}
	return 0;
}
	
