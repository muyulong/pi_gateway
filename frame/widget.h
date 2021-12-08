#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<database/dataBase.h>
#include<QCheckBox>
#include<frame/log.h>
#include<task/task.h>
#include <QHostInfo>
#include <QTcpServer>
#include <QTcpSocket>


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

    void on_pushButton_switch2Network_clicked();
    //连接建立按钮
    //---------------------
    //网络调试
    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnClear_clicked();

    void on_newConnection();

    void onConnected();

    void onDisConnected();

    void onStateChanged(QAbstractSocket::SocketState socketState);

    void onReadyRead();

    void on_btnSend_clicked();


signals:
    void setBtnClicked();

private:
    QStringList buttonNameList;
    QString hBoxLay = "HBL";
    vector<vector<QString> > viewTask;
    int size_row;
    Ui::Widget *ui;
    void closeEvent(QCloseEvent *event);
     bool w_size;

    //------------------------
    QTcpServer *m_tcpServer = nullptr;
    QTcpSocket *m_tcpSocket = nullptr;
};
#endif // WIDGET_H
