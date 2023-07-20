#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include<iostream>
#include<queue>
using namespace std;

typedef void* (*pfunction) (void*);

//任务
typedef struct
{
	pfunction pfun;
	void* arg;
}task_t;

//线程池管理器
class ThreadPool
{
public:	
	ThreadPool(int);
	void addTask(task_t);
	void addTask(pfunction,void*);
	//工作线程
	void run();

private:
	queue<task_t> q;//任务队列

	const int num;
	
	bool shutdown;
	
	pthread_mutex_t lock;
	pthread_cond_t cond;
};

#endif
