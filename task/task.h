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
    void addTask(QDateTime dateTime, QTime time, int taskContentID, bool radioSelect);
    vector<vector<QString>> getTask();
    bool delTask(int taskID);
    bool isTaskActive(int taskID);
    void setTask(int taskID, bool status);

    void taskTable(int size_row);
    void taskViewer();
    // void taskTable();

    bool taskStatus;
    bool radioSelect;

    ~task();

private slots:

    void on_pushButton_setTask_clicked();

    void on_radioButton_time_clicked();

    void on_radioButton_dateTime_clicked();

    void on_pushButton_startTask_clicked();

    void on_pushButton_stopTask_clicked();

    void on_pushButton_delTask_clicked();

private:
    Ui::task *ui;

    // QStringList buttonNameList;
    // QString hBoxLay = "HBL";
    vector<vector<QString>> viewTask;
    int size_row;
};

#endif // TASK_H
