## 养殖厂无线网络系统网关的设计与实现

*muyulong*

*Qt&C++*

*run at a Raspberry Pi 3B+ in Raspbian*

*still developing...*

### 项目简介

~~蒻鸡带学生的毕业设计~~

实现对无线节点的远程监测和控制。

实现对计划任务的增、删、改、查和定时执行。

实现根据下位机传送来的数据动态生成控制面板，能够时监测和操作节点。

建立系统日志数据库，温度日志数据库，生成图表。

### 运行环境

得益于Qt支持跨平台的强大功能，本项目能够在安装了Raspbian系统的Raspberry Pi 3B+上运行。

### 目录结构

**com**

网络通信和串口通信及界面

**dataBase**

数据库

**log**

日志功能及日志界面

**mainfrm**

主界面

**node**

节点功能及界面

**task**

计划任务功能及界面

**user**

用户注册和登录

**welcome**

欢迎界面

**main.cpp**

主函数入口

**qss**

qss样式表

### ToDoList

- [x] 系统设置页面task任务表从mainFrm剥离，有独立的.ui文件
- [x] task任务表界面完善
- [x] 系统设置页面网络通讯功能从mainFrm剥离，有独立的.ui文件
- [x] 完善网络通讯功能
- [x] 系统设置页面串口通讯功能从mainFrm剥离，有独立的.ui文件
- [x] 完善串口通讯功能
- [x] mainFrm主界面根据网络或串口通讯内容动态生成节点
- [x] 新建温度表页面，并关联到mainFrm中
- [x] 温度表页面根据数据库中的历史温度数据，动态生成图表
- [x] 登录界面完善
- [x] 注册界面完善
- [x] 欢迎界面完善
- [ ] tips小贴士功能完善
- [ ] 当前在线节点功能完善
- [ ] 运行中计划任务功能完善
- [ ] 关于按钮功能完善
- [ ] 所有页面qss的编写
- [ ] 其他若干功能和细节优化

### 声明

本人保证不对项目中的代码负任何责任，任何个人，组织或团体等如因为本项目中的任何代码出现任何影响，均与本人无关。

### 协议

[WTFPL](https://anak10thn.github.io/WTFPL/)

```
            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
```

![](http://www.wtfpl.net/wp-content/uploads/2012/12/wtfpl-badge-1.png)

