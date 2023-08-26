#!/bin/bash

:<<EOF
	Shell 输入/输出重定向：
		默认的标注输入：终端
		默认的标准输出：终端
	文件描述符：
		标准输入（STDIN） 0
		标准输出 （STDOUT） 1
		标准错误输出（STDERR）2
	
	输出重定向至file : command > file
	输入重定向至file : command < file  =====> 把 file的内容作为标准输入 
	输出以追加方式重定向至file : command >> file
	将文件描述符为n的输出 重定向到file : n > file
					     n >> file
	
	将输出文件m和n合并:
		n >& m
	将输入文件m和n合并：
		n <& m

	<< tag : 将开始标记tag和结束标记tag之间的内容作为输入
	
EOF




echo `who >> myfile` 

echo `wc -l < myfile > outfile`


