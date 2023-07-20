#include<iostream>
#include<fstream>
using namespace std;

typedef struct
{
	int id;
	char name[20];
	char sex;
	char addr[20];
	float score;
}people;

//c++ 二进制io
void file_w()
{
	//打开
	ofstream fout("./a.txt",ios::out);
	if(fout.fail())
	{
		cerr<<"open fail"<<endl;
		return ;
	}
	people p[3]={\
			{1001,"wangqin",'m',"湖北",10},\
			{1002,"刘滢",'w',"湖北",91},\
			{1003,"mg",'m',"湖南",92}\
			};
	//操作
		fout.write((char*)p,sizeof(people)*3);
	//关闭
	fout.close();
}

void file_r()
{
	//打开
	ifstream fin("./a.txt",ios::in);
	if(fin.fail())
	{
		cerr<<"open fail"<<endl;
		return ;
	}

	int listen = -1;
	int ploc=0;//记录开头读写位置
	int ploc1=0;
	people p;
	//操作
	while(fin.read((char*)&p,sizeof(people)))
	{
		ploc1=fin.tellg();
		if(listen<p.score)
		{
			listen=p.score;
			ploc=ploc1-sizeof(people);
		}
		//cout<<fin.gcount()<<endl;获取读取的字符数目
	}
	fin.clear();//必须先清除与当前流相关联的标志，设置位置之前:
	fin.seekg(ploc,ios::beg);
	fin.read((char*)&p,sizeof(people));
	cout<<p.id<<" "<<p.sex<<" "<<p.name<<" "<<p.score<<" "<<p.addr<<endl;

	//关闭
	fin.close();
}




int main()
{	
//	file_w();
	file_r();
	

	return 0;
}
