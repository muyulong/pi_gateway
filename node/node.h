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
    struct nodeMsg
    {
        QVector<QString> nodeAddr;
        QString cmd;
        QString data;
    };
    struct nodeStatus
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
        int temperature;
        int humidity;
    };
    //初始化节点
    void initNode();

    //初始化节点树
    void initTree();

    //设置节点
    void setName();
    void setSwitch();
    void setFuncAvable();
    void setTH();

    //设置树
    void setTree();

    //--------------------
    void setNode();

    void getNodeAddr();
    //根据收到的信息，设置节点数据

    void nodeSetting(nodeMsg);

    void commandSend(int,QString);

    void getNodeMsg();
public slots:
    void commandReceive();

    //--------------------

private:
    Ui::node *ui;

    //-------------
    class log L;
    netCom *N = new netCom;
    QQueue<QString> rcvMsg;
    nodeMsg m_nodeMsg;
    nodeStatus m_nodeStatus;
};

#endif // NODE_H
