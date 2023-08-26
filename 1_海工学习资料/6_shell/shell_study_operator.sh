#!/bin/bash

:<<EOF
	shell运算符
		1.算数运算符
		2.关系运算符
		3.布尔运算符
		4.字符串运算符
		5.文件测试运算符	

	原生bash不支持简单数学运算，但可以通过其他命令来实现，例如：awk和expr , expr最常用
	expr是一款表达式计算工具，可以完成表达式求值操作
	
	expr表达式计算工具使用方式：
		需要使用``反引号括起来;
		表达式和运算符之间要有空格 ;
	正确写法：`expr 2 + 2`
	错误写法1：expr 2 + 2
	错误写法2：`expr 2+2`

	算数运算符：
		格式：`expr a 算数运算符 b`
		+ 
		- 
		* : 乘号（*）前边必须加反斜杠（\）才能实现乘法运算
		/
		%
		=
		==	
		!=

		另一种语法：
			$[ $a * $b ]
	
		BASH中用于计算的工具:
			let arg [arg...]
		arg : 要执行的表达式
		例：
			变量名 为 no
			自加操作： let no++
			自减操作： let no--
			简写： 	 let no+=10  ----》 no=no+10
		
	
	关系运算符:
		格式[$a 关系运算符 $b]

		-eq : 是否相等 		相等返回值true (equal)
		-ne : 是否不相等 	不相等返回true (not equal )
		-gt : a > b		若是返回true (greater than)
		-lt : a < b		若是返回true （less than）
		-ge : a >= b		若是返回true (greater than or equal)
		-le : a <= b 		若是返回true (less than or equal)

		格式 (($a > $b ))

	布尔运算符:
		! 非运算  取反	 [!表达式]
		-o ：或运算  	[ 表达式1 -o 表达式2 ] -----[$a -lt 20 -o b -gt 100] 
		-a ：与运算

	逻辑运算符:
		&& : 逻辑and
		|| : 逻辑or
	字符串运算符：
		格式 ： [$a 字符串运算符 $b]
		= : 两个字符串是否相等
		!= : 两个字符串是否不相等 
		-z : 字符串长度是否为0，[-z $a]
		-n : 字符串长度是否不为0 [-n $a]
		$ : 字符串是否不为空 [$a]
	文件测试运算符:
		格式： [文件测试运算符 $file]
		-b file 检查文件是否为块设备文件
		-c file 是否为字符设备文件
		-d file 是否是目录
		-f file 是否为普通文件
		-g file 是否设置了SGID位
		-k file 是否设置了Sticky Bit
		-p file 是否是有名管道
		-u file 是否设置了SUID位
		-r file 是否可读
		-w file 是否可写
		-x file 是否可执行
		-s file 是否为空
		-e file 是否存在（包括目录） 
		-S file : 判断某个文件是否Socket
		-L file : 检测文件是否存在并且是一个符号链接


EOF

val=`expr 2 + 2`
echo "expr 2+2=${val}"

#算数运算符
a=10
b=20

echo "----------------算数表达式-------------------------"
val=`expr $a + $b`
echo "a + b : $val"

val=`expr $a - $b`
echo "a - b : $val"

val=`expr $a \* $b`
echo "a * b : $val"

val=`expr $b / $a`
echo "b / a : $val"

val=`expr $b % $a`
echo "b % a : $val"

if [ $a == $b ]
then
   echo "a 等于 b"
fi

if [ $a != $b ]
then
   echo "a 不等于 b"
fi

#关系运算符
echo "----------------关系表达式-------------------------"
if [ $a -eq $b ]
then
   echo "$a -eq $b : a 等于 b"
else
   echo "$a -eq $b: a 不等于 b"
fi

if [ $a -ne $b ]
then
   echo "$a -ne $b: a 不等于 b"
else
   echo "$a -ne $b : a 等于 b"
fi

if [ $a -gt $b ]
then
   echo "$a -gt $b: a 大于 b"
else
   echo "$a -gt $b: a 不大于 b"
fi

if [ $a -lt $b ]
then
   echo "$a -lt $b: a 小于 b"
else
   echo "$a -lt $b: a 不小于 b"
fi

if [ $a -ge $b ]
then
   echo "$a -ge $b: a 大于或等于 b"
else
   echo "$a -ge $b: a 小于 b"
fi

if [ $a -le $b ]
then
   echo "$a -le $b: a 小于或等于 b"
else
   echo "$a -le $b: a 大于 b"
fi


#布尔表达式
echo "----------------布尔表达式-------------------------"
if [ $a != $b ]
then
   echo "$a != $b : a 不等于 b"
else
   echo "$a == $b: a 等于 b"
fi

if [ $a -lt 100 -a $b -gt 15 ]
then
   echo "$a 小于 100 且 $b 大于 15 : 返回 true"
else
   echo "$a 小于 100 且 $b 大于 15 : 返回 false"
fi

if [ $a -lt 100 -o $b -gt 100 ]
then
   echo "$a 小于 100 或 $b 大于 100 : 返回 true"
else
   echo "$a 小于 100 或 $b 大于 100 : 返回 false"
fi

if [ $a -lt 5 -o $b -gt 100 ]
then
   echo "$a 小于 5 或 $b 大于 100 : 返回 true"
else
   echo "$a 小于 5 或 $b 大于 100 : 返回 false"
fi

#逻辑表达式
echo "---------------逻辑表达式-------------------------"
if [[ $a -lt 100 && $b -gt 100 ]]
then
   echo "返回 true"
else
   echo "返回 false"
fi

if [[ $a -lt 100 || $b -gt 100 ]]
then
   echo "返回 true"
else
   echo "返回 false"
fi

#字符串表达式
echo "---------------字符串表达式-------------------------"
a="abc"
b="efg"
if [ $a = $b ]
then
   echo "$a = $b : a 等于 b"
else
   echo "$a = $b: a 不等于 b"
fi
if [ $a != $b ]
then
   echo "$a != $b : a 不等于 b"
else
   echo "$a != $b: a 等于 b"
fi
if [ -z $a ]
then
   echo "-z $a : 字符串长度为 0"
else
   echo "-z $a : 字符串长度不为 0"
fi
if [ -n "$a" ]
then
   echo "-n $a : 字符串长度不为 0"
else
   echo "-n $a : 字符串长度为 0"
fi
if [ $a ]
then
   echo "$a : 字符串不为空"
else
   echo "$a : 字符串为空"
fi
