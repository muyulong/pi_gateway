#include "node.h"
#include "ui_node.h"

node::node(QWidget *parent) : QWidget(parent),
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

    //connect(N,hasReadData(),this,commandReceive());

    this->setName();
    this->setSwitch();
    this->setFuncAvable();
    this->setTH();
}

//初始化节点树
void node::initTree()
{
    // 1，构造Model
    QStandardItemModel *model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList() << "节点编号"
                                     << "节点类型"); //设置列头
    // 2，给QTreeView应用model
    ui->treeView->setModel(model);
}

//设置节点
void node::setName()
{
    ui->lb_nodeName->setText(m_nodeStatus.addr);
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
        ui->checkBox_temp->setChecked(1);
    }
    else
    {
        ui->checkBox_temp->setChecked(0);
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
    //QString temp_str = QString("%1").arg(t);
    //ui->lb_temp->setText(temp_str);
}

//设置树
void node::setTree()
{
}

//------------------------------

/*
initSystem()
initDevices()
checkTasks()
这个等会儿写
getDevicesInfo()
getOperableDevices()
commandEncode(String)
commandDecode(未知类型)
commandSend(未知类型)
commandReceive()
编码解码功能放在接收和发送完成之后写
*/

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
        cmd = "--";
    }
    if (str == "状态")
    {
        cmd = "S-";
    }
    return cmd;
}

int parityCheck(QString nMsg)
{
    // QString nMsg="112233";

    //    QString strMsg="h";
    //    char* chMsg;
    //    QByteArray baMsg = strMsg.toLatin1();
    //    chMsg=baMsg.data();
    //    QByteArray byte_nMsg = nMsg.toLatin1();
    //    for(int i = 0; i < nMsg.size(); i++)
    //    {
    //        qDebug() << int(byte_nMsg.at(i));//输出
    //    }
    //    char bitMask = 1 << 7;
    //         for (int i = 0; i < 8; i++)
    //         {
    //             qDebug()  << (bitMask & chMsg[i] ? 1 : 0);
    //             chMsg[i] = chMsg[i] << 1;
    //         }

    QByteArray byte_nMsg = nMsg.toLatin1();
    qDebug() << byte_nMsg;
    return 1;
}

// commandSend("开灯",0,2);
//把编码解码和发送接收做一块儿了

// FFFF#//1 初始化所有设备
// 0bca#//1 初始化0bca设备
// FFFF#OL1 向所有节点发送开灯指令
// 0bca#OF1 向0bca节点发送开风扇指令
// FFFF#HT1 查询所有节点温度和湿度
// 0bca#HT1
// 0bca#S/1
// FFFF#S/1

void node::commandSend(int nodeID, QString msg)
{
    QString node_add = m_nodeMsg.nodeAddr[nodeID];
    QString cmd_str = node_add + "#" + str2cmd(msg);
    QString parity_type = QString(parityCheck(cmd_str));
    cmd_str = cmd_str + parity_type;
    N.sendData(cmd_str);
}

void node::nodeSetting(nodeMsg m_Node)
{
    m_nodeStatus.addr = m_Node.nodeAddr.;
    if(m_Node.nodeAddr =="0000")
    {
        m_nodeStatus.nodeType = "协调器节点";
        m_nodeStatus.hasBeep = true;
    }
    else
    {
        m_nodeStatus.nodeType = "终端节点";
        m_nodeStatus.hasBeep = false;
    }
    switch (m_Node.cmd) {
    case "OL":
        if(m_Node.data = "0001")
        {
            m_nodeStatus.lightStatus = true;
        }
        else
        {
            m_nodeStatus.lightStatus = false;
        }
        break;
    case "CL":
        if(m_Node.data = "0001")
        {
            m_nodeStatus.lightStatus = false;
        }
        else
        {
            m_nodeStatus.lightStatus = true;
        }
        break;
    case "OF":
        if(m_Node.data = "0001")
        {
            m_nodeStatus.fanStatus = true;
        }
        else
        {
            m_nodeStatus.fanStatus = false;
        }
        break;
    case "CF":
        if(m_Node.data = "0001")
        {
            m_nodeStatus.fanStatus = false;
        }
        else
        {
            m_nodeStatus.fanStatus = true;
        }
        break;
    case "IN":
        m_nodeStatus.lightStatus = bool(m_Node.data.at(0));
        m_nodeStatus.fanStatus = bool(m_Node.data.at(1));
        break;
    case "TH":
        m_nodeStatus.temperature = m_Node.data.mid(0,2).toInt();
        m_nodeStatus.humidity = m_Node.data.mid(2,2).toInt();
        break;
    case "--":
        m_nodeStatus.hasLight = bool(m_Node.data.at(0));
        m_nodeStatus.hasFan = bool(m_Node.data.at(1));
        m_nodeStatus.hasTH = bool(m_Node.data.at(3));
        break;
    default:
        break;
    }
}

// 0bca#IN11-11 表示0bca节点风扇打开，灯泡打开
// 0bcb#IN11-11 表示0bcb节点风扇打开，灯泡打开
// 0bcc#IN11-11 表示0bcc节点风扇打开，灯泡打开
// 0000#OL00011 所有节点成功打开灯泡
// 0000#OL00001 所有节点打开灯泡失败
// 0bca#OF00011 0bca节点成功打开风扇
// 0bca#OF00001 0bca节点打开风扇失败
// 0bca#TH20201 0bca节点查询到温度，温度为20度
// 0bcb#TH20211 0bcb节点查询到温度为20度，温度为21度
// 0bcc#TH22221 0bcc节点查询到温度，温度为22度
// 0bca#--11-11 0bca节点有灯泡，风扇，温湿度传感器

void node::getNodeMsg()
{
    rcvMsg.enqueue(N.getData());
    while (rcvMsg.count()>0) {
        this->commandReceive();
    }
}

void node::commandReceive()
{
    nodeMsg m_nodeMsg;
    QString msg = rcvMsg.dequeue();
    m_nodeMsg.nodeAddr.append(msg.mid(0, 4));    //节点地址
    m_nodeMsg.cmd = msg.mid(5, 2);     //命令位
    m_nodeMsg.data = msg.mid(8, 4);    //数据位
    QString parity_type = msg.mid(11, 1); //校验位
    setNode(m_nodeMsg);
}
