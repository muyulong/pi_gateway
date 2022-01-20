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


void node::getDevicesInfo()
{
    QString rcvMsg="#RE-A.ffff////54321@";
    QString nodeMsg[3];
    nodeMsg[0]="#RE-S.0bcaINFA00001@";
    nodeMsg[1]="#RE-S.0bcbINLT00011@";
    nodeMsg[2]="#RE-S.0bccINQT//201@";
    //定义一个二维容器数组
    //[0][0]为广播地址
    //[0][1]为数组行数
    //存放 节点编号 节点类型 节点数据(开闭情况)
    /*
    [0][0] [0][1] [0][2]
    [1][0] [1][1] [1][2]
    */
    //#RE-A.ffff////00021@ 表示0000根节点共有2个子节点
    //#RE-S.0bcaINFA00001@ 表示0bca节点初始化风扇，当前风扇状态为关闭
    //#RE-S.0bcbINLT00011@ 表示0bcb节点初始化灯泡，当前灯泡状态为开启
    //#RE-S.0bccINQT00201@ 表示0bcc节点初始化温度传感器，当前温度20度

    int nodeNum=rcvMsg.mid(14,4).toInt()+1;
    int row=3;
    vector<vector<QString>> rcvInfo(nodeNum,vector<QString>(row,0));
    rcvInfo[0][0]=".ffff";
    rcvInfo[0][1]=rcvMsg.mid(14,4);
    for(int i=0;i<nodeNum;i++)
    {
        rcvInfo[i+1][0]=nodeMsg[i].mid(6,4);
        rcvInfo[i+1][1]=nodeMsg[i].mid(10,4);
        rcvInfo[i+1][2]=nodeMsg[i].mid(14,4);
    }
    dvInfo=rcvInfo;
}

QString commandConvert(QString cmd)
{
    QString C_cmd;
    if(cmd=="开灯")
    {
        C_cmd="OL";
    }
    if(cmd=="关灯")
    {
        C_cmd="CL";
    }
    if(cmd=="开风")
    {
        C_cmd="KF";
    }
    if(cmd=="关风")
    {
        C_cmd="GF";
    }
    if(cmd=="查温")
    {
        C_cmd="QT";
    }
    if(cmd=="初始化")
    {
        C_cmd="//";
    }
    return C_cmd;
}

int parityCheck(QString nMsg)
{
    //QString nMsg="112233";

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
    qDebug()<<byte_nMsg;
    return  1;
}

//commandSend("开灯",0,2);
//把编码解码和发送接收做一块儿了
void node::commandSend(QString msg,int idvl,int nodeID)
{
    //#SE-S.0bcaOL1@
    QString idvl_type;
    QString node_add;
    QString parity_type;
    QString cmd_str;
    switch (idvl)
    {
    case 0:
        idvl_type="-S";
        break;

    case 1:
        idvl_type="-A";
        break;

    default:
        break;
    }
    //#SE-S.0bcaOL1@
    node_add=dvInfo[nodeID+1][0];
    cmd_str="#SE"+idvl_type+"."+node_add+commandConvert(msg);
    parity_type=QString(parityCheck(cmd_str));
    cmd_str=cmd_str+parity_type+"@";
    //return cmd_str;

    //N.sendLinkData();
}

//#RE-S.0bcaQTOK//201@
//#RE-A.ffffCFOK////1@
//#RE-A.ffff////00021@ 表示0000根节点共有2个子节点
//#RE-S.0bcaINFA00001@ 表示0bca节点初始化风扇，当前风扇状态为关闭
//#RE-S.0bcbINLT00011@ 表示0bcb节点初始化灯泡，当前灯泡状态为开启
//#RE-S.0bccINQT00201@ 表示0bcc节点初始化温度传感器，当前温度20度

//需要一个初始化节点的函数
//例如 initNode
//先完成节点类吧
//
//ffff节点标识 -A
//子节点标识 -S
void node::commandReceive(QString rcvMsg)
{
    QString idvl_type;
    QString node_add;
    QString parity_type;
    QString cmd_str;
    QString data_str;
    idvl_type = rcvMsg.mid(4,2);
    node_add = rcvMsg.mid(6,4);
    cmd_str = rcvMsg.mid(10,4);
    data_str = rcvMsg.mid(14,4);
    parity_type = rcvMsg.mid(18,1);
    if(idvl_type=="-A")
    {

    }
    if(idvl_type=="-S")
    {

    }

}
