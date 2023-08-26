#!/bin/bash

#shell字符串:可以是单引号，双引号，也可以不用引号
str='this is a string'
str1="this is a string"
#str2=this is a string
echo ’good ${str}‘
echo "good \"${str1}\" "
#echo ${str2}


#拼接字符串
your_name="runoob"
#双引号拼接
greeting="hello,"${your_name}" !"
greeting_1="hello,${your_name} !"
echo $greeting $greeting_1

greeting='hello,'${your_name}'!'
greeting_1='hello,${your_name} !'
echo $greeting $greeting_1

#获取字符串长度(#字符串名)
string="abcd"
echo ${#string}

#提取子字符串 :字符串第2个字符开始截取4个字符（第一个字符索引值为：0）
string="runoob is a great site"
string_2="${string:1:4}"
echo ${string:1:4}
echo ${string_2}

#查找子字符串 （``反引号）: 查找字符i 或 o 的位置（哪个字母先出现就计算哪个）
echo `expr index "${string}" io` #输出4

