#!/bin/bash

:<< EOF
	bash支持一维数组（不支持多维数组），并没有限定数组大小
	下标由0开始编号
EOF

#定义数组 数组名={值1 值2 ... 值n}
array_name=(value0 value1 value2 value3)

array_name1=(value0 
	    value1 
	    value2 
	    value3)

array_name2[0]=value0
array_name2[1]=value1
array_name2[2]=value2

#读取数组
echo ${array_name[0]} 
echo ${array_name1[3]} 
echo ${array_name2[2]}

#获取数组中所有元素
echo ${array_name[@]}


#获取数组长度（#数组名）
length=${#array_name[0]} #获取数组第一个元素的长度
length1=${#array_name[@]} #或 ${#array_name[*]}
echo "单个数组元素的长度: ${length}"
echo "数组长度: ${length1}"

#关联数组(键值对)
:<<EOF
	关联数组：可以使用i"任意字符串或整数"作为下标来访问数组元素
EOF

declare -A site=(
	["google"]="www.google.com" 
	["runoob"]="www.runoob.com" 
	["taobao"]="www.taobao.com"
)

declare -A site1;
site1["google"]="www.google.com" 
site1["runoob"]="www.runoob.com" 
site1["taobao"]="www.taobao.com"

echo ${site["google"]}
echo ${site1["google"]}
echo ${site[@]}
echo ${#site[@]}
echo "获取数组中所有的键：${!site[@]}"



