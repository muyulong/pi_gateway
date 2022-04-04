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
    ui->lb_nodeName->setText("FFFF");
    ui->lb_nodeType->setText("无");
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

    connect(ui->treeView,&QTreeView::doubleClicked,this,&node::treeItemCkicked);

    isRootNodeSet = false;
}

void node::on_toolButton_start_clicked()
{
    emit netStart();
    emit sendTip(getNetAdd());
}

void node::on_toolButton_stop_clicked()
{
    emit netStart();
    emit sendTip("停止传输");
}

void node::on_toolButton_refresh_clicked()
{
    commandSend(ui->lb_nodeName->text(),"状态");
    QEventLoop eventloop;
    QTimer::singleShot(100, &eventloop, SLOT(quit()));
    eventloop.exec();
    commandSend(ui->lb_nodeName->text(),"查温湿度");
}

void node::on_toolButton_init_clicked()
{
    commandSend(ui->lb_nodeName->text(),"初始化");
}

void node::on_pushButton_opLight_clicked()
{
    commandSend(ui->lb_nodeName->text(),"开灯");
}

void node::on_pushButton_clLight_clicked()
{
    commandSend(ui->lb_nodeName->text(),"关灯");
}

void node::on_pushButton_opFan_clicked()
{
    commandSend(ui->lb_nodeName->text(),"开风");
}

void node::on_pushButton_clFan_clicked()
{
    commandSend(ui->lb_nodeName->text(),"关风");
}

void node::treeItemCkicked(const QModelIndex &index)
{
    QString selectedRowTxt = ui->treeView->model()->itemData(index).values()[0].toString();
    if(selectedRowTxt == "终端" || selectedRowTxt == "协调器")
    {
        selectedRowTxt = "FFFF";
    }
    commandSend(selectedRowTxt,"状态");
    QEventLoop eventloop;
    QTimer::singleShot(100, &eventloop, SLOT(quit()));
    eventloop.exec();
    commandSend(selectedRowTxt,"查温湿度");
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
    ui->treeView->setModel(model);
    //ui->treeView->setAlternatingRowColors(true);
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->treeView->header()->setSectionsMovable(false);
    ui->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);   //选中行
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->treeView->expandAll();
}

//设置节点
void node::setName()
{
    ui->lb_nodeName->setText(m_nodeStateQueue.first().getAddr());
    ui->lb_nodeType->setText(m_nodeStateQueue.first().getNodeType());
}

void node::setSwitch()
{
    if (m_nodeStateQueue.first().getLightStatus())
    {
        ui->lb_lightStatus->setText("已开启");
    }
    else
    {
        ui->lb_lightStatus->setText("未开启");
    }
    if (m_nodeStateQueue.first().getFanStatus())
    {
        ui->lb_fanStatus->setText("已开启");
    }
    else
    {
        ui->lb_fanStatus->setText("未开启");
    }
    if(m_nodeStateQueue.first().getBeepStatus())
    {

    }
    else
    {

    }
}

void node::setFuncAvable()
{
    if (m_nodeStateQueue.first().hasTH())
    {
        ui->checkBox_temperature->setChecked(1);
        ui->checkBox_humidity->setChecked(1);
    }
    else
    {
        ui->checkBox_temperature->setChecked(0);
        ui->checkBox_humidity->setChecked(0);
    }
    if (m_nodeStateQueue.first().hasLight())
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
    if (m_nodeStateQueue.first().hasFan())
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
    if(m_nodeStateQueue.first().hasBeep())
    {

    }
    else
    {

    }
}

void node::setTH()
{
    ui->lb_temperature->setText(m_nodeStateQueue.first().getTemperature());
    ui->lb_humidity->setText(m_nodeStateQueue.first().getHumidity());
}

//设置树
void node::setTree()
{
    if(m_nodeAddrList.first() == "FFFF")
    {
        if(isRootNodeSet == false)
        {
            rootNode = new QStandardItem(m_nodeAddrList.first());
            model->appendRow(rootNode);
            model->setItem(model->indexFromItem(rootNode).row(),1,new QStandardItem(m_nodeStateQueue.last().getNodeType()));
            ui->treeView->setCurrentIndex(rootNode->index());
            isRootNodeSet = true;
        }
        if(!m_nodeAddrList.contains(m_nodeStateQueue.last().getAddr()))
        {
            m_nodeAddrList.append(m_nodeStateQueue.last().getAddr());
            endNode = new QStandardItem(m_nodeAddrList.last());
            rootNode->appendRow(endNode);
            rootNode->setChild(endNode->index().row(),1,new QStandardItem(m_nodeStateQueue.last().getNodeType()));
            ui->treeView->setCurrentIndex(endNode->index());
        }
        this->setNode();
        m_nodeStateQueue.dequeue();
        ui->treeView->update();
        ui->treeView->expandAll();
    }
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
        cmd = "QA";
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
    if(!nMsg.isEmpty())
    {
        return 1;
    }
}

bool node::checkTemp(int temp)
{
    if(temp>30)
    {
        tempOver = true;
    }
    else
    {
        tempOver = false;
    }
    return tempOver;
}

bool node::checkHumi(int humi)
{
    if(humi>70)
    {
        humiOver = true;
    }
    else
    {
        humiOver = false;
    }
    return humiOver;
}

bool node::isOverTemp()
{
    return tempOver;
}

bool node::isOverHumi()
{
    return humiOver;
}

void node::commandSend(QString nodeAddr, QString msg)
{
    if(nodeAddr == "0000")
    {
        nodeAddr = "FFFF";
    }
    QString cmd_str = nodeAddr + "#" + str2cmd(msg);
    //QString parityNum = QString::number(parityCheck(cmd_str));
    QString parityNum = "1";
    cmd_str = cmd_str + parityNum;
    sendData(cmd_str);
}

void node::nodeSetting(nodeMsg m_Node)
{
    if(m_Node.cmd[0]=='T'&&m_Node.cmd[1]=='H')
    {
        qint64 time = QDateTime::currentDateTime().toMSecsSinceEpoch();
        int temp = QString(m_Node.data[0]).toInt()*10 + QString(m_Node.data[1]).toInt();
        int humi = QString(m_Node.data[2]).toInt()*10 + QString(m_Node.data[3]).toInt();
        emit sendTH(time,temp,humi);
        if(checkTemp(temp))
        {
            addLog("温度监控",4 , " "+QString::number(temp)+"℃");
        }
        if(checkHumi(humi))
        {
            addLog("湿度监控",5,  " "+QString::number(temp)+"%");
        }
    }
    else
    {
        nodeState m_nodeState;
        if(m_Node.addr=="FFFF")
        {
            m_nodeState.initNodeState("协调器");
            m_nodeState.setAddr(m_Node.addr);
            if(!m_nodeAddrList.contains(m_Node.addr))
            {
                m_nodeAddrList.append(m_Node.addr);
            }
        }
        else
        {
            m_nodeState.initNodeState("终端");
            m_nodeState.setAddr(m_Node.addr);
            if(m_Node.cmd[0]=='O')
            {
                if(m_Node.cmd[1]=='L')
                {
                    m_Node.data[3]=='1' ? m_nodeState.setLightStatus(true) : m_nodeState.setLightStatus(false);
                }
                if(m_Node.cmd[1]=='F')
                {
                    m_Node.data[3]=='1' ? m_nodeState.setFanStatus(true) : m_nodeState.setFanStatus(false);
                }
            }
            if(m_Node.cmd[0]=='C')
            {
                if(m_Node.cmd[1]=='L')
                {
                    m_Node.data[3]=='1' ? m_nodeState.setLightStatus(false) : m_nodeState.setLightStatus(true);
                }
                if(m_Node.cmd[1]=='F')
                {
                    m_Node.data[3]=='1' ? m_nodeState.setFanStatus(false) : m_nodeState.setFanStatus(true);
                }
            }
            if(m_Node.cmd[0]=='I'&&m_Node.cmd[1]=='N')
            {
                m_Node.data[0]=='1' ? m_nodeState.setLightStatus(true) : m_nodeState.setLightStatus(false);
                m_Node.data[1]=='1' ? m_nodeState.setFanStatus(true) : m_nodeState.setFanStatus(false);
            }
            if(m_Node.cmd[0]=='Q'&&m_Node.cmd[1]=='A')
            {
                m_nodeState.setTemperature(QString(m_Node.data[0]) + QString(m_Node.data[1]));
                m_nodeState.setHumidity(QString(m_Node.data[2]) + QString(m_Node.data[3]));
            }
            if(m_Node.cmd[0]=='S'&&m_Node.cmd[1]=='-')
            {
                bool hasLight, hasFan, hasBeep, hasTH;
                m_Node.data[0]=='1' ? hasLight = true : hasLight = false;
                m_Node.data[1]=='1' ? hasFan = true : hasFan = false;
                m_Node.data[2]=='1' ? hasBeep = true : hasBeep = false;
                m_Node.data[3]=='1' ? hasTH = true : hasTH = false;
                m_nodeState.setExUnit(hasLight,hasFan,hasBeep,hasTH);
            }
        }
        m_nodeStateQueue.enqueue(m_nodeState);
        this->setTree();
    }
}

void node::commandReceive()
{
    nodeMsg m_nodeMsg;
    //QString msg = rcvMsg.dequeue();
    QString msg = getData();
    if(msg.at(4)=="#")
    {
        if(msg.mid(0, 4)=="0000")
        {
            m_nodeMsg.addr.append("FFFF");
        }
        else
        {
            m_nodeMsg.addr.append(msg.mid(0, 4));    //节点地址
        }
        m_nodeMsg.cmd[0] = msg.at(5);     //命令位
        m_nodeMsg.cmd[1] = msg.at(6);     //命令位
        m_nodeMsg.data[0] = msg.at(7);    //数据位
        m_nodeMsg.data[1] = msg.at(8);    //数据位
        m_nodeMsg.data[2] = msg.at(9);    //数据位
        m_nodeMsg.data[3] = msg.at(10);    //数据位
        QString parity_data = msg.at(11); //校验位
        nodeSetting(m_nodeMsg);
    }
    emit sendOnline(QString::number(m_nodeAddrList.count()));
    qDebug()<<msg;
}

nodeState::nodeState()
{
    this->addr="无";
    this->nodeType="无";
    this->hasLightUnit=false;
    this->hasFanUnit=false;
    this->hasTHUnit=false;
    this->hasBeepUnit=false;
    this->lightStatus=false;
    this->fanStatus=false;
    this->beepStatus=false;
    this->temperature="无";
    this->humidity="无";
}

nodeState::~nodeState()
{

}

void nodeState::initNodeState(QString type)
{
    if(type == "协调器")
    {
        this->addr="FFFF";
        this->nodeType="协调器";
        this->hasLightUnit=false;
        this->hasFanUnit=false;
        this->hasTHUnit=false;
        this->hasBeepUnit=true;
        this->lightStatus=false;
        this->fanStatus=false;
        this->beepStatus=false;
        this->temperature="无";
        this->humidity="无";
    }
    else if(type == "终端")
    {
        this->addr="无";
        this->nodeType="终端";
        this->hasLightUnit=true;
        this->hasFanUnit=true;
        this->hasTHUnit=true;
        this->hasBeepUnit=false;
        this->lightStatus=false;
        this->fanStatus=false;
        this->beepStatus=false;
        this->temperature="无";
        this->humidity="无";
    }
}

QString nodeState::getAddr()
{
    return this->addr;
}
QString nodeState::getNodeType()
{
    return this->nodeType;
}
bool nodeState::getLightStatus()
{
    return this->lightStatus;
}
bool nodeState::getFanStatus()
{
    return this->fanStatus;
}
bool nodeState::getBeepStatus()
{
    return this->beepStatus;
}
QString nodeState::getTemperature()
{
    return this->temperature;
}
QString nodeState::getHumidity()
{
    return this->humidity;
}

bool nodeState::hasLight()
{
    return this->hasLightUnit;
}
bool nodeState::hasFan()
{
    return this->hasFanUnit;
}
bool nodeState::hasTH()
{
    return this->hasTHUnit;
}
bool nodeState::hasBeep()
{
    return this->hasBeepUnit;
}

void nodeState::setAddr(QString addr)
{
    this->addr =addr;
}
void nodeState::setNodeType(QString nodetype)
{
    this->nodeType = nodetype;
}
void nodeState::setLightStatus(bool ls)
{
    this->lightStatus = ls;
}
void nodeState::setFanStatus(bool fs)
{
    this->fanStatus = fs;
}
void nodeState::setBeepStatus(bool bs)
{
    this->beepStatus = bs;
}
void nodeState::setTemperature(QString temp)
{
    this->temperature = temp;
}
void nodeState::setHumidity(QString humi)
{
    this->humidity = humi;
}

void nodeState::setExUnit(bool hsL,bool hsF,bool hsB,bool hsTH)
{
    this->hasLightUnit = hsL;
    this->hasFanUnit = hsF;
    this->hasBeepUnit = hsB;
    this->hasTHUnit = hsTH;
}

//setNode()调用setName(),setSwitch(),setFuncAvable(),setTH();
//setNode应当接收一个参数，用来
