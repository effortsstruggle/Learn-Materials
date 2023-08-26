#!/bin/bash

:<<EOF
	printf :
		1. 可以格式化字符串，制定字符串宽度、左右对齐方式等；
		2.不会自动添加换行符，需要手动添加”\n“

	printf 命令语法：
		printf format-string [args]
	
	format-string : 为格式控制字符串
	args : 参数列表

	格式化替代符：
		%s :
		%d
		%c
		%f
	-10s : 宽度为10的字符( - : 左对齐 ， 没有：右对齐)
	-4.2f : 格式化为小数，保留2位小数


	转义序列：
		\a : 警告字符，通常为ASCII 的 BEL字符	
		\b ： 后退
		\c : 不显示输出结果中任何结尾的换行符
		\f ： 换页
		\n : 换行
		\r : 回车
		\t : 水平制表符
		\v : 垂直制表符
		\\ : 一个字面上的反斜杠字符
		\ddd ： 标识1 - 3 位数八进制字符(仅在格式化字符串中有效)
		\0ddd ：表示1 - 3 位数八进制字符
EOF


echo "Hello , Shell"

printf "Hello , Shell\n"


printf "%-10s , %-8s , %-4s\n" 姓名 性别 体重kg
printf "%-10s , %-8s , %-4.2f\n" abc 男 66.1234
printf "%-10s , %-8s , %-4.2f\n" efg 男 48.6543
printf "%-10s , %-8s , %-4.2f\n" hjk 女 47.9876


#格式只指定一个参数，但多出的参数仍会按照该格式输出（format-string被重用）
printf "%s\n" abc def


#如果没有args , 那么 %s 用 NULL 代替，%d用0代替
printf "%s and %d\n"



printf "www.baidu.com \a\n"
