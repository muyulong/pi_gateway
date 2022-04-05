#include "user.h"

user::user(QObject *parent) : QObject(parent)
{

}

bool user::compareUser(QString s1, QString s2)
{
    //在数据库中检索s1对应的结果串，然后与s2进行比对
    QSqlQuery query(db);
    QString search_sql = "select pwd from userInfo where name=(?)";
    query.prepare(search_sql);
    query.addBindValue(s1);

    if (!query.exec())
    {
        qDebug() << "Error: Fail to Search." << query.lastError();
    }
    else
    {
        qDebug() << "Search Success !";
    }

    //报错： QSqlQuery::value: not positioned on a valid record
    QString pass;

    if (query.next())
    {
        pass = query.value(0).toString();
    }
    if (s2 == pass)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Driver not load原因： 是因为QSQLQuery对象没有和db关联

int user::setUser(QString name, QString pwd)
{

    query = QSqlQuery(db);
    // QString insert_sql = "insert into userInfo values (?, ?)";
    QString same = QString("select * from userInfo where name='%1' ").arg(name);
    // query.prepare(insert_sql);
    query.prepare("INSERT INTO userInfo (name, pwd) "
                  "VALUES (?, ?)");
    query.addBindValue(name);
    query.addBindValue(pwd);
    if (query.exec())
    {
        qDebug() << "inserted success!";
        return 1;
    }
    else if (query.exec(same) && query.first())
    {
        return 2;
    }
    else
    {
        qDebug() << query.lastError();
        // return 0;
    }
    return 0;
}
