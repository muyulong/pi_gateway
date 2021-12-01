#ifndef USER_H
#define USER_H
#include<dataBase.h>

class user :public dataBase
{
public:
    user();

    bool compareUser(QString s1,QString s2);
    int setUser(QString name,QString pwd);

};

#endif // USER_H
