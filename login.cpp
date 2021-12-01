#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_login_clicked()
{
    QString user;
    QString pwd;
    user = ui->username->text();//获取用户名
    pwd = ui->password->text();//获取密码
    if(user == "")
        QMessageBox::warning(this,"","用户名不能为空！");
    else if(pwd == "")
        QMessageBox::warning(this,"","密码不能为空！");
    else
    {

        //在数据库中进行查询验证
        bool login = U.compareUser(user,pwd);
        if(login)
        {
            w.L.addLog(user,1);
            w.getLoginUser(user);
            w.show();
            w.taskViewer();
            this->close();
            emit exitWelcome();
        }
        else
            QMessageBox::warning(NULL,"Error","用户名或密码错误！！！");
    }
}
void login::closeEvent(QCloseEvent *)
{
    emit exitLogin();
}
