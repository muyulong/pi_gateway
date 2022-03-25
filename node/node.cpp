#include "node.h"
#include "ui_node.h"

node::node(QWidget *parent) : QWidget(parent),
    ui(new Ui::node)
{
    ui->setupUi(this);

    this->initNode();
    this->initTree();
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
    ui->lb_nodeType->setText("协调器");
    ui->lb_temperature->setText("0");
    ui->lb_humidity->setText("0");
    ui->checkBox_fan->setChecked(0);
    ui->checkBox_light->setChecked(0);
    ui->checkBox_temperature->setChecked(0);
    ui->checkBox_humidity->setChecked(0);
    ui->pushButton_opLight->setDisabled(1);
    ui->pushButton_clLight->setDisabled(1);
    ui->pushButton_opFan->setDisabled(1);
    ui->pushButton_clFan->setDisabled(1);

    connect(N, SIGNAL(hasReadData()), this, SLOT(commandReceive()));

    m_nodeStatus.addr="";
    m_nodeStatus.hasLight=false;
    m_nodeStatus.hasFan=false;
    m_nodeStatus.hasTH=false;
    m_nodeStatus.hasBeep=false;
    m_nodeStatus.lightStatus=false;
    m_nodeStatus.fanStatus=false;
    m_nodeStatus.beepStatus=false;
    m_nodeStatus.temperature="无";
    m_nodeStatus.humidity="无";
    m_nodeStatus.nodeType="";

    m_nodeAddr.append("FFFF");

    this->setNode();
}

void node::on_toolButton_start_clicked()
{
    N->Start();
    emit sendTip(N->getNetAdd());
}

void node::on_toolButton_stop_clicked()
{
    N->Stop();
    emit sendTip("停止传输");
}

void node::on_toolButton_refresh_clicked()
{
    this->getNodeAddr();
}

void node::on_toolButton_init_clicked()
{
    commandSend(0,"初始化");
}

void node::setNode()
{
    this->setName();
    this->setSwitch();
    this->setFuncAvable();
    this->setTH();
}

//初始化节点树
void node::initTree()
{
    // 1，构造Model
    model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList() << "节点编号"<< "节点类型"); //设置列头
    // 2，给QTreeView应用model
    rootNode = new QStandardItem(m_nodeAddr.last());
    model->appendRow(rootNode);
    model->setItem(model->indexFromItem(rootNode).row(),1,new QStandardItem(QStringLiteral("协调器")));

    ui->treeView->setModel(model);
    ui->treeView->setAlternatingRowColors(true);
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->treeView->header()->setSectionsMovable(false);
    ui->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);   //选中行
    ui->treeView->expandAll();
}

//设置节点
void node::setName()
{
    ui->lb_nodeName->setText(m_nodeStatus.addr);
    ui->lb_nodeType->setText(m_nodeStatus.nodeType);
}

void node::setSwitch()
{
    if (m_nodeStatus.lightStatus)
    {
        ui->lb_lightStatus->setText("已开启");
    }
    else
    {
        ui->lb_lightStatus->setText("未开启");
    }
    if (m_nodeStatus.fanStatus)
    {
        ui->lb_fanStatus->setText("已开启");
    }
    else
    {
        ui->lb_fanStatus->setText("未开启");
    }
    if(m_nodeStatus.beepStatus)
    {

    }
    else
    {

    }
}

void node::setFuncAvable()
{
    if (m_nodeStatus.hasTH)
    {
        ui->checkBox_temperature->setChecked(1);
        ui->checkBox_humidity->setChecked(1);
    }
    else
    {
        ui->checkBox_temperature->setChecked(0);
        ui->checkBox_humidity->setChecked(0);
    }
    if (m_nodeStatus.hasLight)
    {
        ui->checkBox_light->setChecked(1);
        ui->pushButton_opLight->setDisabled(0);
        ui->pushButton_clLight->setDisabled(0);
    }
    else
    {
        ui->checkBox_light->setChecked(0);
        ui->pushButton_opLight->setDisabled(1);
        ui->pushButton_clLight->setDisabled(1);
    }
    if (m_nodeStatus.hasFan)
    {
        ui->checkBox_fan->setChecked(1);
        ui->pushButton_opFan->setDisabled(0);
        ui->pushButton_clFan->setDisabled(0);
    }
    else
    {
        ui->checkBox_fan->setChecked(0);
        ui->pushButton_opFan->setDisabled(1);
        ui->pushButton_clFan->setDisabled(1);
    }
    if(m_nodeStatus.hasBeep)
    {

    }
    else
    {

    }
}

void node::setTH()
{
    ui->lb_temperature->setText(m_nodeStatus.temperature);
    ui->lb_humidity->setText(m_nodeStatus.humidity);
}

//设置树
void node::setTree()
{
    endNode = new QStandardItem(m_nodeAddr.last());
    qDebug()<<m_nodeAddr.last();
    rootNode->appendRow(endNode);
    rootNode->setChild(endNode->index().row(),1,new QStandardItem(m_nodeStatus.nodeType));
    ui->treeView->update();
}

void node::getNodeAddr()
{
    commandSend(0,"状态");

}

QString str2cmd(QString str)
{
    QString cmd;
    if (str == "开灯")
    {
        cmd = "OL";
    }
    if (str == "关灯")
    {
        cmd = "CL";
    }
    if (str == "开风")
    {
        cmd = "OF";
    }
    if (str == "关风")
    {
        cmd = "CF";
    }
    if (str == "查温湿度")
    {
        cmd = "TH";
    }
    if (str == "初始化")
    {
        cmd = "IN";
    }
    if (str == "状态")
    {
        cmd = "S-";
    }
    return cmd;
}

int parityCheck(QString nMsg)
{
    //QByteArray byte_nMsg = nMsg.toLatin1();
    //char* chMsg = byte_nMsg.data();
    //for (int i = 0; i < 7; i++)
    //{
    //qDebug()  << (bitMask ^ chMsg[i] ? 1 : 0);
    //chMsg[i] = chMsg[i] << 1;
    //    qDebug()  << (chMsg[i]^chMsg[i+1]);
    //}
    return 1;
}

void node::commandSend(int nodeID, QString msg)
{
    QString node_add = m_nodeAddr.at(nodeID);
    QString cmd_str = node_add + "#" + str2cmd(msg);
    QString parityNum = QString::number(parityCheck(cmd_str));
    cmd_str = cmd_str + parityNum;
    N->sendData(cmd_str);
}

void node::nodeSetting(nodeMsg m_Node)
{
    QString addr = m_Node.nodeAddr;
    m_nodeStatus.addr = addr;
    if(addr=="FFFF")
    {
        m_nodeStatus.nodeType = "协调器";
        m_nodeStatus.hasBeep = true;
        m_nodeStatus.addr="FFFF";
        m_nodeStatus.hasLight=false;
        m_nodeStatus.hasFan=false;
        m_nodeStatus.hasTH=false;
        m_nodeStatus.lightStatus=false;
        m_nodeStatus.fanStatus=false;
        m_nodeStatus.beepStatus=false;
        m_nodeStatus.temperature="无";
        m_nodeStatus.humidity="无";
    }
    else
    {
        m_nodeStatus.nodeType = "终端";
        m_nodeStatus.hasBeep = false;
        if(m_Node.cmd[0]=='O')
        {
            if(m_Node.cmd[1]=='L')
            {
                m_Node.data[3]=='1' ? m_nodeStatus.lightStatus = true : m_nodeStatus.lightStatus = false;
            }
            if(m_Node.cmd[1]=='F')
            {
                m_Node.data[3]=='1' ? m_nodeStatus.fanStatus = true : m_nodeStatus.fanStatus = false;
            }
        }
        if(m_Node.cmd[0]=='C')
        {
            if(m_Node.cmd[1]=='L')
            {
                m_Node.data[3]=='1' ? m_nodeStatus.lightStatus = false : m_nodeStatus.lightStatus = true;
            }
            if(m_Node.cmd[1]=='F')
            {
                m_Node.data[3]=='1' ? m_nodeStatus.fanStatus = false : m_nodeStatus.fanStatus = true;
            }
        }
        if(m_Node.cmd[0]=='I'&&m_Node.cmd[1]=='N')
        {
            m_Node.data[0]=='1' ? m_nodeStatus.lightStatus = true : m_nodeStatus.lightStatus = false;
            m_Node.data[1]=='1' ? m_nodeStatus.fanStatus = true : m_nodeStatus.fanStatus = false;
        }
        if(m_Node.cmd[0]=='T'&&m_Node.cmd[1]=='H')
        {
            m_nodeStatus.temperature = QString(m_Node.data[0]) + QString(m_Node.data[1]);
            m_nodeStatus.humidity = QString(m_Node.data[2]) + QString(m_Node.data[3]);
        }
        if(m_Node.cmd[0]=='S'&&m_Node.cmd[1]=='-')
        {
            if(!m_nodeAddr.contains(addr))
            {
                m_nodeAddr.append(addr);
            }
            m_Node.data[0]=='1' ? m_nodeStatus.hasLight = true : m_nodeStatus.hasLight = false;
            m_Node.data[1]=='1' ? m_nodeStatus.hasFan = true : m_nodeStatus.hasFan = false;
            m_Node.data[2]=='1' ? m_nodeStatus.hasTH = true : m_nodeStatus.hasTH = false;
            m_Node.data[3]=='1' ? m_nodeStatus.hasBeep = true : m_nodeStatus.hasBeep = false;
        }
    }
}

void node::commandReceive()
{
    nodeMsg m_nodeMsg;
    //QString msg = rcvMsg.dequeue();
    QString msg =  N->getData();
    qDebug()<<msg;
    if(msg.mid(0, 4)=="0000")
    {
        m_nodeMsg.nodeAddr.append("FFFF");
    }
    else
    {
        m_nodeMsg.nodeAddr.append(msg.mid(0, 4));    //节点地址
    }
    m_nodeMsg.cmd[0] = msg.at(5);     //命令位
    m_nodeMsg.cmd[1] = msg.at(6);     //命令位
    m_nodeMsg.data[0] = msg.at(7);    //数据位
    m_nodeMsg.data[1] = msg.at(8);    //数据位
    m_nodeMsg.data[2] = msg.at(9);    //数据位
    m_nodeMsg.data[3] = msg.at(10);    //数据位
    QString parity_data = msg.at(11); //校验位
    nodeSetting(m_nodeMsg);
    this->setNode();
    this->setTree();
}
