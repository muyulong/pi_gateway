#!/bin/sh

if [ $# == 1 ];                        #判断参数个数
then                                #若参数正确执行代码
    git add .
    message=$1
    git commit -m "${message}"
    git push origin master
else                                #参数错误则输出Usage
    echo '[usage]'
    echo 'gitPush [COMMIT MESSAGE]'
fi