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
}

void netCom::initNet()
{
    //--

    heart = new HeartBeat(this, 5000);
    // socket = new StringTcpSocket(this);
    // connect(m_tcpSocket, SIGNAL(dataRead(QString)),this,   SLOT(onDataRead(QString)));
    connect(heart, SIGNAL(dead()), this, SLOT(onDead()));
    connect(this, SIGNAL(stopListen()), this, SLOT(onDead()));
    //--

    //重置ComboBox内容
    ui->comboBox->clear();
    //定义最大连接数
    tcpSocket_Max = 2;
    //--------------------------------------------
    //本地主机名

    QString hostName = QHostInfo::localHostName();

    //本机IP地址
    QHostInfo hostInfo = QHostInfo::fromName(hostName);

    // IP地址列表
    QList<QHostAddress> addrList = hostInfo.addresses();
    for (int i = 0; i < addrList.count(); i++)
    {
        QHostAddress host = addrList.at(i);

        if (QAbstractSocket::IPv4Protocol == host.protocol())
        {
            QString ip = host.toString();
            ui->comboBox->addItem(ip);
        }
    }

    m_tcpServer = new QTcpServer(this);
    connect(m_tcpServer, &QTcpServer::newConnection, this, &netCom::on_newConnection);
    ui->lineEditPort->setText("8080");

    ui->btnStop->setEnabled(false);
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
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
    ui->lbListen->setText("正在监听");
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
        ui->btnStart->setEnabled(true);
        ui->btnStop->setEnabled(false);
        ui->lbListen->setText("停止监听");
        ui->plainTextEdit->appendPlainText("**停止监听**");
        // m_tcpSocket->close();
        emit stopListen();
    }
}

//获取传输数据
QString netCom::getData()
{
    QString result;
    for (int i = 0; i < tcpSocketList.count(); i++)
    {
        QTcpSocket *tcpSocket = tcpSocketList.at(i);
        while (!tcpSocket->atEnd()) //没有读到末尾一直读
        {
            result.append(QString(tcpSocket->readAll()));
        }
        // result.append(QString("\n"));
    }
    return result;
}

//断开连接和发送消息要对多连接状态进行处理
//切记切记，不然会闪退
//已解决

//发送数据
void netCom::sendData(QString data)
{
    for (int i = 0; i < tcpSocketList.length(); i++) //遍历客户端
    {
        tcpSocketList.at(i)->write(data.toLatin1());
    }
    ui->plainTextEdit->appendPlainText("[out]" + data);
}

//--------------------------
//网络调试

void netCom::on_btnStart_clicked()
{
    this->Start();
}

void netCom::on_btnStop_clicked()
{
    this->Stop();
}

void netCom::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

void netCom::onReadyRead()
{
    emit hasReadData();
    ui->plainTextEdit->appendPlainText("[in] " + this->getData());
}

void netCom::on_btnSend_clicked()
{
    QString msg = ui->lineEdit->text();
    this->sendData(msg);
    // ui->plainTextEdit->appendPlainText("[out]"+msg);
}

void netCom::on_newConnection()
{

    if (tcpSocketList.count() < tcpSocket_Max)
    {
        // QThread *thread = new QThread;        //不可以有parent
        // connect(thread, &QThread::finished, thread, &QThread::deleteLater);    //线程结束后自动删除自己

        m_tcpSocket = m_tcpServer->nextPendingConnection();
        connect(m_tcpSocket, &QTcpSocket::connected, this, &netCom::onConnected);
        connect(m_tcpSocket, &QTcpSocket::disconnected, this, &netCom::onDisConnected);
        connect(m_tcpSocket, &QTcpSocket::stateChanged, this, &netCom::onStateChanged);
        connect(m_tcpSocket, &QTcpSocket::readyRead, this, &netCom::onReadyRead);

        tcpSocketList.append(m_tcpSocket);

        QString msg = QString("客户端[%1:%2]已连接!").arg(m_tcpSocket->peerAddress().toString()).arg(m_tcpSocket->peerPort());
        ui->plainTextEdit->appendPlainText(msg);

        // m_tcpSocket->moveToThread(thread);            //注意,使用moveToThread方法将socket转移到新线程中
        // m_heartbeat->start();                 //开始心跳
        heart->beat();

        ui->plainTextEdit->appendPlainText("**开始心跳");
        // thread->start();

        // ui->plainTextEdit->appendPlainText("** client socket connected");
        // ui->plainTextEdit->appendPlainText("** peer address: "+m_tcpSocket->peerAddress().toString());
        // ui->plainTextEdit->appendPlainText("** peer port: "+QString::number(m_tcpSocket->peerPort()));
    }
    else
    {
        m_tcpSocket = m_tcpServer->nextPendingConnection();
        m_tcpSocket->close();
        QString str = QString("最多建立%1个连接！").arg(tcpSocket_Max);
        QMessageBox::information(this, "警告", str, QMessageBox::Ok, QMessageBox::NoButton);
    }
}

void netCom::onConnected()
{
    QString msg = QString("客户端[%1:%2]已连接!").arg(m_tcpSocket->peerAddress().toString()).arg(m_tcpSocket->peerPort());
    ui->plainTextEdit->appendPlainText(msg);

    // ui->plainTextEdit->appendPlainText("** client socket connected");
    // ui->plainTextEdit->appendPlainText("** peer address: "+m_tcpSocket->peerAddress().toString());
    // ui->plainTextEdit->appendPlainText("** peer port: "+QString::number(m_tcpSocket->peerPort()));
}

void netCom::onDisConnected()
{
    m_tcpSocket = (QTcpSocket *)this->sender();
    QString msg = QString("客户端[%1:%2]已退出!").arg(m_tcpSocket->peerAddress().toString()).arg(m_tcpSocket->peerPort());
    ui->plainTextEdit->appendPlainText(msg);

    // m_heartbeat->stop();
    emit onDead();

    //删除断开的客户端
    for (int i = 0; i < tcpSocketList.length(); i++)
    {
        if (tcpSocketList.at(i)->peerAddress() == m_tcpSocket->peerAddress())
        {
            if (tcpSocketList.at(i)->peerPort() == m_tcpSocket->peerPort())
            {
                tcpSocketList.removeAt(i);
                break;
            }
        }
    }
    // ui->plainTextEdit->appendPlainText("** client socket disconnected");
    // m_tcpSocket->deleteLater();
    // m_tcpServer->close();
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
