#include "node.h"
#include "ui_node.h"

node::node(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::node)
{
    ui->setupUi(this);

    this->initTree();
    this->initNode();
}

node::~node()
{
    delete ui;
}

/*
 * 节点类需要的功能
 * 接收传过来的值
 * 获取节点地址，设置对应控件的值
 * 获取节点类型，根据类型设置启用或禁用风扇或者灯泡
 * 获取节点温度，设置温度控件的值
*/

//初始化节点
void node::initNode()
{
    ui->lb_nodeName->setText("0000");
    ui->lb_parNodeName->setText("ffff");
    ui->lb_temp->setText("0");
    ui->checkBox_fan->setChecked(0);
    ui->checkBox_light->setChecked(0);
    ui->checkBox_temp->setChecked(0);
    ui->checkBox_fan->setCheckable(0);
    ui->checkBox_light->setCheckable(0);
    ui->checkBox_temp->setCheckable(0);
    ui->pushButton_opLight->setDisabled(1);
    ui->pushButton_clLight->setDisabled(1);
    ui->pushButton_opFan->setDisabled(1);
    ui->pushButton_clFan->setDisabled(1);
}

//初始化节点树
void node::initTree()
{
    //1，构造Model
    QStandardItemModel* model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList()<<"节点编号"<< "节点类型");     //设置列头
    //2，给QTreeView应用model
    ui->treeView->setModel(model);
}

//设置节点
void node::setName(QString nodeName,QString parNodeName)
{
    ui->lb_nodeName->setText(nodeName);
    ui->lb_parNodeName->setText(parNodeName);
}

void node::setSwitch(bool lightStatus,bool fanStatus)
{
    if(lightStatus)
    {
        ui->lb_lightStatus->setText("已开启");
    }
    if(!lightStatus)
    {
        ui->lb_lightStatus->setText("未开启");
    }
    if(fanStatus)
    {
        ui->lb_fanStatus->setText("已开启");
    }
    if(!fanStatus)
    {
        ui->lb_fanStatus->setText("未开启");
    }
}

void node::setFuncAvable(bool tp,bool lt,bool fn)
{
    if(tp)
    {
        ui->checkBox_temp->setChecked(1);
    }
    if(!tp)
    {
        ui->checkBox_temp->setChecked(0);
    }
    if(lt)
    {
        ui->checkBox_light->setChecked(1);
        ui->pushButton_opLight->setDisabled(0);
        ui->pushButton_clLight->setDisabled(0);
    }
    if(!lt)
    {
        ui->checkBox_light->setChecked(0);
        ui->pushButton_opLight->setDisabled(1);
        ui->pushButton_clLight->setDisabled(1);
    }
    if(fn)
    {
        ui->checkBox_fan->setChecked(1);
        ui->pushButton_opFan->setDisabled(0);
        ui->pushButton_clFan->setDisabled(0);
    }
    if(!fn)
    {
        ui->checkBox_fan->setChecked(0);
        ui->pushButton_opFan->setDisabled(1);
        ui->pushButton_clFan->setDisabled(1);
    }
}

void node::setTemp(float temp)
{
    QString temp_str = QString("%1").arg(temp);
    ui->lb_temp->setText(temp_str);
}

//设置树
void node::setTree()
{

}

