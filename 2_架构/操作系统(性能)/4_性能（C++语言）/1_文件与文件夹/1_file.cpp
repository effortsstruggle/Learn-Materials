#include<iostream>
#include<fstream>
using namespace std;

struct student
{
	int id;
	char name[15];
	char sex;
	float score;
	char addr[20];
};

//c++ : 文件
void file_w()
{
	//1.打开文件(实例化时调用构造器时打开，或者调用open函数打开)
	ofstream fout("./a.txt",ios::out);
	
	if(fout.fail())
	{
		cerr<<"open fail"<<endl;
		return ;
	}
	//2.操作文件
	struct student s[3]={\
			{1001,"wangqin",'m',92,"湖北"},\
			{1002,"lg",'w',91,"湖南"},\
			{1003,"gj",'m',10,"湖北"}\
		     };
	for(int i=0;i<3;i++)
		fout<<s[i].id<<" "
			<<s[i].name<<" "
			<<s[i].sex<<" "
			<<s[i].score<<" "
			<<s[i].addr<<endl;
	
	//3.关闭文件
	fout.close();	
}

//读
void file_r()
{
	//1.打开文件
	ifstream fin("./a.txt",ios::in);
	if(fin.fail())
	{
		cerr<<"open fail"<<endl;
		return ;
	}
	student s;
	//2.操作文件
	while(1)
	{
		fin>>s.id>>s.name>>s.sex>>s.score>>s.addr;
		if(fin.eof())//避免最后一个输出两次
			break;
		cout<<s.id<<" "<<s.name<<" "<<s.sex<<" "<<s.score<<" "<<s.addr<<endl; 
	}
	//3.关闭文件
	fin.close();
}

void getMax()
{
	//1.打开
	//第一种
	ifstream fin("./a.txt",ios::in);//fopen("./a.txt","w+");
/*
	//第二种		
	ifstream fin;
	fin.open("./a.txt",ios::in);
*/
	if(fin.fail())
	{
		cerr<<"open fail"<<endl;
		return ;
	}
	//2.操作文件
	student s;

	int ploc=0,ploc1=0;//记录位置
	
	ploc = fin.tellg();//ploc记录最大值的位置
		
	int listen=0;//监哨值
	
	while(1)
	{
		ploc1 = fin.tellg();
		//读取文件
		fin>>s.id>>s.name>>s.sex>>s.score>>s.addr;
		
		if(fin.eof())
			break;
		
		if(s.score>listen)
		{
			listen = s.score;
			ploc=ploc1;
		}
	}
	
	fin.clear();//设置位置之前需要先清除当前流相关的标志
	fin.seekg(ploc,ios::beg);
	
	fin>>s.id>>s.name>>s.sex>>s.score>>s.addr;
	cout<<s.id<<" "<<s.name<<" "<<s.sex<<" "<<s.score<<" "<<s.addr<<endl; 
	
	//3.关闭文件
	fin.close();

}

int main()
{	
	file_w();
//	file_r();
	
	getMax();
	return 0;
}
