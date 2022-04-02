#ifndef TASK_H
#define TASK_H

#include <QWidget>
#include <database/dataBase.h>
#include <QCheckBox>
#include <vector>
#include <QStandardItemModel>
#include "QHBoxLayout"
#include <QTableView>
#include <QHeaderView>

namespace Ui
{
    class task;
}

class task : public QWidget, public dataBase
{
    Q_OBJECT
public:
    explicit task(QWidget *parent = nullptr);

    void initTask();
    void addTask(QDateTime dateTime, QTime time, int conditionID, int taskContentID, bool radioSelect);
    vector<vector<QString>> getTask();
    bool delTask(int taskID);
    bool isTaskActive(int taskID);
    void setTask(int taskID, bool status);

    void taskTable(int size_row);
    void taskViewer();
    // void taskTable();

    void runTask();

    bool taskStatus;
    bool radioSelect;

    ~task();

signals:
    sendTaskNum(QString);

private slots:

    void on_pushButton_setTask_clicked();

    void on_radioButton_time_clicked();

    void on_radioButton_dateTime_clicked();

    void on_pushButton_startTask_clicked();

    void on_pushButton_stopTask_clicked();

    void on_pushButton_delTask_clicked();

    void currentRowCkicked(const QModelIndex &index);

private:
    Ui::task *ui;

    // QStringList buttonNameList;
    // QString hBoxLay = "HBL";
    vector<vector<QString>> viewTask;
    int size_row;

#pragma pack(push,1)
    typedef struct
    {
        QDateTime taskDataTime;
        QString taskEvent;
    }taskStruct;
#pragma pack(pop)
};

#endif // TASK_H
