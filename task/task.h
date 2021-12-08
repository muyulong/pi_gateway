#ifndef TASK_H
#define TASK_H

#include<database/dataBase.h>

class task :public dataBase,public QWidget
{
public:
    task();


    void addTask(QDateTime dateTime,QTime time,int taskContentID,bool radioSelect);
    vector<vector<QString>> getTask();
    bool delTask(int taskID);
    bool isTaskActive(int taskID);
    void setTask(int taskID,bool status);
    //void taskTable();

    bool taskStatus;

};

#endif // TASK_H
