#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
using namespace std;

typedef struct 
{
	int id;
	char name[20];
	char sex;
	float score;
}stu;

//写入文件
void file_w()
{
	//打开(返回文件描述符:文件描述符指向所打开的一块区域)
	int fd = open("./msg.data",O_CREAT|O_TRUNC|O_WRONLY,0664);	
	if(fd<0)
	{
		cerr<<"open fail"<<endl;
		return ;
	}
	stu s[3]={\
			{1001,"wangqin",'m',190},\
			{1002,"wgj",'w',102},\
			{1003,"ta",'w',100}\
			};
	//操作
	write(fd,s,sizeof(s));
	//关闭
	close(fd);
}
//读取文件
void file_r()
{
	//打开(返回文件描述符:文件描述符指向所打开的一块区域)
	int fd = open("./msg.data",O_RDONLY);	
	if(fd<0)
	{
		cerr<<"open fail"<<endl;
		return ;
	}
	stu s;
	//操作
	while(read(fd,&s,sizeof(stu))>0)
	{
		cout<<s.id<<" "<<s.name<<" "<<s.sex<<" "<<s.score<<endl;
	}
	//关闭
	close(fd);
}

void getMax()
{
	//打开(返回文件描述符:文件描述符指向所打开的一块区域)
	int fd = open("./msg.data",O_RDONLY);	
	if(fd<0)
	{
		cerr<<"open fail"<<endl;
		return ;
	}
	stu s;
	int listen=-1;
	int ploc=0;
	int ploc1=0;
	int ploc2=0;
	//操作
	while((ploc=read(fd,&s,sizeof(stu)))>0)
	{
		ploc1+=ploc;//记录读取后的位置
		if(s.score>listen)
		{
			listen=s.score;
			ploc2=ploc1-sizeof(stu);
		}
	}
	lseek(fd,ploc2,SEEK_SET);
	read(fd,&s,sizeof(stu));
	cout<<s.id<<" "<<s.name<<" "<<s.sex<<" "<<s.score<<endl;
	
	//关闭
	close(fd);
}

int main()
{
//	file_w();
	//file_r();

	getMax();
	return 0;
}
