#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    //    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    //    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    ui->setupUi(this);

    buttonNameList.append("ss");
    buttonNameList.append("ss");
    buttonNameList.append("ss");
    buttonNameList.append("ss");

    ui->comboBox_event->addItems(QStringList()<<"打开灯泡"<<"关闭灯泡"<<"打开风扇"<<"关闭风扇"<<"监测温度");
    radioSelect=0;
    ui->radioButton_time->click();

    //--------------------------------------------
    //本地主机名
    QString hostName = QHostInfo::localHostName();

    //本机IP地址
    QHostInfo hostInfo = QHostInfo::fromName(hostName);

    //IP地址列表
    QList<QHostAddress> addrList = hostInfo.addresses();
    for(int i=0;i<addrList.count();i++)
    {
        QHostAddress host = addrList.at(i);

        if(QAbstractSocket::IPv4Protocol == host.protocol())
        {
            QString ip = host.toString();
            ui->comboBox->addItem(ip);
        }
    }

    m_tcpServer = new QTcpServer(this);
    connect(m_tcpServer,&QTcpServer::newConnection,this,&Widget::on_newConnection);
    ui->lineEditPort->setText("8080");

    //初始化界面
    this->setFixedSize(880,630);
    w_size=1;
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_2_clicked()
{
    //创建水平布局,用于设置按钮的排列顺序
    QHBoxLayout *hBoxLayout = new QHBoxLayout();
    hBoxLayout->setObjectName(hBoxLay);
    foreach(QString buttonName,buttonNameList)
    {
        QPushButton *pButton = new QPushButton(buttonName,ui->scrollArea);
        pButton->setObjectName(buttonName);
        pButton->setText(buttonName);
        hBoxLayout->addWidget(pButton);
    }
    ui->scrollArea->setLayout(hBoxLayout);

}


void Widget::on_pushButton_4_clicked()
{
    foreach(QString buttonName, buttonNameList)
    {
        //获取groupBox中的Pushbutton
        QPushButton *pushBt =  ui->scrollArea->findChild<QPushButton*>(buttonName);
        //删除pushButton
        delete pushBt;
    }
    //删除水平布局,如果此处不删除，会使得第二次添加相同名称的QPushbutton时失败
    QHBoxLayout *HBoxlay = ui->scrollArea->findChild<QHBoxLayout*>(hBoxLay);
    delete HBoxlay;
}

void Widget::closeEvent(QCloseEvent *event)
{
    switch( QMessageBox::information(this,tr("提示"),tr("确定退出系统?"),tr("确定"), tr("取消"),0,1))
    {
    case 0:
        this->L.addLog(usr,2);
        event->accept();
        break;
    case 1:
    default:
        event->ignore();
        break;
    }
}

void Widget::getLoginUser(QString user)
{
    usr=user;
}

void Widget::on_pushButton_viewLog_clicked()
{
    L.logViewer(1);
    L.setModal(false);
    L.show();
}


void Widget::on_pushButton_setTask_clicked()
{
    QDateTime datetime;
    QTime time;
    int taskContentID;
    datetime=ui->dateTimeEdit->dateTime();
    time=ui->timeEdit->time();
    taskContentID=ui->comboBox_event->currentIndex();
    T.addTask(datetime,time,taskContentID,radioSelect);
    taskViewer();
}


void Widget::on_radioButton_time_clicked()
{
    ui->dateTimeEdit->setEnabled(false);
    ui->timeEdit->setEnabled(true);
    radioSelect=1;
}


void Widget::on_radioButton_dateTime_clicked()
{
    ui->dateTimeEdit->setEnabled(true);
    ui->timeEdit->setEnabled(false);
    radioSelect=0;
}

void Widget::taskViewer()
{
    viewTask=T.getTask();
    size_row = viewTask.size();
    qDebug() << "接收到任务数量："<<viewTask.size();
    taskTable(size_row);
}

void Widget::taskTable(int size_row)
{
    //。。。。。。。。。。。。。
    QStandardItemModel* standItemModel = new QStandardItemModel(this);
    standItemModel->setColumnCount(3);
    //standItemModel->setHeaderData(0,Qt::Horizontal,QStringLiteral("时间"));   //设置表头内容
    standItemModel->setHeaderData(0,Qt::Horizontal,("时间"));   //设置表头内容
    standItemModel->setHeaderData(1,Qt::Horizontal,("任务"));
    standItemModel->setHeaderData(2,Qt::Horizontal,("状态"));
    //向表格添加内容
    for(int i=0;i<size_row;++i)
    {

        QString time=viewTask[i][0];
        QString task=viewTask[i][1];
        QString status=viewTask[i][2];
        if(status=="0")
        {
            status="未运行";
        }
        if(status=="1")
        {
            status="运行中";
        }
        standItemModel->setItem(i, 0, new QStandardItem(time));
        standItemModel->setItem(i, 1, new QStandardItem(task));
        standItemModel->setItem(i, 2, new QStandardItem(status));
        standItemModel->item(i,0)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
        standItemModel->item(i,1)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
        standItemModel->item(i,2)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
    }
    ui->tableView_task->setModel(standItemModel);    //挂载表格模型
    //设置表格属性
    //tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);        //表头信息显示居中
    ui->tableView_task->setColumnWidth(0,150);       //设定表格宽度
    ui->tableView_task->setColumnWidth(1,80);
    ui->tableView_task->setColumnWidth(2,75);
    //tableView->verticalHeader()->hide();    //隐藏默认显示的行头
    ui->tableView_task->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中时整行选中
    ui->tableView_task->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑
    /* 设置列宽在可视界面自适应宽度 */
    //ui->tableView_task->horizontalHeader()->setSectionResizeMode (QHeaderView::Stretch);
    //qDebug() <<tableView->horizontalHeader();
    /* 行颜色交替显示 */
    ui->tableView_task->setAlternatingRowColors(true);
    /* 不允许在图形界面修改内容 */
    //    tableView->setContextMenuPolicy(Qt::CustomContextMenu);         //需要在表格使用右键菜单，需要启动该属性
    //    tableView->sortByColumn(0,Qt::AscendingOrder);                 //表格第0列，按降序排列
    ui->tableView_task->setSelectionMode(QAbstractItemView::SingleSelection);
    //。。。。。。。。。。。。。
}

void Widget::on_pushButton_startTask_clicked()
{
    int i=0;
    i= ui->tableView_task->currentIndex().row()+1;
    T.setTask(i,1);
    taskViewer();
}


void Widget::on_pushButton_stopTask_clicked()
{
    int i=0;
    i= ui->tableView_task->currentIndex().row()+1;
    T.setTask(i,0);
    taskViewer();
}


void Widget::on_pushButton_delTask_clicked()
{
    QString dlgTitle=QString("删除");
    QString strInfo;
    int i=0;
    i= ui->tableView_task->currentIndex().row()+1;
    qDebug()<<i;
    if(i==0)
    {
        strInfo="未选中任何行！";
    }
    else
    {
        bool dT=T.delTask(i);
        if(!dT)
        {
            strInfo=QString("无法删除正在运行中的任务！");
        }
        if(dT)
        {
            strInfo=QString("已删除第%1条记录！"). arg(i);
        }
    }
    QMessageBox::information(this, dlgTitle, strInfo,QMessageBox::Ok,QMessageBox::NoButton);
    taskViewer();
}

//--------------------------
//网络调试

void Widget::on_btnStart_clicked()
{
    //当前选择的ip
    QString ip = ui->comboBox->currentText();

    //端口
    int port = ui->lineEditPort->text().toInt();

    QHostAddress addr(ip);

    //监听
    m_tcpServer->listen(addr,port);

    ui->plainTextEdit->appendPlainText("**开始监听...");

    ui->plainTextEdit->appendPlainText("**服务器地址: "+m_tcpServer->serverAddress().toString());

    ui->plainTextEdit->appendPlainText("**服务器端口: "+QString::number(m_tcpServer->serverPort()));

    ui->btnStart->setEnabled(false);

    ui->btnStop->setEnabled(true);

    ui->lbListen->setText("正在监听");
}

void Widget::on_btnStop_clicked()
{
    if(m_tcpServer->isListening())
    {
        m_tcpServer->close();
        ui->btnStart->setEnabled(true);
        ui->btnStop->setEnabled(false);
        ui->lbListen->setText("停止监听");
        ui->plainTextEdit->appendPlainText("**停止监听**");
    }
}

void Widget::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

void Widget::on_newConnection()
{
    m_tcpSocket = m_tcpServer->nextPendingConnection();
    connect(m_tcpSocket,&QTcpSocket::connected,this,&Widget::onConnected);
    connect(m_tcpSocket,&QTcpSocket::disconnected,this,&Widget::onDisConnected);
    connect(m_tcpSocket,&QTcpSocket::stateChanged,this,&Widget::onStateChanged);
    connect(m_tcpSocket,&QTcpSocket::readyRead,this,&Widget::onReadyRead);

    ui->plainTextEdit->appendPlainText("** client socket connected");
    ui->plainTextEdit->appendPlainText("** peer address: "+m_tcpSocket->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("** peer port: "+QString::number(m_tcpSocket->peerPort()));
}

void Widget::onConnected()
{
    ui->plainTextEdit->appendPlainText("** client socket connected");
    ui->plainTextEdit->appendPlainText("** peer address: "+m_tcpSocket->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("** peer port: "+QString::number(m_tcpSocket->peerPort()));
}

void Widget::onDisConnected()
{
    ui->plainTextEdit->appendPlainText("** client socket disconnected");
    m_tcpSocket->deleteLater();
}

void Widget::onStateChanged(QAbstractSocket::SocketState socketState)
{
    switch (socketState)
    {
    case QAbstractSocket::UnconnectedState:
        ui->lbListen->setText("UnconnectedState");break;
    case QAbstractSocket::HostLookupState:
        ui->lbListen->setText("HostLookupState");break;
    case QAbstractSocket::ConnectedState:
        ui->lbListen->setText("ConnectedState");break;
    case QAbstractSocket::ConnectingState:
        ui->lbListen->setText("ConnectingState");break;
    case QAbstractSocket::BoundState:
        ui->lbListen->setText("BoundState");break;
    case QAbstractSocket::ClosingState:
        ui->lbListen->setText("ClosingState");break;
    case QAbstractSocket::ListeningState:
        ui->lbListen->setText("ListeningState");break;
    }

}

void Widget::onReadyRead()
{
    while(m_tcpSocket->canReadLine())
    {
        ui->plainTextEdit->appendPlainText("[in] "+m_tcpSocket->readLine());
    }
}

void Widget::on_btnSend_clicked()
{
    QString msg =ui->lineEdit->text();
    ui->plainTextEdit->appendPlainText("[out]"+msg);
    QByteArray str = msg.toUtf8();
    str.append('\n');
    m_tcpSocket->write(str);
}


void Widget::on_pushButton_switch2Network_clicked()
{
    if(w_size)
    {
        this->setFixedSize(1170,630);
        w_size=0;
    }
    else
    {
        this->setFixedSize(880,630);
        w_size=1;
    }
}
