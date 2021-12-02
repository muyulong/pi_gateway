#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<dataBase.h>
#include<QCheckBox>
#include<log.h>
#include<task.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void getLoginUser(QString user);
    void taskTable(int size_row);
    void taskViewer();
    QString usr;
    bool radioSelect;

    class log L;
    class task T;

    ~Widget();


private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_viewLog_clicked();

    void on_pushButton_setTask_clicked();

    void on_radioButton_time_clicked();

    void on_radioButton_dateTime_clicked();

    void on_pushButton_startTask_clicked();

    void on_pushButton_stopTask_clicked();

    void on_pushButton_delTask_clicked();

signals:
    void setBtnClicked();

private:
    QStringList buttonNameList;
    QString hBoxLay = "HBL";
    vector<vector<QString> > viewTask;
    int size_row;
    Ui::Widget *ui;
    void closeEvent(QCloseEvent *event);
};
#endif // WIDGET_H
