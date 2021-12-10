#include "mainfrm.h"
#include "ui_mainfrm.h"

mainFrm::mainFrm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainFrm)
{
    //    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    //    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    ui->setupUi(this);

    //    buttonNameList.append("ss");
    //    buttonNameList.append("ss");
    //    buttonNameList.append("ss");
    //    buttonNameList.append("ss");



    //    //--------------------------------------------
    //    //本地主机名
    //    QString hostName = QHostInfo::localHostName();

    //    //本机IP地址
    //    QHostInfo hostInfo = QHostInfo::fromName(hostName);

    //    //IP地址列表
    //    QList<QHostAddress> addrList = hostInfo.addresses();
    //    for(int i=0;i<addrList.count();i++)
    //    {
    //        QHostAddress host = addrList.at(i);

    //        if(QAbstractSocket::IPv4Protocol == host.protocol())
    //        {
    //            QString ip = host.toString();
    //            ui->comboBox->addItem(ip);
    //        }
    //    }

    //    m_tcpServer = new QTcpServer(this);
    //    connect(m_tcpServer,&QTcpServer::newConnection,this,&Widget::on_newConnection);
    //    ui->lineEditPort->setText("8080");

    //初始化界面
    //this->setFixedSize(880,630);
    //w_size=1;
    this->initFrm();
}

mainFrm::~mainFrm()
{
    delete ui;
}


void mainFrm::initFrm()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    //setPalette(QPalette(QColor(132,223,255)));//设置窗口背景
    //setAutoFillBackground(true);
    //this->resize(1920,1030);
    this->resize(1200,742);
    ui->comboBox_event->addItems(QStringList()<<"打开灯泡"<<"关闭灯泡"<<"打开风扇"<<"关闭风扇"<<"监测温度");
    radioSelect=0;
    ui->radioButton_time->click();
    //this->resize(QGuiApplication::primaryScreen()->availableGeometry().width(),QGuiApplication::primaryScreen()->availableGeometry().height());
    //qDebug()<<this;

    maxSize.setWidth(QGuiApplication::primaryScreen()->availableGeometry().width()-30);
    maxSize.setHeight(QGuiApplication::primaryScreen()->availableGeometry().height());
    norSize.setWidth(this->width()-30);
    norSize.setHeight(this->height()-30);

    ui->label_tile->setText("网络节点智能管理系统");
    ui->label_tile->setFont(QFont("Microsoft Yahei", 20));
    this->setWindowTitle(ui->label_tile->text());

    //初始化日志表
    ui->stackedWidget->addWidget(LL);
    LL->logViewer(1);
    //    //单独设置指示器大小
    //    int addWidth = 20;
    //    int addHeight = 10;
    //    int rbtnWidth = 15;
    //    int ckWidth = 13;
    //    int scrWidth = 12;
    //    int borderWidth = 3;

    //右下角时间
    QTimer *timer = new QTimer(this);
    //这里this不要忘了哈，不然需要自己手动添加资源释放
    connect(timer, SIGNAL(timeout()), this, SLOT(ShowDateTime()));
    //关联信号和槽
    timer->start(1000);


    //圆角矩形
    //绘制背景图
    this->RoundedRect(norSize.width(),norSize.width());

    //---------------

    //设置窗体透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    //设置无边框
    //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //实例阴影shadow
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    //设置阴影距离
    shadow->setOffset(0,0);
    //设置阴影颜色
    shadow->setColor(QColor("#444444"));
    //设置阴影圆角
    shadow->setBlurRadius(15);
    //给嵌套QWidget设置阴影
    ui->widget_bg->setGraphicsEffect(shadow);
    //给垂直布局器设置边距(此步很重要, 设置宽度为阴影的宽度)
    ui->lay_bg->setMargin(1);
    ui->widget_bg->setStyleSheet("background-color:white");


    /* custom system btn */
    int wide = width();//获取界面的宽度
    maxOrNormal=true;
    //    QIcon icon;
    //    icon = style()->standardIcon( QStyle::SP_TitleBarMinButton );
    //    ui->pushButton_min->setIcon( icon );
    //    if( maxOrNormal ){// true represents Max
    //        icon = style()->standardIcon( QStyle::SP_TitleBarMaxButton );
    //        ui->pushButton_max->setIcon( icon );
    //    }else{
    //        icon = style()->standardIcon( QStyle::SP_TitleBarNormalButton );
    //        ui->pushButton_max->setIcon( icon );
    //    }
    //    icon = style()->standardIcon( QStyle::SP_TitleBarCloseButton );
    //    ui->pushButton_close->setIcon( icon );


    //this->location = this->geometry();

    //设置最小化最大化关闭三个按钮


    //获取最小化、关闭按钮图标
    QIcon minIcon  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QIcon closeIcon = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    QIcon maxIcon = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);

    //设置最小化、关闭按钮图标
    ui->pushButton_min->setIcon(minIcon);
    ui->pushButton_close->setIcon(closeIcon);
    ui->pushButton_max->setIcon(maxIcon);

    //设置最小化、关闭按钮在界面的位置
    ui->pushButton_min->setGeometry(wide-65,5,30,30);
    ui->pushButton_close->setGeometry(wide-5,5,30,30);
    ui->pushButton_max->setGeometry(wide-35,5,30,30);

    //设置鼠标移至按钮上的提示信息
    ui->pushButton_min->setToolTip(tr("最小化"));
    ui->pushButton_close->setToolTip(tr("关闭"));
    ui->pushButton_max->setToolTip(tr("最大化"));

    //设置最小化、关闭按钮的样式
    ui->pushButton_max->setStyleSheet("background-color:transparent;border:none;");
    ui->pushButton_close->setStyleSheet("background-color:transparent;border:none;");
    ui->pushButton_min->setStyleSheet("background-color:transparent;border:none;");

    connect( ui->pushButton_min, SIGNAL(clicked(bool)), this, SLOT( onMin(bool)) );
    connect( ui->pushButton_max, SIGNAL(clicked(bool)), this, SLOT( onMaxOrNormal(bool)) );
    connect( ui->pushButton_close, SIGNAL(clicked(bool)), this, SLOT( onClose(bool)) );

    //设置顶部和侧边导航按钮
    QList<QToolButton *> tbtns = ui->widget_fucBtns->findChildren<QToolButton *>();
    QList<QPushButton *> lbtns = ui->widget_left->findChildren<QPushButton *>();
    foreach (QToolButton *tbtn, tbtns) {
        //btn->setIconSize(icoSize);
        //btn->setMinimumWidth(icoWidth);
        tbtn->setCheckable(true);
        tbtn->setStyleSheet("background-color:transparent;border:none;");
        connect(tbtn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }
    foreach (QPushButton *lbtn, lbtns) {
        //btn->setIconSize(icoSize);
        //btn->setMinimumWidth(icoWidth);
        lbtn->setCheckable(true);
        lbtn->setStyleSheet("background-color:transparent;border:none;");
        connect(lbtn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }
    ui->toolButton_main->click();
}

void mainFrm::RoundedRect(int w,int h)
{
    //圆角矩形
    //绘制背景图
    QBitmap bmp(w,h);
    //qDebug()<<this->size();
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),15,15);
    //ui->widget_bg->setMask(bmp);
    ui->widget_bg->setMask(bmp);
}

void mainFrm::buttonClick()
{
    QToolButton *tb = (QToolButton *)sender();
    QString tname = tb->text();
    QPushButton *lb = (QPushButton *)sender();
    QString lname = tb->text();

    QList<QToolButton *> tbtns = ui->widget_fucBtns->findChildren<QToolButton *>();
    QList<QPushButton *> lbtns = ui->widget_left->findChildren<QPushButton *>();
    foreach (QToolButton *tbtn, tbtns) {
        if (tbtn == tb) {
            tbtn->setChecked(true);
        } else {
            tbtn->setChecked(false);
        }
    }
    foreach (QPushButton *lbtn, lbtns) {
        if (lbtn == lb) {
            lbtn->setChecked(true);
        } else {
            lbtn->setChecked(false);
        }
    }

    if (tname == "主界面"||lname == "设备信息") {
        ui->stackedWidget->setCurrentIndex(0);
    } else if (tname == "系统设置") {
        ui->stackedWidget->setCurrentIndex(1);
    } else if (tname == "使用说明") {
        ui->stackedWidget->setCurrentIndex(2);
    } else if (lname == "日志查看") {
        ui->stackedWidget->setCurrentWidget(LL);
    } else if (lname == "温度表") {
        ui->stackedWidget->setCurrentIndex(4);
    } else if (tname == "退出系统") {
        this->close();
    }
}

void mainFrm::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
        //鼠标相对于窗体的位置（或者使用event->globalPos() - this->pos()）
        move_point = event->pos();;
    }
}
void mainFrm::mouseMoveEvent(QMouseEvent *event)
{
    //若鼠标左键被按下
    if(mouse_press)
    {
        //鼠标相对于屏幕的位置
        QPoint move_pos = event->globalPos();

        //移动主窗体位置
        this->move(move_pos - move_point);
    }
}
void mainFrm::mouseReleaseEvent(QMouseEvent *event)
{
    //设置鼠标为未被按下
    mouse_press = false;
}

void mainFrm::onMin(bool)
{
    if( windowState() != Qt::WindowMinimized ){
        setWindowState( Qt::WindowMinimized );
    }
}

void mainFrm::onMaxOrNormal(bool)
{
    QIcon icon;
    if( maxOrNormal ){
        icon = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);
        ui->pushButton_max->setIcon(icon);
        setWindowState( Qt::WindowMaximized );
        this->RoundedRect(maxSize.width(),maxSize.width());
    }else {
        icon = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
        ui->pushButton_max->setIcon(icon);
        setWindowState( Qt::WindowNoState );
        this->RoundedRect(norSize.width(),norSize.height());
    }
    maxOrNormal = !maxOrNormal;
}

void mainFrm::onClose(bool)
{
    close();
}



//void mainFrm::on_pushButton_2_clicked()
//{
//    //创建水平布局,用于设置按钮的排列顺序
//    QHBoxLayout *hBoxLayout = new QHBoxLayout();
//    hBoxLayout->setObjectName(hBoxLay);
//    foreach(QString buttonName,buttonNameList)
//    {
//        QPushButton *pButton = new QPushButton(buttonName,ui->scrollArea);
//        pButton->setObjectName(buttonName);
//        pButton->setText(buttonName);
//        hBoxLayout->addWidget(pButton);
//    }
//    ui->scrollArea->setLayout(hBoxLayout);

//}


//void mainFrm::on_pushButton_4_clicked()
//{
//    foreach(QString buttonName, buttonNameList)
//    {
//        //获取groupBox中的Pushbutton
//        QPushButton *pushBt =  ui->scrollArea->findChild<QPushButton*>(buttonName);
//        //删除pushButton
//        delete pushBt;
//    }
//    //删除水平布局,如果此处不删除，会使得第二次添加相同名称的QPushbutton时失败
//    QHBoxLayout *HBoxlay = ui->scrollArea->findChild<QHBoxLayout*>(hBoxLay);
//    delete HBoxlay;
//}

void mainFrm::closeEvent(QCloseEvent *event)
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

void mainFrm::getLoginUser(QString user)
{
    usr=user;
    ui->label_bottom_user->setText(usr+"，欢迎使用！");
}

void mainFrm::ShowDateTime()
{
    QString dtm =QDateTime::currentDateTime() .toString("yyyy年MM月dd日 hh:mm:ss ddd");
    ui->label_bottom_time->setText(dtm);
}

void mainFrm::on_pushButton_setTask_clicked()
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


void mainFrm::on_radioButton_time_clicked()
{
    ui->dateTimeEdit->setEnabled(false);
    ui->timeEdit->setEnabled(true);
    radioSelect=1;
}


void mainFrm::on_radioButton_dateTime_clicked()
{
    ui->dateTimeEdit->setEnabled(true);
    ui->timeEdit->setEnabled(false);
    radioSelect=0;
}

void mainFrm::taskViewer()
{
    viewTask=T.getTask();
    size_row = viewTask.size();
    qDebug() << "接收到任务数量："<<viewTask.size();
    taskTable(size_row);
}

void mainFrm::taskTable(int size_row)
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

void mainFrm::on_pushButton_startTask_clicked()
{
    int i=0;
    i= ui->tableView_task->currentIndex().row()+1;
    T.setTask(i,1);
    taskViewer();
}


void mainFrm::on_pushButton_stopTask_clicked()
{
    int i=0;
    i= ui->tableView_task->currentIndex().row()+1;
    T.setTask(i,0);
    taskViewer();
}


void mainFrm::on_pushButton_delTask_clicked()
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
/*
void mainFrm::on_btnStart_clicked()
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

void mainFrm::on_btnStop_clicked()
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

void mainFrm::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

void mainFrm::on_newConnection()
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

void mainFrm::onConnected()
{
    ui->plainTextEdit->appendPlainText("** client socket connected");
    ui->plainTextEdit->appendPlainText("** peer address: "+m_tcpSocket->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("** peer port: "+QString::number(m_tcpSocket->peerPort()));
}

void mainFrm::onDisConnected()
{
    ui->plainTextEdit->appendPlainText("** client socket disconnected");
    m_tcpSocket->deleteLater();
}

void mainFrm::onStateChanged(QAbstractSocket::SocketState socketState)
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

//void mainFrm::onReadyRead()
//{
//    while(m_tcpSocket->canReadLine())
//    {
//        ui->plainTextEdit->appendPlainText("[in] "+m_tcpSocket->readLine());
//    }
//}

//void mainFrm::on_btnSend_clicked()
//{
//    QString msg =ui->lineEdit->text();
//    ui->plainTextEdit->appendPlainText("[out]"+msg);
//    QByteArray str = msg.toUtf8();
//    str.append('\n');
//    m_tcpSocket->write(str);
//}


//void mainFrm::on_pushButton_switch2Network_clicked()
//{
//    if(w_size)
//    {
//        this->setFixedSize(1170,630);
//        w_size=0;
//    }
//    else
//    {
//        this->setFixedSize(880,630);
//        w_size=1;
//    }
//}
*/
