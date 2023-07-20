#include<iostream>
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
using namespace std;

//共享内存
int main()
{
//0.(生成唯一key值)
	key_t key=ftok("./",1);
//1.创建共享内存:返回内存编号(标识符)	
	int shmid=shmget(key,100,0666|IPC_CREAT);
	cout<<shmid<<endl;
	if(shmid<0)
	{
		perror("shmget fail");
		return -1;
	}

//2.shmid映射:转换为逻辑地址 
//ploc:记录了共享内存的首地址
	char* ploc = (char*)shmat(shmid,NULL,0);
	if(ploc==NULL)
	{
		perror("shmat fail");
		return -1;	
	}
//3.使用(地址)
	strcpy(ploc,"hello , nice to meet you");
	return 0;
}
