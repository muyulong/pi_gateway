#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <mainfrm/mainfrm.h>
#include <user/user.h>
#include <QMessageBox>

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
    ~login();

private slots:

    void on_pushButton_login_clicked();

signals:
    void exitLogin(); //新建一个信号槽
    void exitWelcome();
    bool compareUser(QString s1, QString s2);

private:
    Ui::login *ui;
    mainFrm *m_mainFrm = new mainFrm;
};

#endif // LOGIN_H
