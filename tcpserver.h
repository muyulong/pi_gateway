//#ifndef TCPSOCKET_H
//#define TCPSOCKET_H

//#include <QTcpSocket>
//#include <QObject>
//#include <string.h>
//#include <QtNetwork>

//class TcpSocket:public QTcpSocket
//{
//    Q_OBJECT
//public:
//    TcpSocket();

//signals:
//    void updateClients(QString,int);
//    void disconnected(int);
//protected slots:
//    void dataReceived();
//    void slotDisconnected();
//};

//#endif // TCPSOCKET_H

////-----------------------------------------

//#ifndef SERVER_H
//#define SERVER_H

//#include  <QTcpServer>

//class Server : public QTcpServer
//{
//    Q_OBJECT
//public:
//    Server(int port=0);
//    QList <TcpSocket*> tcpSocketList;//用于保存各个客户端的TCP连接

//signals:
//    void updateServer(QString,int);//用于发送给界面类更新界面

//public slots:
//    void slotUpdateClients(QString,int);//用于将消息发给每个客户端
//    void slotDisconnected(int); //用于移除断开连接的客户端socket

//protected:
//    void incomingConnection(int socketDescriptor);//虚函数，处理试图连接的客户端
//    //将其连接句柄保存用于转发消息。
//};

//#endif // SERVER_H


////-----------------------------------------


//#ifndef TCPSERVER_H
//#define TCPSERVER_H

//class tcpServer:
//{
//public:
//     explicit tcpServer();
//    ~tcpServer();
//    int port;
//    Server *server;

//private:

//public slots:
//void slotUpdateServer(QString msg, int length);
////由到消息后更新界面. msg为收到的消息，length为其长度

//private slots:
//    //void on_pushButtonCreate_clicked();
//};

//#endif // TCPSERVER_H
