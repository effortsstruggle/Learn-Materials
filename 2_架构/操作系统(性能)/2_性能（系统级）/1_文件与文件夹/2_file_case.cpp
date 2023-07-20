#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
using namespace std;

//案例:copy
void copy(char* argv1,char* argv2)
{
	//打开
	int fp = open(argv1,O_RDONLY);
	int fp2 = open(argv2,O_CREAT|O_WRONLY|O_TRUNC,0664);
	if(fp<0||fp2<0)
	{
		cerr<<"open fail"<<endl;
		return ;
	}
	char buf[100];
	int ilen=0;
	//操作
	while((ilen=read(fp,buf,100))>0)
	{
		write(fp2,buf,ilen);
	}
	//关闭
	close(fp);	
	close(fp2);
}

int main(int argc , char* argv[])
{
	if(argc!=3)
	{
		cout<<"参数不匹配"<<endl;
		return -1;
	}
	copy(argv[1],argv[2]);

	return 0;
}
