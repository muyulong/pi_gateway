#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QSqlQuery>
#include<QMessageBox>
#include <QCloseEvent>


using namespace std;

class dataBase
{
public:
    dataBase();
    void initDatebase();
    void createTable(QString  tableName,QString columnName[],QString dataType[],int columnNum);
    bool isTableExist(QSqlQuery & query, QString table);
    int sqlSize(QSqlQuery query);

    QSqlDatabase db;
    QSqlQuery query;

    ~dataBase();

private:


};

#endif // DATABASE_H
