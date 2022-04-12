#include "regist.h"
#include "ui_regist.h"

regist::regist(QWidget *parent) : QDialog(parent),
                                  ui(new Ui::regist)
{
    ui->setupUi(this);
}

regist::~regist()
{
    delete ui;
}

void regist::on_pushButton_register_clicked()
{
    QString user;
    QString pwd, pwd2;
    user = ui->username->text();
    pwd = ui->password->text();
    pwd2 = ui->password_2->text();
    if (user == "")
        QMessageBox::warning(this, "", QString("用户名不能为空！"));
    else if (pwd == "")
        QMessageBox::warning(this, "", QString("密码不能为空！"));
    else if (pwd2 == "")
        QMessageBox::warning(this, "", QString("确认密码不能为空！"));
    else if (!(pwd == pwd2))
        QMessageBox::warning(this, "", QString("两次输入密码必须相同！"));
    else
    {
        int reg = setUser(user, pwd);
        if (reg == 1)
        {
            QMessageBox::information(NULL, QString("注册成功"), QString("注册成功！！！"), QMessageBox::Yes);
            this->close();
        }
        else if (reg == 2)
            QMessageBox::warning(NULL, "Error", QString("用户名重复！！！"));
        else if (reg == 0)
            QMessageBox::warning(NULL, "Error", QString("注册失败，请重试！！！"));
    }
}
void regist::closeEvent(QCloseEvent *)
{
    emit exitRegist();
}
