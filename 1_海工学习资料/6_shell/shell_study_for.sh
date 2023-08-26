#!/bin/bash

:<<EOF
	循环控制:
		for循环：
			for var in item1 item2 ... itemN
			do
			    command1
			    command2
			    ...
			    commandN
			done

			in 列表可以包含替换，字符串和文件名

		while循环：
			while condition
			do
    				command
			done
		
		until循环：(条件为true时停止)
		until condition
		do
		    command
		done


		循环控制语句：
			break
			continue

EOF



#for循环
for loop in  1 2 3 4 5 
do
    echo "The value is: $loop"
done

for (( loop=1 ; loop<10 ; loop=`expr ${loop} + 1`))
do
	if(( loop==5 ))
	then
		#break
		continue
	fi
    echo "The value is: ${loop}"
    #let "loop++"
done


#while循环
int=1
#while(( $int<=5 ))
while(( ${int} <= 5 ))
do
    echo $int
    let "int++"
done
	

#循环读取键盘消息 FILM为变量名
echo '按下 <CTRL-D> 退出'
echo -n '输入你最喜欢的网站名: '
while read FILM
do
	echo "是的 ! ${FILM} 是一个好网站"
done

#死循环 
:<< EOF
while true
do
    command
done

#for (( ; ; ))

EOF


a=1
#until ! [ ${a} -lt 10 ]
#do
#	echo ${a}
#	let "a++"
#done

until !(( ${a} < 10 ))
do
	echo ${a}
	let "a++"
done
