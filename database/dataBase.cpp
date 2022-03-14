#include "dataBase.h"

dataBase::dataBase()
{
}

void dataBase::initDatebase()
{
    if (QSqlDatabase::contains("first"))
    {
        db = QSqlDatabase::database("first");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE", "first");
        db.setDatabaseName("test.db");
    }
    if (db.open())
    {
        qDebug() << "connect database success!";
    }
    else
    {
        qDebug() << "connect database failed!";
    }
}

void dataBase::createTable(QString tableName, QString columnName[], QString dataType[], int columnNum)
{
    query = QSqlQuery(db);
    if (isTableExist(query, tableName))
    {
        qDebug() << "Table has created!";
    }
    else
    {
        QString create_table = "create table " + tableName + "(" + columnName[0] + " " + dataType[0] + ")";
        query.exec(create_table);
        qDebug() << create_table;
        // qDebug() << query.lastError();
        for (int i = 1; i < columnNum; i++)
        {
            QString insert_column = "alter table " + tableName + " add column " + columnName[i] + " " + dataType[i];
            query.exec(insert_column);
            qDebug() << insert_column;
            // qDebug() << query.lastError();
        }
        // QString insert_column = "(name varchar, pwd varchar)";
        qDebug() << "Table created!";
    }
}

bool dataBase::isTableExist(QSqlQuery &query, QString table)
{
    QString sql = QString("select * from '%1'").arg(table);
    query.exec(sql);
    return query.next();
}

int dataBase::sqlSize(QSqlQuery query)
{
    int initialPos = query.at();
    // Very strange but for no records .at() returns -2
    int pos = 0;
    if (query.last())
        pos = query.at() + 1;
    else
        pos = 0;
    // Important to restore initial pos
    query.seek(initialPos);
    return pos;
}
// sqlite不支持直接读取结果大小
// https://stackoverflow.com/questions/26495049/qsqlquery-size-always-returns-1

dataBase::~dataBase()
{
    db.close();
}
