#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <QObject>
#include <QTimer>
#include <QDateTime>

//--
class HeartBeat : public QObject

{
    Q_OBJECT
public:
    HeartBeat(QObject *parent, int interval)
        : QObject(parent)
    {
        checkTimer = new QTimer(this);
        checkTimer->setInterval(interval);
        last = QDateTime::currentDateTime();
        connect(checkTimer, SIGNAL(timeout()), this, SLOT(check()));
    }
    ~HeartBeat()
    {
        delete checkTimer;
    }
    void beat()
    {
        if (!checkTimer->isActive())
            checkTimer->start();
        last = QDateTime::currentDateTime();
    }
    void stop()
    {
        if (checkTimer->isActive())
            checkTimer->stop();
        last = QDateTime::currentDateTime();
    }
signals:
    void dead();
private slots:
    void check()
    {
        if (last.secsTo(QDateTime::currentDateTime()) >= 5)
        {
            checkTimer->stop();
            emit dead();
        }
    }

private:
    QDateTime last;
    QTimer *checkTimer;
};
//--

#endif // HEARTBEAT_H
