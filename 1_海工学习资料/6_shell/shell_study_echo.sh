#!/bin/bash

str="name"

echo "It is test"


#显示转义字符
echo " \"It is test\" "


#原样输出，不进行转义或取变量（单引号）
echo '${str}\"'


#显示换行( -e : 开启转义 , \n：换行 \c 不换行)
echo -e "OK! \c"
echo "It is a test"


#输出结果至文件(重定向)
echo "It is a test" > myfile


#从标准输入中读取一行，指定给shell变量(阻塞)
read name
echo "${name} It is a test"


#显示命令执行结果 (反引号)
echo `date`
echo `pwd`
