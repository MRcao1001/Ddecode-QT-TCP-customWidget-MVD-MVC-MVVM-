#include "TCPClient.h"
#include "ui_TCPClient.h"

TCPClient::TCPClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TCPClient)
{
    ui->setupUi(this);
    //初始化TCP客户端
    tcpClient = new QTcpSocket(this);   //实例化tcpClient
    tcpClient->abort();                 //取消原有连接
    ui->btnConnect->setEnabled(true);
    ui->btnSend->setEnabled(false);

    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), \
            this, SLOT(ReadError(QAbstractSocket::SocketError)));
}

TCPClient::~TCPClient()
{
    delete ui;
}

void TCPClient::ConnectToServer(QString Ip, quint16 Port)
{

    tcpClient->connectToHost(Ip, Port);
    if (tcpClient->waitForConnected(1000))  // 连接成功则进入if{}
    {
        ui->btnConnect->setText("断开");
        ui->btnSend->setEnabled(true);
    }
    else {
        QMessageBox message(QMessageBox::NoIcon, "提示", "无法连接到服务器，请检查网络连接");
        message.setIconPixmap(QPixmap(":/img/Tip.png"));
        message.exec();
    }
}

void TCPClient::DisConnectToServer()
{
    tcpClient->disconnectFromHost();
    if (tcpClient->state() == QAbstractSocket::UnconnectedState \
            || tcpClient->waitForDisconnected(1000))  //已断开连接则进入if{}
    {
        ui->btnConnect->setText("连接");
        ui->btnSend->setEnabled(false);
    }
}

void TCPClient::ReadData()
{
    QByteArray buffer = tcpClient->readAll();
    if(buffer == "Licence_Is_Right")
    {
        emit LicenceResult(0);
    }
    if(buffer == "Licence_Is_False")
    {
        emit LicenceResult(-1);
    }
    if(!buffer.isEmpty())
    {
        ui->edtRecv->append(buffer);
    }
}

void TCPClient::ReadError(QAbstractSocket::SocketError)
{
    tcpClient->disconnectFromHost();
    ui->btnConnect->setText(tr("连接"));
    QMessageBox msgBox;
    msgBox.setText(tr("failed to connect server because %1").arg(tcpClient->errorString()));
    msgBox.exec();
}

void TCPClient::SendInfo(const char* Licence)
{
    if(tcpClient->write(Licence) == -1)
    {
        qDebug()<<"Send Error";
    }
}

void TCPClient::on_btnConnect_clicked()
{
    if(ui->btnConnect->text()=="连接")
    {
        tcpClient->connectToHost(ui->edtIP->text(), ui->edtPort->text().toInt());
        if (tcpClient->waitForConnected(1000))  // 连接成功则进入if{}
        {
            ui->btnConnect->setText("断开");
            ui->btnSend->setEnabled(true);
        }
    }
    else
    {
        tcpClient->disconnectFromHost();
        if (tcpClient->state() == QAbstractSocket::UnconnectedState \
                || tcpClient->waitForDisconnected(1000))  //已断开连接则进入if{}
        {
            ui->btnConnect->setText("连接");
            ui->btnSend->setEnabled(false);
        }
    }
}

void TCPClient::on_btnSend_clicked()
{
    QString data = ui->edtSend->toPlainText();
    if(data != "")
    {
        tcpClient->write(data.toLatin1()); //qt5出去了.toAscii()
    }
}

void TCPClient::on_pushButton_clicked()
{
    ui->edtRecv->clear();
}
