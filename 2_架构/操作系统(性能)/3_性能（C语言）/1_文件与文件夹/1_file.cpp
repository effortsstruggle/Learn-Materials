#include<iostream>
#include<stdio.h>
using namespace std;

typedef struct 
{
	int id;
	char name[20];
	char sex;
	float height;
	int age;
	float score;
	char addr[20];

}msg;

//c语言文件:
//写
void file_w()
{
	//1.打开文件
	FILE* file = fopen("./msg.txt","w+");
	
	msg m[4]={
			{1001,"wangqin",'m',176.5,21,99.0,"湖北"},\
			{1002,"tade",'m',156.5,22,59.0,"湖北"},\
			{1003,"sr",'m',116.5,23,9.0,"湖北"},\
			{1004,"mg",'m',156.5,24,59.0,"重庆"}
		 }; 
		 
	
	for(int i=0;i<4;i++)
	{
		//2.操作文件
		fprintf(file,"%d %s %c %f %d %f %s\n",m[i].id,m[i].name,m[i].sex,m[i].height,m[i].age,m[i].score,m[i].addr);
	}
	//3.关闭文件
	fclose(file);
}

//读
void file_r()
{
	//1.打开文件
	FILE* file = fopen("./msg.txt","r+");
	if(!file)
	{
		perror("open fail");
		return ;
	}
	
	msg m;
	while(1)
	{
		//2.操作文件
		fscanf(file,"%d %s %c %f %d %f %s",&m.id,m.name,&m.sex,&m.height,&m.age,&m.score,m.addr);
		    if(feof(file))
				break;		

		printf("%d %s %c %f %d %f %s\n",m.id,m.name,m.sex,m.height,m.age,m.score,m.addr);
	}
	//3.关闭文件
	fclose(file);
}

//查找成绩最大的信息
void getMax()
{
	//1.打开文件
	FILE* file = fopen("./msg.txt","r+");
	if(file==NULL)
	{
		perror("open fail");
		return ;
	}
	//2.操作文件
	msg m;
	int listen =0;//监哨值法
	int ploc=0,ploc1=0;//ploc ploc1:记录位置（其中ploc1记录最大值位置）
	
	while(1)
	{
		
		//获取读写位置
		int ploc = ftell(file);
		
		fscanf(file,"%d %s %c %f %d %f %s",&m.id,m.name,&m.sex,&m.height,&m.age,&m.score,m.addr);
		
		if(feof(file))
		     break;	
		
		if(listen<m.score)
		{
			ploc1=ploc;
			listen = m.score;	
		}
	}
	//定位
	fseek(file,ploc1,SEEK_SET);
	
	fscanf(file,"%d %s %c %f %d %f %s",&m.id,m.name,&m.sex,&m.height,&m.age,&m.score,m.addr);
	
	printf("%d %s %c %f %d %f %s\n",m.id,m.name,m.sex,m.height,m.age,m.score,m.addr);
	//关闭文件
	fclose(file);
}

int main()
{
	file_w();	
	//file_r();
	//getMax();

	return 0;
}
