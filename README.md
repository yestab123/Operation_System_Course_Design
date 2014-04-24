Operation_System_Course_Design
==============================

    Operation System Course Design Project
    Member:yestab123,shuzi,djf
    Task:File System theory and design.
    Environment:Win7,C Language,CodeBlock/VC


Usage:
-------------------------
    //*切换目录: 	cd [目录名]  //当目录名为 .. 的时候，切换到父目录
    //*创建文件：	create [文件名]
    //*创建目录：	mkdir [目录名]
    //*打开文件： 	open [文件名] [模式] //模式为r w c ，三选一，r:只读，w:只写，c:只写（覆盖以前写的内容）
    //*文件号： 	list //（打开的文件会获得一个数字，在操作read和write的时候需要使用此数字来操作） list （显示对应的文件号）
    //*读文件： 	read [文件号] [读取大小（整数）]        //文件号参见上行，读取文件到文件尾的时候需要关闭文件才能重新读取头部。
    //*写文件： 	write [文件号]  //执行后可以不断输入内容，直到输入“ # ” 来结束内容，#并不保存
    //*关闭文件：   close [文件号] //文件需要关闭之后才能用其他模式打开
    //*显示当前文件目录： ls    //显示当前文件的文件、目录
    //*##所有目录和文件的创建都只会创建在当前目录
    //*系统磁盘状态： status
    //*
    //*
    //*
    //*
    //*
    //*
    //*
    //*
    //*
