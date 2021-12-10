#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


namespace Ui {
class serialCom;
}

class serialCom : public QWidget
{
    Q_OBJECT

public:
    explicit serialCom(QWidget *parent = nullptr);

    void initMycom();

    ~serialCom();

private slots:
    void on_openMyComBtn_clicked();

    void on_closeMyComBtn_clicked();

    void on_sendMsgBtn_clicked();

    void readMyCom();

    void on_pushButton_clear_clicked();

private:

    Ui::serialCom *ui;

    QSerialPort myCom;

};

#endif // SERIALCOM_H
