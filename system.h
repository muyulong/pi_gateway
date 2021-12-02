#ifndef SYSTEM_H
#define SYSTEM_H

#include "log.h"

class system
{
public:
    system();
    ~system();

    void initSystem();
    void initDevices();
    void checkTasks();
    //void getDevicesInfo();
    //void getOperableDevices();
    void commandEncode(QString msg);
    //void commandDecode(未知类型);
    //void commandSend(未知类型);
    //void commandReceive();




    private:
    class log L;

};




#endif // SYSTEM_H
