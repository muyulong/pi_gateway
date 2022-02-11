#include "mainfrm.h"
#include "ui_mainfrm.h"

mainFrm::mainFrm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainFrm)
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
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    //setPalette(QPalette(QColor(132,223,255)));//设置窗口背景
    //setAutoFillBackground(true);
    //this->resize(1920,1030);
    this->resize(1200,742);

    //this->resize(QGuiApplication::primaryScreen()->availableGeometry().width(),QGuiApplication::primaryScreen()->availableGeometry().height());
    //qDebug()<<this;

    ui->label_tile->setText("网络节点智能管理系统");
    ui->label_tile->setFont(QFont("Microsoft Yahei", 20));
    this->setWindowTitle(ui->label_tile->text());

    //初始化日志表
    ui->stackedWidget->addWidget(LL);
    LL->logViewer(1);

    //初始化任务表
    QGridLayout *gridTask = new QGridLayout;
    gridTask->addWidget(TT,0,0);
    ui->widget_task->setLayout(gridTask);
    TT->taskViewer();

    //初始化网络连接调试
    QGridLayout *gridNet = new QGridLayout;
    gridNet->addWidget(NN,0,0);
    ui->widget_2net->setLayout(gridNet);

    //初始化串口连接调试
    QGridLayout *gridSerial = new QGridLayout;
    gridSerial->addWidget(SS,0,0);
    ui->widget_2serial->setLayout(gridSerial);

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

    //初始化节点界面
    QGridLayout *gridNode = new QGridLayout;
    gridNode->addWidget(NNode,0,0);
    ui->widget_node->setLayout(gridNode);
    //


    //圆角矩形
    //绘制背景图
    //this->RoundedRect(norSize.width(),norSize.width());

    //---------------

    //设置窗体透明
    //this->setAttribute(Qt::WA_TranslucentBackground, true);
    //设置无边框
    //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //实例阴影shadow
    //QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    //设置阴影距离
    //shadow->setOffset(0,0);
    //设置阴影颜色
    //shadow->setColor(QColor("#444444"));
    //设置阴影圆角
    //shadow->setBlurRadius(15);
    //给嵌套QWidget设置阴影
    //ui->widget_bg->setGraphicsEffect(shadow);
    //给垂直布局器设置边距(此步很重要, 设置宽度为阴影的宽度)
    //ui->lay_bg->setMargin(1);
    //ui->widget_bg->setStyleSheet("background-color:white");


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
        NN->initNet();
        SS->initMycom();
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
    }else {
        icon = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
        ui->pushButton_max->setIcon(icon);
        setWindowState( Qt::WindowNoState );
    }
    maxOrNormal = !maxOrNormal;
}

void mainFrm::onClose(bool)
{
    close();
}

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


void mainFrm::initSystem()
{
    initDevices();
    checkTasks();
    L.addLog("系统",3);
    N.linkStart();
}

void mainFrm::initDevices()
{
    //dvInfo[0][0]=".ffff";
    //dvInfo[0][1]="0";
    //-----------

}

void mainFrm::checkTasks()
{

}
