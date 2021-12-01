#ifndef REGIST_H
#define REGIST_H

#include <QDialog>
#include<user.h>

namespace Ui {
class regist;
}

class regist : public QDialog
{
    Q_OBJECT

public:
    explicit regist(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *);

    user U;
    ~regist();

private slots:
    void on_pushButton_register_clicked();
signals:
    void exitRegist();//新建一个信号槽
private:
    Ui::regist *ui;
};

#endif // REGIST_H
