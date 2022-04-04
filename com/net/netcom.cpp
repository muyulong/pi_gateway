#include "netcom.h"
#include "ui_netcom.h"

netCom::netCom(QWidget *parent) : QWidget(parent),
    ui(new Ui::netCom)
{
    ui->setupUi(this);
    this->initNet();
}

netCom::~netCom()
{
    delete ui;
    m_tcpServer->deleteLater();
    m_tcpSocket->deleteLater();
}

void netCom::initNet()
{
    heart = new HeartBeat(this, 5000);
    connect(heart, SIGNAL(dead()), this, SLOT(onDead()));
    connect(this, SIGNAL(stopListen()), this, SLOT(onDead()));
    ui->comboBox->clear();
    QList<QHostAddress> addrList = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, addrList)
    {
        //使用IPv4地址
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
        {
            if (address.toString().contains("127.0."))
            {
                continue;
            }
            else
            {
                QString ip = address.toString();
                ui->comboBox->addItem(ip);
            }
        }
    }
    ui->lineEditPort->setText("8080");
}

//供其他函数调用的方法
//建立连接
void netCom::Start()
{
    //当前选择的ip
    QString ip = ui->comboBox->currentText();
    //端口
    int port = ui->lineEditPort->text().toInt();
    QHostAddress addr(ip);
    //监听
    m_tcpServer->listen(addr, port);
    ui->plainTextEdit->appendPlainText("**开始监听...");
    ui->plainTextEdit->appendPlainText("**服务器地址: " + m_tcpServer->serverAddress().toString());
    ui->plainTextEdit->appendPlainText("**服务器端口: " + QString::number(m_tcpServer->serverPort()));
    ui->lbListen->setText("正在监听");
    connect(m_tcpServer, &QTcpServer::newConnection, this, &netCom::on_newConnection);
}

QString netCom::getNetAdd()
{
    QString netAdd = "ip: "+ui->comboBox->currentText()+" "+"port: "+ui->lineEditPort->text();
    return netAdd;
}

void netCom::onDead()
{
    ui->plainTextEdit->appendPlainText("**停止心跳");
    heart->stop();
    if(m_tcpSocket)
    {
        m_tcpSocket->close();
    }
}

//断开连接
void netCom::Stop()
{
    if (m_tcpServer->isListening())
    {
        m_tcpServer->close();
        ui->lbListen->setText("停止监听");
        ui->plainTextEdit->appendPlainText("**停止监听**");
        emit stopListen();
    }
}

//获取传输数据
QString netCom::getData()
{
    QString result;
    QByteArray byteStr;
    while (!m_tcpSocket->atEnd()) //没有读到末尾一直读
    {
        byteStr.append(m_tcpSocket->readAll());
    }
    result.prepend(byteStr).remove(QRegExp("\\s"));
    if(result == "")
    {
        result = "empty data!";
    }
    m_msg = result;
    return result;
}
//发送数据
void netCom::sendData(QString data)
{
    ui->plainTextEdit->appendPlainText("[out]:" + data);
    m_tcpSocket->write(data.toLatin1());
}

void netCom::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

void netCom::onReadyRead()
{
    emit hasReadData();
    ui->plainTextEdit->appendPlainText("[IN]: " + m_msg);
}

void netCom::on_btnSend_clicked()
{
    QString msg = ui->lineEdit->text();
    this->sendData(msg);
    ui->plainTextEdit->appendPlainText("[out]:"+msg);
}

void netCom::on_newConnection()
{
    m_tcpSocket = m_tcpServer->nextPendingConnection();
    //connect(m_tcpSocket, &QTcpSocket::connected, this, &netCom::onConnected);
    //connect(m_tcpSocket, &QTcpSocket::disconnected, this, &netCom::onDisConnected);
    //connect(m_tcpSocket, &QTcpSocket::stateChanged, this, &netCom::onStateChanged);
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &netCom::onReadyRead);
}

void netCom::onConnected()
{
    QString msg = QString("客户端[%1:%2]已连接!").arg(m_tcpSocket->peerAddress().toString()).arg(m_tcpSocket->peerPort());
    ui->plainTextEdit->appendPlainText(msg);
    heart->beat();
    ui->plainTextEdit->appendPlainText("**开始心跳");
}

void netCom::onDisConnected()
{
    m_tcpSocket = (QTcpSocket *)this->sender();
    QString msg = QString("客户端[%1:%2]已退出!").arg(m_tcpSocket->peerAddress().toString()).arg(m_tcpSocket->peerPort());
    ui->plainTextEdit->appendPlainText(msg);
    emit onDead();
}

void netCom::onStateChanged(QAbstractSocket::SocketState socketState)
{
    switch (socketState)
    {
    case QAbstractSocket::UnconnectedState:
        ui->label_socket->setText("UnconnectedState");
        break;
    case QAbstractSocket::HostLookupState:
        ui->label_socket->setText("HostLookupState");
        break;
    case QAbstractSocket::ConnectedState:
        ui->label_socket->setText("ConnectedState");
        break;
    case QAbstractSocket::ConnectingState:
        ui->label_socket->setText("ConnectingState");
        break;
    case QAbstractSocket::BoundState:
        ui->label_socket->setText("BoundState");
        break;
    case QAbstractSocket::ClosingState:
        ui->label_socket->setText("ClosingState");
        break;
    case QAbstractSocket::ListeningState:
        ui->label_socket->setText("ListeningState");
        break;
    }
}
