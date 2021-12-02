#include "welcome.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("GBK");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    welcome w;
    w.show();

    return a.exec();
}
