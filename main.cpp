#include "welcome/welcome.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QApplication a(argc, argv);

    //QFile qss(":qss/Aqua.qss");
    QFile qss(":qss/lightgray.qss");
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

    //
//    QString strMsg="h";
//    char* chMsg;
//    QByteArray baMsg = strMsg.toLatin1();
//    chMsg=baMsg.data();
//    QByteArray byte_nMsg = nMsg.toLatin1();
//    for(int i = 0; i < nMsg.size(); i++)
//    {
//        qDebug() << int(byte_nMsg.at(i));//输出
//    }
//    char bitMask = 1 << 7;
//         for (int i = 0; i < 8; i++)
//         {
//             qDebug()  << (bitMask & chMsg[i] ? 1 : 0);
//             chMsg[i] = chMsg[i] << 1;
//         }
    //

    welcome w;
    w.show();

    return a.exec();
}
