#include "mainfrm.h"
#include "ui_mainfrm.h"

mainFrm::mainFrm(QWidget *parent)
    : QWidget(parent), ui(new Ui::mainFrm)
{
    ui->setupUi(this);
    this->initFrm();
}

mainFrm::~mainFrm()
{
    delete ui;
}

void mainFrm::initFrm()
{
    //初始化日志表
    ui->stackedWidget->addWidget(m_log);
    m_log->logViewer(1);

    //初始化图表
    ui->stackedWidget->addWidget(m_THchart);

    //初始化任务表
    QGridLayout *gridTask = new QGridLayout;
    gridTask->addWidget(m_task, 0, 0);
    ui->widget_task->setLayout(gridTask);
    m_task->taskViewer();

    //初始化网络连接调试
    QGridLayout *gridNet = new QGridLayout;
    gridNet->addWidget(m_netCom, 0, 0);
    ui->widget_2net->setLayout(gridNet);

    //初始化串口连接调试
    QGridLayout *gridSerial = new QGridLayout;
    gridSerial->addWidget(m_serialCom, 0, 0);
    ui->widget_2serial->setLayout(gridSerial);

    //右下角时间
    QTimer *timer = new QTimer(this);
    //这里this不要忘了哈，不然需要自己手动添加资源释放
    connect(timer, SIGNAL(timeout()), this, SLOT(ShowDateTime()));
    //关联信号和槽
    timer->start(1000);

    //初始化节点界面
    QGridLayout *gridNode = new QGridLayout;
    gridNode->addWidget(m_node, 0, 0);
    ui->widget_node->setLayout(gridNode);

    connect(this,&mainFrm::addLog,m_log,&log::addLog);
    connect(m_node,&node::sendTip,this,&mainFrm::setTip);
    connect(m_node,&node::sendOnline,this,&mainFrm::setOnline);
    connect(this,&mainFrm::getRunTaskNum,m_task,&task::getRunTaskNum);
    connect(m_node, &node::sendTH, m_THchart, &THchart::setTHchart);
    connect(m_task,&task::isOverTemp,m_node,&node::isOverTemp);
    connect(m_task,&task::isOverHumi,m_node,&node::isOverHumi);
    connect(m_task,&task::sendTaskCmd,m_node,&node::commandSend);
    connect(m_node,&node::netStart,m_netCom,&netCom::Start);
    connect(m_node,&node::netStop,m_netCom,&netCom::Stop);
    connect(m_node,&node::getNetAdd,m_netCom,&netCom::getNetAdd);
    connect(m_netCom,&netCom::hasReadData,m_node,&node::commandReceive);
    connect(m_node,&node::sendData,m_netCom,&netCom::sendData);
    connect(m_node,&node::getData,m_netCom,&netCom::getData);

    /* custom system btn */
    int wide = width(); //获取界面的宽度
    maxOrNormal = true;

    //设置最小化最大化关闭三个按钮

    //获取最小化、关闭按钮图标
    QIcon minIcon = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QIcon closeIcon = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    QIcon maxIcon = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);

    //设置最小化、关闭按钮图标
    ui->pushButton_min->setIcon(minIcon);
    ui->pushButton_close->setIcon(closeIcon);
    ui->pushButton_max->setIcon(maxIcon);

    //设置最小化、关闭按钮在界面的位置
    ui->pushButton_min->setGeometry(wide - 65, 5, 30, 30);
    ui->pushButton_close->setGeometry(wide - 5, 5, 30, 30);
    ui->pushButton_max->setGeometry(wide - 35, 5, 30, 30);

    //设置鼠标移至按钮上的提示信息
    ui->pushButton_min->setToolTip(tr("最小化"));
    ui->pushButton_close->setToolTip(tr("关闭"));
    ui->pushButton_max->setToolTip(tr("最大化"));

    //设置最小化、关闭按钮的样式
    ui->pushButton_max->setStyleSheet("background-color:#5584AC;border:none;");
    ui->pushButton_close->setStyleSheet("background-color:#5584AC;border:none;");
    ui->pushButton_min->setStyleSheet("background-color:#5584AC;border:none;");

    connect(ui->pushButton_min, SIGNAL(clicked(bool)), this, SLOT(onMin(bool)));
    connect(ui->pushButton_max, SIGNAL(clicked(bool)), this, SLOT(onMaxOrNormal(bool)));
    connect(ui->pushButton_close, SIGNAL(clicked(bool)), this, SLOT(onClose(bool)));

    //设置顶部和侧边导航按钮
    QList<QToolButton *> tbtns = ui->widget_fucBtns->findChildren<QToolButton *>();
    QList<QPushButton *> lbtns = ui->widget_left->findChildren<QPushButton *>();
    foreach (QToolButton *tbtn, tbtns)
    {
        tbtn->setCheckable(true);
        connect(tbtn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }
    foreach (QPushButton *lbtn, lbtns)
    {
        lbtn->setCheckable(true);
        connect(lbtn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }

    ui->label_tile->setText("网络节点智能管理系统");
    ui->label_tile->setFont(QFont("Microsoft Yahei", 20));
    this->setWindowTitle(ui->label_tile->text());
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    this->resize(1200, 540);

    ui->lb_online->setText("0");
    ui->lb_tasks->setText("0");

    ui->toolButton_main->click();

    QString strExplain = "使用说明";
    ui->label_explain->setText(strExplain);
    ui->label_explain->setAlignment(Qt::AlignCenter);
}

void mainFrm::setTip(QString tip)
{
    ui->label_tips->setText(tip);
}

void mainFrm::setOnline(QString online)
{
    ui->lb_online->setText(online);
}

void mainFrm::RoundedRect(int w, int h)
{
    //绘制背景图
    QBitmap bmp(w, h);
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(), 15, 15);
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
    foreach (QToolButton *tbtn, tbtns)
    {
        if (tbtn == tb)
        {
            tbtn->setChecked(true);
        }
        else
        {
            tbtn->setChecked(false);
        }
    }
    foreach (QPushButton *lbtn, lbtns)
    {
        if (lbtn == lb)
        {
            lbtn->setChecked(true);
        }
        else
        {
            lbtn->setChecked(false);
        }
    }

    if (tname == "主界面" || lname == "设备信息")
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if (tname == "系统设置")
    {
        ui->stackedWidget->setCurrentIndex(1);
        m_netCom->initNet();
        m_serialCom->initMycom();
    }
    else if (tname == "使用说明")
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
    else if (lname == "日志查看")
    {
        ui->stackedWidget->setCurrentWidget(m_log);
    }
    else if (lname == "温度湿度表")
    {
        ui->stackedWidget->setCurrentWidget(m_THchart);
    }
    else if (tname == "退出系统")
    {
        this->close();
    }
}

void mainFrm::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mouse_press = true;
        //鼠标相对于窗体的位置（或者使用event->globalPos() - this->pos()）
        move_point = event->pos();
    }
}
void mainFrm::mouseMoveEvent(QMouseEvent *event)
{
    //若鼠标左键被按下
    if (mouse_press && maxOrNormal)
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
    if(event)
    {
        mouse_press = false;
    }
}

void mainFrm::onMin(bool)
{
    if (windowState() != Qt::WindowMinimized)
    {
        setWindowState(Qt::WindowMinimized);
    }
}

void mainFrm::onMaxOrNormal(bool)
{
    QIcon icon;
    if (maxOrNormal)
    {
        icon = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);
        ui->pushButton_max->setIcon(icon);
        setWindowState(Qt::WindowMaximized);
    }
    else
    {
        icon = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
        ui->pushButton_max->setIcon(icon);
        setWindowState(Qt::WindowNoState);
    }
    maxOrNormal = !maxOrNormal;
}

void mainFrm::onClose(bool)
{
    close();
}

void mainFrm::closeEvent(QCloseEvent *event)
{
    switch (QMessageBox::information(this, tr("提示"), tr("确定退出系统?"), tr("确定"), tr("取消"), 0, 1))
    {
    case 0:
        this->m_log->addLog(usr, 2);
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
    usr = user;
    ui->label_bottom_user->setText(usr + "，欢迎使用！");
}

void mainFrm::ShowDateTime()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString dtm = currentTime.toString("yyyy年MM月dd日 hh:mm:ss ddd");
    QString taskTime = currentTime.toString("yyyy-MM-dd hh:mm:ss");
    ui->label_bottom_time->setText(dtm);
    this->checkTime2RunTask(taskTime);
    ui->lb_tasks->setText(getRunTaskNum());
}

void mainFrm::checkTime2RunTask(QString time)
{
    for(auto task : m_task->m_taskStructVec)
    {
        if(time == task.taskDataTime)
        {
            m_task->runTask(task.taskEvent);
        }
    }
}

void mainFrm::on_pushButton_about_clicked()
{
    QString msg = "Repository:<a href='https://github.com/muyulong/pi_gateway'>GitHub</a> <a href='https://gitee.com/muyulong/pi_gateway'>Gitee</a><br>Develop:<a href='https://github.com/muyulong'>muyulong</a><br>Blog:<a href='https://mmyyll.ml/'>Muyulong’s Blog</a>" ;
    QMessageBox::about(nullptr,"关于",msg);
}
