#include "serialcom.h"
#include "ui_serialcom.h"

serialCom::serialCom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serialCom)
{
    ui->setupUi(this);
    this->initMycom();
}

serialCom::~serialCom()
{
    delete ui;
}

void serialCom::initMycom()
{
    ui->closeMyComBtn->setEnabled(false);
    ui->sendMsgBtn->setEnabled(false);
    //重置ComboBox内容
    ui->portNameComboBox->clear();
    ui->baudRateComboBox->clear();
    ui->dataBitsComboBox->clear();
    ui->parityComboBox->clear();
    ui->stopBitsComboBox->clear();
    ui->flowComboBox->clear();
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->portNameComboBox->addItem(serial.portName());
            serial.close();
        }
    }
    ui->baudRateComboBox->addItems(QStringList()<<"1200"<<"2400"<<"4800"<<"9600"<<"19200"<<"38400"<<"57600"<<"115200");
    ui->dataBitsComboBox->addItems(QStringList()<<"5"<<"6"<<"7"<<"8");
    ui->parityComboBox->addItems(QStringList()<<"奇"<<"偶"<<"无");
    ui->stopBitsComboBox->addItems(QStringList()<<"1"<<"1.5"<<"2");
    ui->flowComboBox->addItems(QStringList()<<"无"<<"硬件"<<"软件");
}

//另读串口函数
void serialCom::readMyCom()
{//读串口函数
    QByteArray temp=myCom.readAll();
    //读取串口缓冲区的所有数据给临时变量temp
    ui->textBrowser->insertPlainText("[in]:"+temp+"\n");
    //将串口的数据显示在窗口的文本浏览器中
}

void serialCom::on_openMyComBtn_clicked()

{
    QString portName = ui->portNameComboBox->currentText(); //获取串口名
    myCom.setPortName(portName);
    //定义串口对象，并传递参数，在构造函数里对其进行初始化
    myCom.open(QIODevice::ReadWrite); //打开串口
    //根据组合框内容对串口进行设置
    switch(ui->baudRateComboBox->currentText().toInt())
    {
    case 1200:
        myCom.setBaudRate(QSerialPort::Baud1200);
        break;
    case 2400:
        myCom.setBaudRate(QSerialPort::Baud2400);
        break;
    case 4800:
        myCom.setBaudRate(QSerialPort::Baud4800);
        break;
    case 9600:
        myCom.setBaudRate(QSerialPort::Baud9600);
        break;
    case 19200:
        myCom.setBaudRate(QSerialPort::Baud19200);
        break;
    case 38400:
        myCom.setBaudRate(QSerialPort::Baud38400);
        break;
    case 57600:
        myCom.setBaudRate(QSerialPort::Baud57600);
        break;
    case 115200:
        myCom.setBaudRate(QSerialPort::Baud115200);
        break;
    default:
        break;
    }
    //设置波特率
    switch(ui->dataBitsComboBox->currentText().toInt())
    {
    case 5:
        myCom.setDataBits(QSerialPort::Data5);
        break;
    case 6:
        myCom.setDataBits(QSerialPort::Data6);
        break;
    case 7:
        myCom.setDataBits(QSerialPort::Data7);
        break;
    case 8:
        myCom.setDataBits(QSerialPort::Data8);
        break;
    default:
        break;
    }
    //设置数据位
    if(ui->parityComboBox->currentText()==tr("无"))
        myCom.setParity(QSerialPort::NoParity);
    else if(ui->parityComboBox->currentText()==tr("奇"))
        myCom.setParity(QSerialPort::OddParity);
    else if(ui->parityComboBox->currentText()==tr("偶"))
        myCom.setParity(QSerialPort::EvenParity);
    //设置奇偶校验
    if(ui->stopBitsComboBox->currentText()==tr("1"))
        myCom.setStopBits(QSerialPort::OneStop);
    else if(ui->stopBitsComboBox->currentText()==tr("1.5"))
        myCom.setStopBits(QSerialPort::OneAndHalfStop);
    else if(ui->stopBitsComboBox->currentText()==tr("2"))
        myCom.setStopBits(QSerialPort::TwoStop);
    //设置停止位
    if(ui->flowComboBox->currentText()==tr("无"))
        myCom.setFlowControl(QSerialPort::NoFlowControl);
    else if(ui->flowComboBox->currentText()==tr("硬件"))
        myCom.setFlowControl(QSerialPort::HardwareControl);
    else if(ui->flowComboBox->currentText()==tr("软件"))
        myCom.setFlowControl(QSerialPort::SoftwareControl);
    //设置数据流控制，我们使用无数据流控制的默认设置
    //myCom.setTimeout(500); //设置延时
    connect(&myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
    //信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作
    ui->openMyComBtn->setEnabled(false); //打开串口后“打开串口”按钮不可用
    ui->closeMyComBtn->setEnabled(true); //打开串口后“关闭串口”按钮可用
    ui->sendMsgBtn->setEnabled(true); //打开串口后“发送数据”按钮可用
    ui->baudRateComboBox->setEnabled(false); //设置各个组合框不可用
    ui->dataBitsComboBox->setEnabled(false);
    ui->parityComboBox->setEnabled(false);
    ui->stopBitsComboBox->setEnabled(false);
    ui->portNameComboBox->setEnabled(false);
     ui->flowComboBox->setEnabled(false);
}
void serialCom::on_closeMyComBtn_clicked()
{
    myCom.close();
    ui->openMyComBtn->setEnabled(true); //关闭串口后“打开串口”按钮可用
    ui->closeMyComBtn->setEnabled(false); //关闭串口后“关闭串口”按钮不可用
    ui->sendMsgBtn->setEnabled(false); //关闭串口后“发送数据”按钮不可用
    ui->baudRateComboBox->setEnabled(true); //设置各个组合框可用
    ui->dataBitsComboBox->setEnabled(true);
    ui->parityComboBox->setEnabled(true);
    ui->stopBitsComboBox->setEnabled(true);
    ui->portNameComboBox->setEnabled(true);
    ui->flowComboBox->setEnabled(true);
}

void serialCom::on_sendMsgBtn_clicked()
{
    myCom.write(ui->sendMsgLineEdit->text().toLatin1());
    ui->textBrowser->insertPlainText("[out]:"+ui->sendMsgLineEdit->text()+"\n");
}

void serialCom::on_pushButton_clear_clicked()
{
    ui->textBrowser->clear();
}
