#ifndef WELCOME_H
#define WELCOME_H

#include <QWidget>
#include"user/regist.h"
#include"user/login.h"

namespace Ui {
class welcome;
}


class welcome : public QWidget
{
    Q_OBJECT

public:
    explicit welcome(QWidget *parent = nullptr);
    ~welcome();

private slots:
    void on_pushButton_register_clicked();

    void on_pushButton_login_clicked();

    void on_pushButton_exit_clicked();

private:
    Ui::welcome *ui;
    regist r;
    login l;
};

#endif // WELCOME_H
