#ifndef NETCOM_H
#define NETCOM_H

#include <QWidget>
#include <QHostInfo>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
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
    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnClear_clicked();

    void on_newConnection();

    void onConnected();

    void onDisConnected();

    void onStateChanged(QAbstractSocket::SocketState socketState);

    void onReadyRead();

    void on_btnSend_clicked();

private:
    Ui::netCom *ui;

    //------------------------
    QTcpServer *m_tcpServer = nullptr;
    QTcpSocket *m_tcpSocket = nullptr;
};

#endif // NETCOM_H
