#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
using namespace std;

int main()
{
	//1.打开
	int fd=open("./msg.data",O_RDONLY);
	//2.操作
	char buf[100];	
	read(fd,buf,99);
	cout<<buf<<endl;
	//3.关闭
	close(fd);


	return 0;
}
