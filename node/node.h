#ifndef NODE_H
#define NODE_H

#include <QWidget>
#include <QStandardItemModel>
#include "log/log.h"
#include "com/net/netcom.h"
#include <QQueue>
#include <QVector>
#include <QDebug>
#include <QMap>

namespace Ui
{
class node;
}

class nodeState
{
public:
    nodeState();

    ~nodeState();

    void initNodeState(QString);
    QString getAddr();
    QString getNodeType();
    bool getLightStatus();
    bool getFanStatus();
    bool getBeepStatus();
    QString getTemperature();
    QString getHumidity();

    bool hasLight();
    bool hasFan();
    bool hasTH();
    bool hasBeep();

    void setAddr(QString);
    void setNodeType(QString);
    void setLightStatus(bool);
    void setFanStatus(bool);
    void setBeepStatus(bool);
    void setTemperature(QString);
    void setHumidity(QString);

    void setExUnit(bool,bool,bool,bool);
private:
    QString addr;
    QString nodeType;
    bool hasLightUnit;
    bool hasFanUnit;
    bool hasTHUnit;
    bool hasBeepUnit;
    bool lightStatus;
    bool fanStatus;
    bool beepStatus;
    QString temperature;
    QString humidity;
};

class node : public QWidget , nodeState
{
    Q_OBJECT

public:
    explicit node(QWidget *parent = nullptr);
    ~node();

#pragma pack(push,1)
    typedef struct
    {
        QString addr;
        QChar cmd[4];
        QChar data[4];
    }nodeMsg;
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

    //根据收到的信息，设置节点数据

    void nodeSetting(nodeMsg);

    void getNodeMsg();

    bool checkTemp(int);

    bool checkHumi(int);

signals:
    void sendTip(QString);
    void sendTH(qint64,int,int);
    void sendOnline(QString);
    void netStart();
    void netStop();
    QString getNetAdd();
    void sendData(QString);
    QString getData();
    void addLog(QString, int, QString);

public slots:
    void commandReceive();
    void commandSend(QString, QString);
    bool isOverTemp();
    bool isOverHumi();

private slots:
    //设置树
    void setTree();
    //--------------------
    void treeItemCkicked(const QModelIndex &index);

    void on_toolButton_start_clicked();

    void on_toolButton_stop_clicked();

    void on_toolButton_refresh_clicked();

    void on_toolButton_init_clicked();

    void on_pushButton_opLight_clicked();

    void on_pushButton_clLight_clicked();

    void on_pushButton_opFan_clicked();

    void on_pushButton_clFan_clicked();

private:
    Ui::node *ui;

    //-------------
    QStringList m_nodeAddrList;
    //用于存储节点地址
    QStandardItemModel *model;
    QStandardItem *rootNode;
    QStandardItem *endNode;
    //生成树
    QQueue<nodeState> m_nodeStateQueue;
    //储存每次节点发送来的消息状态
    bool isRootNodeSet;
    bool tempOver = false;
    bool humiOver = false;
};

#endif // NODE_H
