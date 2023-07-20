#include<iostream>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
using namespace std;

int main()
{
	key_t key=ftok("./",1);//和写入的路径必须一模一样
	//不需要创建空间
	int shmid=shmget(key,100,0666|IPC_CREAT);
	//2.地址映射
	char* ploc=(char*)shmat(shmid,NULL,0);

//	strcpy(ploc,"hello kugou");
	cout<<ploc<<endl;

	return 0;
}
