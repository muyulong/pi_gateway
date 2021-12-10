#ifndef MAINFRM_H
#define MAINFRM_H

#include <QWidget>
#include<database/dataBase.h>
#include<QCheckBox>
#include<frame/log.h>
#include<task/task.h>
#include <QHostInfo>
#include <QTcpServer>
#include <QTcpSocket>
//#include<QDesktopWidget>
#include<QScreen>
#include<QPainter>
#include <QBitmap>
#include<QGraphicsEffect>
#include <QPaintEvent>


QT_BEGIN_NAMESPACE
namespace Ui {
class mainFrm;
}
QT_END_NAMESPACE

class mainFrm : public QWidget
{
    Q_OBJECT

public:

    explicit mainFrm(QWidget *parent = nullptr);
    void getLoginUser(QString user);
    void taskTable(int size_row);
    void taskViewer();
    QString usr;
    bool radioSelect;

    class log *LL = new class log;
    class log L;
    class task T;

    ~mainFrm();


private slots:

    //void on_pushButton_2_clicked();

    //void on_pushButton_4_clicked();

    //void on_pushButton_viewLog_clicked();

    void on_pushButton_setTask_clicked();

    void on_radioButton_time_clicked();

    void on_radioButton_dateTime_clicked();

    void on_pushButton_startTask_clicked();

    void on_pushButton_stopTask_clicked();

    void on_pushButton_delTask_clicked();

    void ShowDateTime();

    //void on_pushButton_switch2Network_clicked();
    //连接建立按钮
    //---------------------
    //网络调试
    //void on_btnStart_clicked();

    //void on_btnStop_clicked();

    //void on_btnClear_clicked();

    //void on_newConnection();

    //void onConnected();

    //void onDisConnected();

    //void onStateChanged(QAbstractSocket::SocketState socketState);

    //void onReadyRead();

    //void on_btnSend_clicked();


signals:
    void setBtnClicked();

private:
    Ui::mainFrm *ui;

    QStringList buttonNameList;
    QString hBoxLay = "HBL";
    vector<vector<QString> > viewTask;
    int size_row;

    void closeEvent(QCloseEvent *event);
    //bool w_size;

    //------------------------
    QTcpServer *m_tcpServer = nullptr;
    QTcpSocket *m_tcpSocket = nullptr;

    QPoint move_point; //移动的距离
    bool mouse_press; //鼠标按下
    //鼠标按下事件
    void mousePressEvent(QMouseEvent *event);
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event);
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);


    void RoundedRect(int w,int h);
    //绘制圆角矩形

    bool maxOrNormal;//true表示当前窗口状态为normal，图标应显示为max

    QSize norSize;
    QSize maxSize;


private slots:

    void initFrm();

    void buttonClick();

    /* custom system btn */
    void onMin( bool );
    void onMaxOrNormal( bool );
    void onClose( bool );
};
#endif // MAINFRM_H
