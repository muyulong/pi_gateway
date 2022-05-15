#include "welcome/welcome.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss(":qss/myTheme.qss");
    //QFile qss(":qss/Aqua.qss");
    //QFile qss(":qss/lightgray.qss");
    //QFile qss(":qss/flatWhite.qss");
    //QFile qss("");
    if( qss.open(QFile::ReadOnly))
    {
        qDebug("open success");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    else
    {
        qDebug("Open failed");
    }

    welcome w;
    w.show();

    return a.exec();
}
