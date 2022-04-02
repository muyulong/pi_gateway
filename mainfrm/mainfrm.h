#ifndef MAINFRM_H
#define MAINFRM_H

#include <QWidget>
#include <log/log.h>
#include <task/task.h>
#include <com/net/netcom.h>
#include <com/serial/serialcom.h>
#include <node/node.h>
#include <QScreen>
#include <QPainter>
#include <QBitmap>
#include <QGraphicsEffect>
#include <QPaintEvent>
#include "thchart/thchart.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class mainFrm;
}
QT_END_NAMESPACE

class mainFrm : public QWidget
{
    Q_OBJECT

public:
    explicit mainFrm(QWidget *parent = nullptr);
    void getLoginUser(QString user);

    //void initSystem();
    //初始化非主页面的系统基本功能
    //void initDevices();
    //初始化节点数据
    //void checkTasks();
    //检查待执行计划任务

    QString usr;

    class log *LL = new class log;
    class log L;
    task *TT = new task;
    task T;
    netCom *NN = new netCom;
    netCom N;
    serialCom *SS = new serialCom;
    serialCom S;
    node *NNode = new node;
    node Node;

    THchart *TH = new THchart;


    ~mainFrm();

signals:
    void setBtnClicked();

private:
    Ui::mainFrm *ui;

    void closeEvent(QCloseEvent *event);

    QPoint move_point; //移动的距离
    bool mouse_press;  //鼠标按下
    //鼠标按下事件
    void mousePressEvent(QMouseEvent *event);
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event);
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);

    void RoundedRect(int w, int h);
    //绘制圆角矩形

    bool maxOrNormal; // true表示当前窗口状态为normal，图标应显示为max
public slots:
        void setTip(QString);

        void setOnline(QString);

        void setTaskNum(QString);
private slots:

    void ShowDateTime();

    void initFrm();

    void buttonClick();

    void on_pushButton_about_clicked();

    /* custom system btn */
    void onMin(bool);
    void onMaxOrNormal(bool);
    void onClose(bool);
};
#endif // MAINFRM_H
