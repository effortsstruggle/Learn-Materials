#include<iostream>
#include<stdio.h>
using namespace std;

/*
//二进制读写
void binary_w()
{
	FILE* file =fopen("./msg.txt","wb+");
	if(file==NULL)		
	{
		perror("open fail");
		return ;
	}
	int id=1001;
	char sex='m';
	char name[]="wangqin";
	fwrite(&id,1,sizeof(id),file);
	fwrite(&sex,1,sizeof(sex),file);
	fwrite(name,1,sizeof(name),file);
	fclose(file);
}

//二进制读
void binary_r()
{
	FILE* file =fopen("./msg.txt","rb+");
	if(file==NULL)		
	{
		perror("open fail");
		return ;
	}
	int id;
	char sex;
	char name[10];
	int ilen=0;
	fread(&id,1,sizeof(id),file);
	fread(&sex,1,sizeof(sex),file);
	fread(name,1,sizeof(name),file);
	printf("%d %c %s\n",id,sex,name);
	fclose(file);
}
*/

typedef struct 
{
	int id;
	char name[20];
	char sex;
	float score;
}student,*pstudent;

void binary_w()
{
	//1.打开文件
	FILE* file = fopen("./msg.data","wb+");
	if(file==NULL)
	{
		perror("open fail");
		return ;
	}
	student s[3]={\
			{1001,"王勤",'m',99},\
			{1002,"李芬",'w',91},\
			{1003,"他",'m',79}\
			};
	//2.操作文件
	fwrite(s,1,sizeof(student)*3,file);	
	//3.关闭文件
	fclose(file);
}

void binary_r()
{	
	//1.open文件
	FILE* file=fopen("./msg.data","rb+");
	if(!file)
	{
		perror("open fail");
		return ;
	}
	//2.operator文件
	student s;
	pstudent ps=&s;
	
	while(fread(ps,1,sizeof(student),file)>0)
	{
		printf("%d %s %c %f\n",ps->id,ps->name,ps->sex,ps->score);
	}
	//3.close文件
	fclose(file);

	
}



int main()
{
	//binary_w();	
	binary_r();	

	return 0;
}
