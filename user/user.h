#ifndef USER_H
#define USER_H

#include <QObject>
#include <database/dataBase.h>

class user : public QObject, public dataBase
{
    Q_OBJECT
public:
    explicit user(QObject *parent = nullptr);

signals:

public slots:
    bool compareUser(QString s1, QString s2);
    int setUser(QString name, QString pwd);

};

#endif // USER_H
