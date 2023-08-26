#!/bin/bash


:<<EOF
	if 语法：

		if condition
		then
    			command1 
  			command2
    			...
    			commandN 
		fi
	if else 语法：
		if condition
		then
    			command1 
    			command2
    			...
    			commandN
		else
    			command
		fi

	if elif else语法：
		if condition1
		then
    			command1
		elif condition2 
		then 
    			command2
		else
    			commandN
		fi


	if else 语句经常与 test 命令配合使用;


	case ... esac 语法：
		case 值 in
		模式1)
    			command1
    			command2
    			...
    			commandN
    		;; #分支结束标志
		模式2)
   			command1
    			command2
    			...
    			commandN
    		;;
		esac # case结束标志

	
	sh流程控制注意事项：
		1.sh流程控制不可为空，（如：else中没有语句执行，就不要写else）
EOF

numLine=$(ps -ef | grep -c "ssh")
echo ${name}

#使用[ ... ] 	大于:-gt 	小于:-lt
if [ ${numLine} -gt 1 ]
then
	printf "进程中包含ssh的个数大于1：%d \n" ${numLine}
elif [ ${numLine} -lt 1 ]
then
	printf "进程中包含ssh的个数小于1：%d \n" ${numLine}
else
	printf "进程中包含ssh的个数等于1：%d \n" ${numLine}
fi


#使用((...))  >  < 
if (( ${numLine} > 1 ))
then
	printf "进程中包含ssh的个数大于1：%d \n" ${numLine}
elif (( ${numLine} < 1 ))
then
	printf "进程中包含ssh的个数小于1：%d \n" ${numLine}
else
	printf "进程中包含ssh的个数等于1：%d \n" ${numLine}
fi


#if 与 test 配合使用
num1=$[2*3]
num2=$[1+5]
if test $[num1] -eq $[num2]
then
    echo '两个数字相等!'
else
    echo '两个数字不相等!'
fi



echo '输入 1 到 4 之间的数字:'
echo '你输入的数字为:'
read aNum
case $aNum in
#    1)  echo '你选择了 1'
#   ;;
#    2)  echo '你选择了 2'
#    ;;
#    3)  echo '你选择了 3'
#    ;;
#    4)  echo '你选择了 4'
#   ;;
    1|2|3|4|5)
	echo "你输入的数值为：${aNum}"	
    ;;
    *) 
	 echo '你没有输入 1 到 4 之间的数字'
    ;;
esac





site="runoob"

case ${site} in
   "runoob") echo "菜鸟教程"
   ;;
   "google") echo "Google 搜索"
   ;;
   "taobao") echo "淘宝网"
   ;;
esac


