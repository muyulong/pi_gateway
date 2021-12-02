#include "regist.h"
#include "ui_regist.h"

regist::regist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::regist)
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    ui->setupUi(this);
}

regist::~regist()
{
    delete ui;
}

void regist::on_pushButton_register_clicked()
{
    QString user;
    QString pwd,pwd2;
    user = ui->username->text();
    pwd = ui->password->text();
    pwd2=ui->password_2->text();
    if(user == "")
        QMessageBox::warning(this,"","用户名不能为空！");
    else if(pwd == "")
        QMessageBox::warning(this,"","密码不能为空！");
    else if(pwd2== "")
        QMessageBox::warning(this,"","确认密码不能为空！");
    else if(!(pwd==pwd2))
        QMessageBox::warning(this,"","两次输入密码必须相同！");
    else
    {
        int reg = U.setUser(user,pwd);
        if(reg==1)
        {
            QMessageBox::information(NULL, "注册成功", "注册成功！！！", QMessageBox::Yes);
            this->close();
        }
        else if(reg==2)
            QMessageBox::warning(NULL,"Error","用户名重复！！！");
        else if (reg==0)
            QMessageBox::warning(NULL,"Error","注册失败，请重试！！！");
    }
}
void regist::closeEvent(QCloseEvent *)
  {
     emit exitRegist();
 }
