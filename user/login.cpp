#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) : QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    connect(this,&login::sendLoginUser,m_mainFrm,&mainFrm::getLoginUser);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_login_clicked()
{
    user = ui->username->text(); //获取用户名
    pwd = ui->password->text();  //获取密码
    if (user == "")
        QMessageBox::warning(this, "", QString::fromLocal8Bit("用户名不能为空！"));
    else if (pwd == "")
        QMessageBox::warning(this, "", QString::fromLocal8Bit("密码不能为空！"));
    else
    {
        //在数据库中进行查询验证
        bool login = compareUser(user, pwd);
        if (login)
        {
            emit sendLoginUser(user);
            m_mainFrm->addLog(user, 1, "");
            m_mainFrm->show();
            this->close();
            emit exitWelcome();
        }
        else
            QMessageBox::warning(NULL, "Error", QString::fromLocal8Bit("用户名或密码错误！！！"));
    }
}
void login::closeEvent(QCloseEvent *)
{
    emit exitLogin();
}
