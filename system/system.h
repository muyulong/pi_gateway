#ifndef SYSTEM_H
#define SYSTEM_H

#include "log/log.h"

class system
{
public:
    system();
    ~system();

    void initSystem();
    //初始化非主页面的系统基本功能
    void initDevices();
    //初始化节点数据
    void checkTasks();
    //检查待执行计划任务
    void getDevicesInfo();
    //根据收到的信息，设置节点数据
    //void getOperableDevices();
    void commandEncode(QString msg);
    //void commandDecode(未知类型);
    //void commandSend(未知类型);
    //void commandReceive();




    private:
    class log L;

};




#endif // SYSTEM_H
