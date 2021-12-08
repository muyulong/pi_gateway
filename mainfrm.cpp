#include "mainfrm.h"
#include "ui_mainfrm.h"

mainFrm::mainFrm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainFrm)
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
    //setPalette(QPalette(QColor(132,223,255)));//设置窗口背景
    //setAutoFillBackground(true);

    ui->label_tile->setText("网络节点智能管理系统");
    ui->label_tile->setFont(QFont("Microsoft Yahei", 20));
    this->setWindowTitle(ui->label_tile->text());

    //单独设置指示器大小
        int addWidth = 20;
        int addHeight = 10;
        int rbtnWidth = 15;
        int ckWidth = 13;
        int scrWidth = 12;
        int borderWidth = 3;

    //---------------
    QStringList qss;
    qss.append(QString("QComboBox::drop-down,QDateEdit::drop-down,QTimeEdit::drop-down,QDateTimeEdit::drop-down{width:%1px;}").arg(addWidth));
    qss.append(QString("QComboBox::down-arrow,QDateEdit[calendarPopup=\"true\"]::down-arrow,QTimeEdit[calendarPopup=\"true\"]::down-arrow,"
                       "QDateTimeEdit[calendarPopup=\"true\"]::down-arrow{width:%1px;height:%1px;right:2px;}").arg(addHeight));
    qss.append(QString("QRadioButton::indicator{width:%1px;height:%1px;}").arg(rbtnWidth));
    qss.append(QString("QCheckBox::indicator,QGroupBox::indicator,QTreeWidget::indicator,QListWidget::indicator{width:%1px;height:%1px;}").arg(ckWidth));
    qss.append(QString("QScrollBar:horizontal{min-height:%1px;border-radius:%2px;}QScrollBar::handle:horizontal{border-radius:%2px;}"
                       "QScrollBar:vertical{min-width:%1px;border-radius:%2px;}QScrollBar::handle:vertical{border-radius:%2px;}").arg(scrWidth).arg(scrWidth / 2));
    qss.append(QString("QWidget#widget_top>QToolButton:pressed,QWidget#widget_top>QToolButton:hover,"
                       "QWidget#widget_top>QToolButton:checked,QWidget#widget_top>QLabel:hover{"
                       "border-width:0px 0px %1px 0px;}").arg(borderWidth));
    qss.append(QString("QWidget#widget_left>QPushButton:checked,QWidget#widget_left>QToolButton:checked,"
                       "QWidget#widget_left>QPushButton:pressed,QWidget#widget_left>QToolButton:pressed{"
                       "border-width:0px 0px 0px %1px;}").arg(borderWidth));
    this->setStyleSheet(qss.join(""));
    //---------------

    //圆角矩形
    //绘制背景图
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),8,8);
    setMask(bmp);


    this->max = false;
    //this->location = this->geometry();
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    //设置顶部和侧边导航按钮
    QList<QToolButton *> tbtns = ui->widget_fucBtns->findChildren<QToolButton *>();
    QList<QPushButton *> lbtns = ui->widget_left->findChildren<QPushButton *>();
    foreach (QToolButton *tbtn, tbtns) {
        //btn->setIconSize(icoSize);
        //btn->setMinimumWidth(icoWidth);
        tbtn->setCheckable(true);
        connect(tbtn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }
    foreach (QPushButton *lbtn, lbtns) {
        //btn->setIconSize(icoSize);
        //btn->setMinimumWidth(icoWidth);
        lbtn->setCheckable(true);
        connect(lbtn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }
    ui->toolButton_main->click();
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
        ui->stackedWidget->setCurrentIndex(3);
    } else if (lname == "温度表") {
        ui->stackedWidget->setCurrentIndex(4);
    } else if (tname == "用户退出") {
        exit(0);
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

//窗口最小化按钮
void mainFrm::on_pushButton_min_clicked()
{
    showMinimized();
}

//窗口最大化按钮
void mainFrm::on_pushButton_max_clicked()
{
    static QSize frmSize;
    static QPoint frmPoint;
    if (!max) {
        //保存原本的大小位置
        frmSize.setWidth(width());
        frmSize.setHeight(height());
        frmPoint=pos();
        this->setGeometry(QGuiApplication::primaryScreen()->availableGeometry());
        //qDebug()<<QGuiApplication::primaryScreen()->availableGeometry();
        move(0,0);
    } else {
        resize(frmSize.width(),frmSize.height());
        move(frmPoint.x(),frmPoint.y());
    }
    max = !max;
}

//窗口关闭按钮
void mainFrm::on_pushButton_close_clicked()
{
    this->close();
}
