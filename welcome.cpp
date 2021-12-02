#include "welcome.h"
#include "ui_welcome.h"


welcome::welcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);
    connect(&r,SIGNAL(exitRegist()),this,SLOT(show()));
    connect(&l,SIGNAL(exitLogin()),this,SLOT(show()));
    connect(&l,SIGNAL(exitWelcome()),this,SLOT(close()));
}

welcome::~welcome()
{
    delete ui;
}

void welcome::on_pushButton_register_clicked()
{
     //初始化数据库和用户信息表
    QString  tableName="userInfo";
    QString columnName[2]={"name","pwd"};
    QString dataType[2]={"varchar","varchar"};
    int columnNum=2;
    //name varchar, pwd varchar
    r.U.initDatebase();
    r.U.createTable(tableName,columnName,dataType,columnNum);
    r.setModal(true);
    r.show();
    this->hide();
}


void welcome::on_pushButton_login_clicked()
{
    l.U.initDatebase();
    l.setModal(true);
    l.show();
    this->close();
}


void welcome::on_pushButton_exit_clicked()
{
    this->close();
}


