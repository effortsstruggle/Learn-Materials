#include<iostream>
#include<sys/types.h>
#include<dirent.h>
using namespace std;

int main(int argc , char* argv[])
{
	if(argc==1)
		argv[1]="./";
	else if(argc!=2)
	{
		cout<<"输入参数有误"<<endl;
		return -1;
	}
	//1.打开文件夹
	DIR* dir = opendir(argv[1]);
	if(dir==NULL)
	{
		cout<<"opendir fail"<<endl;
		return -2;
	}
	struct dirent* d;//文件夹结构体
	//2.操作文件夹
	while(d=readdir(dir))
	{
		cout<<d->d_name<<endl;
	}
	//3.关闭文件夹
	closedir(dir);
	

	return 0;
}
