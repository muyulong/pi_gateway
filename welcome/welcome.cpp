#include "welcome.h"
#include "ui_welcome.h"

welcome::welcome(QWidget *parent) : QWidget(parent),
                                    ui(new Ui::welcome)
{
    ui->setupUi(this);

    connect(m_regist,&regist::exitRegist,this,&welcome::show);
    connect(m_login,&login::exitLogin,this,&welcome::show);
    connect(m_login,&login::exitWelcome,this,&welcome::close);
    connect(m_regist,&regist::setUser,m_user,&user::setUser);
    connect(m_login,&login::compareUser,m_user,&user::compareUser);
}

welcome::~welcome()
{
    delete ui;
}

void welcome::on_pushButton_register_clicked()
{
    //初始化数据库和用户信息表
    QString tableName = "userInfo";
    QString columnName[2] = {"name", "pwd"};
    QString dataType[2] = {"varchar", "varchar"};
    int columnNum = 2;
    // name varchar, pwd varchar
    m_user->initDatebase();
    m_user->createTable(tableName, columnName, dataType, columnNum);
    m_regist->setModal(true);
    m_regist->show();
    this->hide();
}

void welcome::on_pushButton_login_clicked()
{
    m_user->initDatebase();
    m_login->setModal(true);
    m_login->show();
    this->close();
}

void welcome::on_pushButton_exit_clicked()
{
    this->close();
}
