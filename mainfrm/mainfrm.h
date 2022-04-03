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

    ~mainFrm();

signals:
    void setBtnClicked();
    void addLog(QString, int, QString);
    QString getRunTaskNum();

private:
    Ui::mainFrm *ui;


    QString usr;

    class log *m_log = new class log;
    task *m_task = new task;
    netCom *m_netCom = new netCom;
    serialCom *m_serialCom = new serialCom;
    node *m_node = new node;
    THchart *m_THchart = new THchart;

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

    void checkTime2RunTask(QString);

    bool maxOrNormal; // true表示当前窗口状态为normal，图标应显示为max
public slots:
    void setTip(QString);

    void setOnline(QString);
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
