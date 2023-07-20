#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<dirent.h>
#include<string>
using namespace std;
/*遍历该路径下的文件*/
void list(/*const char* path*/string path)
{
	//1打开文件夹
	DIR* dir=opendir(path.c_str());
	if(!dir)//遍历失败
	{
		cerr<<"open fail"<<endl;
		return;
	}
	//2读取文件
	struct dirent* dt=NULL;
	while((dt=readdir(dir))!=NULL)
	{
		if(strcmp(dt->d_name,".")==0 || strcmp(dt->d_name,"..")==0)
			continue;
		cout<<dt->d_name<<endl;
		if(dt->d_type==DT_DIR)//若该文件夹下的文件名是文件夹，则继续遍历
		{
			//构成一个新的路径，并再次递归
			path+="/";	//path= /home/LF/0723
			path+=dt->d_name;
			list(path);
		}
	}
	//3关闭文件夹
	closedir(dir);
}
int main(int argc,char* argv[])
{
	list(argv[1]); 
	//遍历子文件时：  /父目录/子文件名
	//list("0723");
	return 0;
}
