#include "netcom.h"
#include "ui_netcom.h"

netCom::netCom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::netCom)
{
    ui->setupUi(this);
    this->initNet();
}

netCom::~netCom()
{
    delete ui;
}

void netCom::initNet()
{
        //--------------------------------------------
        //本地主机名
        QString hostName = QHostInfo::localHostName();

        //本机IP地址
        QHostInfo hostInfo = QHostInfo::fromName(hostName);

        //IP地址列表
        QList<QHostAddress> addrList = hostInfo.addresses();
        for(int i=0;i<addrList.count();i++)
        {
            QHostAddress host = addrList.at(i);

            if(QAbstractSocket::IPv4Protocol == host.protocol())
            {
                QString ip = host.toString();
                ui->comboBox->addItem(ip);
            }
        }

        m_tcpServer = new QTcpServer(this);
        connect(m_tcpServer,&QTcpServer::newConnection,this,&netCom::on_newConnection);
        ui->lineEditPort->setText("8080");
}

//--------------------------
//网络调试

void netCom::on_btnStart_clicked()
{
    //当前选择的ip
    QString ip = ui->comboBox->currentText();

    //端口
    int port = ui->lineEditPort->text().toInt();

    QHostAddress addr(ip);

    //监听
    m_tcpServer->listen(addr,port);

    ui->plainTextEdit->appendPlainText("**开始监听...");

    ui->plainTextEdit->appendPlainText("**服务器地址: "+m_tcpServer->serverAddress().toString());

    ui->plainTextEdit->appendPlainText("**服务器端口: "+QString::number(m_tcpServer->serverPort()));

    ui->btnStart->setEnabled(false);

    ui->btnStop->setEnabled(true);

    ui->lbListen->setText("正在监听");
}

void netCom::on_btnStop_clicked()
{
    if(m_tcpServer->isListening())
    {
        m_tcpServer->close();
        ui->btnStart->setEnabled(true);
        ui->btnStop->setEnabled(false);
        ui->lbListen->setText("停止监听");
        ui->plainTextEdit->appendPlainText("**停止监听**");
    }
}

void netCom::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

void netCom::on_newConnection()
{
    m_tcpSocket = m_tcpServer->nextPendingConnection();
    connect(m_tcpSocket,&QTcpSocket::connected,this,&netCom::onConnected);
    connect(m_tcpSocket,&QTcpSocket::disconnected,this,&netCom::onDisConnected);
    connect(m_tcpSocket,&QTcpSocket::stateChanged,this,&netCom::onStateChanged);
    connect(m_tcpSocket,&QTcpSocket::readyRead,this,&netCom::onReadyRead);

    ui->plainTextEdit->appendPlainText("** client socket connected");
    ui->plainTextEdit->appendPlainText("** peer address: "+m_tcpSocket->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("** peer port: "+QString::number(m_tcpSocket->peerPort()));
}

void netCom::onConnected()
{
    ui->plainTextEdit->appendPlainText("** client socket connected");
    ui->plainTextEdit->appendPlainText("** peer address: "+m_tcpSocket->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("** peer port: "+QString::number(m_tcpSocket->peerPort()));
}

void netCom::onDisConnected()
{
    ui->plainTextEdit->appendPlainText("** client socket disconnected");
    m_tcpSocket->deleteLater();
}

void netCom::onStateChanged(QAbstractSocket::SocketState socketState)
{
    switch (socketState)
    {
    case QAbstractSocket::UnconnectedState:
        ui->lbListen->setText("UnconnectedState");break;
    case QAbstractSocket::HostLookupState:
        ui->lbListen->setText("HostLookupState");break;
    case QAbstractSocket::ConnectedState:
        ui->lbListen->setText("ConnectedState");break;
    case QAbstractSocket::ConnectingState:
        ui->lbListen->setText("ConnectingState");break;
    case QAbstractSocket::BoundState:
        ui->lbListen->setText("BoundState");break;
    case QAbstractSocket::ClosingState:
        ui->lbListen->setText("ClosingState");break;
    case QAbstractSocket::ListeningState:
        ui->lbListen->setText("ListeningState");break;
    }

}

void netCom::onReadyRead()
{
    while(m_tcpSocket->canReadLine())
    {
        ui->plainTextEdit->appendPlainText("[in] "+m_tcpSocket->readLine());
    }
}

void netCom::on_btnSend_clicked()
{
    QString msg =ui->lineEdit->text();
    ui->plainTextEdit->appendPlainText("[out]"+msg);
    QByteArray str = msg.toUtf8();
    str.append('\n');
    m_tcpSocket->write(str);
}

