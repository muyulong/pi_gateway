#ifndef NODE_H
#define NODE_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
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
    void setName(QString,QString);
    void setSwitch(bool,bool);
    void setFuncAvable(bool,bool,bool);
    void setTemp(float);

    //设置树
    void setTree();


private:
    Ui::node *ui;
    bool lightStatus;
    bool fanStatus;
};

#endif // NODE_H
