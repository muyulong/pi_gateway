#ifndef TASK_H
#define TASK_H

#include <QWidget>
#include <database/dataBase.h>
#include <QCheckBox>
#include <QVector>
#include <QStandardItemModel>
#include "QHBoxLayout"
#include <QTableView>
#include <QHeaderView>
#include <node/node.h>

namespace Ui
{
class task;
}

#pragma pack(push,1)
typedef struct
{
    QString taskDataTime;
    QString taskEvent;
}taskStruct;
#pragma pack(pop)

class task : public QWidget, public dataBase
{
    Q_OBJECT
public:
    explicit task(QWidget *parent = nullptr);

    void initTask();
    void addTask(QDateTime dateTime, QTime time, int conditionID, int taskContentID, bool radioSelect);
    QVector<QVector<QString>> getTask();
    bool delTask(int taskID);
    bool isTaskActive(int taskID);
    void setTask(int taskID, bool status);

    void taskTable(int size_row);
    void taskViewer();
    // void taskTable();

    void runTask(QString);

    void getTask2Run();

    bool taskStatus;
    bool radioSelect;

    QVector<taskStruct> m_taskStructVec;

    ~task();

signals:
    void sendTaskCmd(QString nodeAddr, QString msg);
    bool isOverTemp();
    bool isOverHumi();
    void addLog(QString, int, QString);

public slots:
    QString getRunTaskNum();

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
    QVector<QVector<QString>> viewTask;
    int size_row;
    int runTaskNum;
};

#endif // TASK_H
