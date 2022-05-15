#ifndef NETCOM_H
#define NETCOM_H

#include <QWidget>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QThread>
#include <com/net/heartbeat.h>

namespace Ui
{
    class netCom;
}

class netCom : public QWidget
{
    Q_OBJECT

public:
    explicit netCom(QWidget *parent = nullptr);

    void initNet();

    ~netCom();

private slots:
    //---------------------
    //网络调试
    void on_btnClear_clicked();

    void onReadyRead();

    void on_btnSend_clicked();

    void on_newConnection();

    void onConnected();

    void onDisConnected();

public slots:
    //供其他函数调用的方法
    void Start();
    //建立连接
    void Stop();
    //断开连接
    QString getData();
    //获取传输数据
    void sendData(QString data);
    //发送数据
    void onDead();
    //心跳停止
    QString getNetAdd();

signals:
    void hasReadData();
    void stopListen();

private:
    Ui::netCom *ui;

    //------------------------
    QTcpServer *m_tcpServer = new QTcpServer;
    QTcpSocket *m_tcpSocket = new QTcpSocket;
    HeartBeat *heart;
    QString m_msg;
};

#endif // NETCOM_H
