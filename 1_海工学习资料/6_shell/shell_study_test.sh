#!/bin/bash

:<<EOF
	
	test命令
		1.用于检查某个条件是否成立；
		2.它可以进行数值、字符和文件三方面的测试
EOF


num1=100
num2=100
if test ${num1} -eq ${num2} 
then
    echo '两个数相等！'
else
    echo '两个数不相等！'
fi


#执行基本的算数运算 [] , (( ))
result=$[num1+num2]
echo "result 为：${result}"


num1="runoob"
num2="runoob"
if test ${num1} = ${num2}
then 
	echo "两个字符串相等"
else 
	echo "两个字符串不相等"
fi
