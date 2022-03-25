#ifndef NODE_H
#define NODE_H

#include <QWidget>
#include <QStandardItemModel>
#include "log/log.h"
#include "com/net/netcom.h"
#include <QQueue>
#include <QVector>
#include <QDebug>

namespace Ui
{
class node;
}

class node : public QWidget
{
    Q_OBJECT

public:
    explicit node(QWidget *parent = nullptr);
    ~node();

#pragma pack(push,1)
    typedef struct
    {
        QString nodeAddr;
        QChar cmd[4];
        QChar data[4];
    }nodeMsg;
#pragma pack(pop)

#pragma pack(push,1)
    typedef struct
    {
        QString addr;
        QString nodeType;
        bool hasLight;
        bool hasFan;
        bool hasTH;
        bool hasBeep;
        bool lightStatus;
        bool fanStatus;
        bool beepStatus;
        QString temperature;
        QString humidity;
    }nodeStatus;
#pragma pack(pop)

    //初始化节点
    void initNode();

    //初始化节点树
    void initTree();

    //设置控件
    void setName();
    void setSwitch();
    void setFuncAvable();
    void setTH();

    //设置节点
    void setNode();

    //获取节点地址
    void getNodeAddr();
    //根据收到的信息，设置节点数据

    void nodeSetting(nodeMsg);

    void commandSend(int,QString);

    void getNodeMsg();

signals:
    void sendTip(QString);

private slots:
    void commandReceive();
    //设置树
    void setTree();
    //--------------------

    void on_toolButton_start_clicked();

    void on_toolButton_stop_clicked();

    void on_toolButton_refresh_clicked();

    void on_toolButton_init_clicked();

private:
    Ui::node *ui;

    //-------------
    class log L;
    netCom *N = new netCom;
    QStringList m_nodeAddr;
    //用于存储节点地址
    QStandardItemModel *model;
    QStandardItem* rootNode;
    QStandardItem* endNode;
    //生成树
    QQueue<QString> rcvMsg;
    //用于存储接收到的消息队列
    nodeStatus m_nodeStatus;
    //根据节点信息记录状态
};

#endif // NODE_H
