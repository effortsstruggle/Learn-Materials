#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<stdio.h>
#include<string.h>
using namespace std;

//命名管道(外存)
int main()
{
	//p:管道文件
	int mk = mkfifo("./msg.data",0666);
	if(mk<0&&errno!=EEXIST)//忽略创建文件失败
	{
		cerr<<"create communication fail"<<endl;
		return -1;
	}

	//1.打开
	int fd=open("msg.data",O_WRONLY);
	if(fd<0)
	{
		cerr<<"open fail"<<endl;
		return -2;	
	}
	//2.操作
	char buf[20]="I Love You";
	write(fd,buf,strlen(buf));
	//3.关闭
	close(fd);
	return 0;
}
