#include "welcome.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QApplication a(argc, argv);
    welcome w;
    w.show();

    return a.exec();
}
