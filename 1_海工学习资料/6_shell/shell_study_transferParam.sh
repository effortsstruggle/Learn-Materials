#!/bin/bash

#执行脚本时，可以向脚本传递参数
:<<EOF
	${n} : n代表一个数字，1为执行脚本的第一个参数 ，以此类推
	${#} : 传递到脚本参数个数
	${*} : 以字符串形式，显示所有向脚本传递的参数
EOF

echo "Shell 传递参数实例！";
echo "执行的文件名：${0}";
echo "第一个参数为：${1}";
echo "第二个参数为：${2}";
echo "第三个参数为：${3}";

echo "参数个数：$#"
echo "传递参数作为1个字符串显示：$*" #如参数 1 2 3 ， ”1 2 3“
echo "传递参数作为3个字符串显示: $@" #如参数 1 2 3 ， ”1“ ”2“ ”3“
echo "脚本运行当前进程ID号: $$"
echo "后台运行的最后一个进程ID号: $!"

#测试S* S@的区别
echo "----\$* 演示----"
for i in "$*"
do
	echo ${i}
done

echo "----\$@ 演示----"
for i in "$@"
do
	echo ${i}
done
