#include<iostream>
#include<pthread.h>
#include"threadPool.h"
using namespace std;
void* threadfun(void*);

ThreadPool::ThreadPool(int num):num(num),shutdown(false)
{
	//初始化锁，初始化条件
	pthread_mutex_init(&lock,NULL);
	pthread_cond_init(&cond,NULL);
	
	int i=0;
	pthread_t tid;
	for(i=0;i<num;i++)
	{
		pthread_create(&tid,NULL,threadfun,this);
	}
}

void ThreadPool::run()
{
	while(1)
	{
		pthread_mutex_lock(&this->lock);
		while(this->q.size()==0)
		{
			cout<<pthread_self()<<"进入冬眠..."<<endl;
			pthread_cond_wait(&this->cond,&this->lock);
		}
		cout<<pthread_self()<<"开始执行任务了"<<endl;

		task_t t = this->q.front();
		this->q.pop();
		
		pthread_mutex_unlock(&this->lock);
		//执行任务
		t.pfun(t.arg);
	}
}

void ThreadPool::addTask(pfunction p , void* arg)
{
	task_t t;
	t.pfun = p;
	t.arg = arg;
	
	this->q.push(t);
	pthread_cond_broadcast(&this->cond);
}



void ThreadPool::addTask(task_t t)
{
	this->q.push(t);
	pthread_cond_broadcast(&this->cond);
}

void* threadfun(void* arg)
{
	pthread_detach(pthread_self());
	cout<<pthread_self()<<"被创建了..."<<endl;
	ThreadPool* pool = (ThreadPool*)arg;
	pool ->run();
}
