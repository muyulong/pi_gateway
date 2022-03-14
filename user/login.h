#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <mainfrm/mainfrm.h>
#include <user/user.h>

namespace Ui
{
    class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *);
    mainFrm m;
    user U;
    ~login();

private slots:

    void on_pushButton_login_clicked();

signals:
    void exitLogin(); //新建一个信号槽
    void exitWelcome();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
