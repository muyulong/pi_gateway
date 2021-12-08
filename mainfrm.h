#ifndef MAINFRM_H
#define MAINFRM_H

#include <QDialog>
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

namespace Ui {
class mainFrm;
}

class mainFrm : public QDialog
{
    Q_OBJECT

public:
    explicit mainFrm(QWidget *parent = nullptr);
    ~mainFrm();

private slots:
    void on_pushButton_min_clicked();

    void on_pushButton_max_clicked();

    void on_pushButton_close_clicked();

private:
    Ui::mainFrm *ui;

    QPoint move_point; //移动的距离
    bool mouse_press; //鼠标按下
    //鼠标按下事件
    void mousePressEvent(QMouseEvent *event);
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event);
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);

    bool max;
    //最大化状态

private slots:
    void initFrm();

    void buttonClick();
};

#endif // MAINFRM_H
