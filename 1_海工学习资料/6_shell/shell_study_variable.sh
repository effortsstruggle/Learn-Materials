#!/bin/bash
#定义变量
your_name="wq"
echo $your_name

#已定义的变量可以重新被定义
your_name="www.runoob.com"
#推荐使用
echo "redefine variable : ${your_name}"

#设置只读变量
myUrl="https://www.google.com"
readonly myUrl
#myUrl="1234"
echo "readonly variable : ${myUrl}"

#删除变量,unset 命令不能删除只读变量
#unset myUrl 
unset your_name
echo "del variable : ${your_name}"


#shell的变量类型
<< variableType
	局部变量: 当前shell程序中有效；
	环境变量：所有的shell程序，包括shell启动的程序都能访问；
	shell变量：shell程序设置的特殊变量，一部分是环境变量，另一部分局部变量
variableType







<< comment
#循环给变量赋值
for file in $(ls /etc) 
do
	echo ${file}
done


for skill in Ada coffe Action Java ; 
do
	echo "I am good at ${skill} Script"
done
comment

