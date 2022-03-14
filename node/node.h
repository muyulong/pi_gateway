#ifndef NODE_H
#define NODE_H

#include <QWidget>
#include <QStandardItemModel>
#include "log/log.h"
#include "com/net/netcom.h"

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

    //初始化节点
    void initNode();

    //初始化节点树
    void initTree();

    //设置节点
    void setName(QString, QString);
    void setSwitch(bool, bool);
    void setFuncAvable(bool, bool, bool);
    void setTemp(float);

    //设置树
    void setTree();

    //--------------------

    void getDevicesInfo();
    //根据收到的信息，设置节点数据

    void commandSend(QString, int, int);

    void commandReceive(QString);

    //--------------------

private:
    Ui::node *ui;
    bool lightStatus;
    bool fanStatus;

    //-------------
    class log L;
    netCom N;
    vector<vector<QString>> dvInfo;
};

#endif // NODE_H
