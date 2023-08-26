#!/bin/bash

:<<EOF
	shell中函数的定义:
		[ function ] funname()
		{
		
		}

	函数调用：funname

	获取函数返回值： $?

	函数参数 : 传递方式 同 shell_strudy_transferParam 
		传递实参：
			funname 1 2 3 4 5 6 7
		获取形参:
			${1} .... ${n}
EOF


function demoFun()
{
	echo "这是我的第一个Shell 函数!"
}

echo "------函数开始执行！！------"
demoFun #函数调用
echo "------函数执行完毕！！------"


funWithReturn()
{
    echo "这个函数会对输入的两个数字进行相加运算..."
    echo "输入第一个数字: "
    read aNum
    echo "输入第二个数字: "
    read anotherNum
    echo "两个数字分别为 $aNum 和 $anotherNum !"
    return $(( $aNum + $anotherNum ))
}
funWithReturn
echo "输入的两个数字之和为 $? !"



function funWithParam()
{
    echo "第一个参数为 ${1} !"
    echo "第二个参数为 ${2} !"
    echo "第十个参数为 ${10} !"
    echo "第十一个参数为 ${11} !"
    echo "参数总数有 ${#} 个!"
    echo "作为一个字符串输出所有参数 ${*} !"
}

funWithParam 1 2 3 4 5 6 7 8 9 34 73 !
