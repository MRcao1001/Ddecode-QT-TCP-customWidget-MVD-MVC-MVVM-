﻿#include "TCPServer.h"
#include "ui_TCPServer.h"

TCPServer::TCPServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TCPServer)
{
    ui->setupUi(this);
    tcpServer = new QTcpServer(this);
    ui->edtIP->setText(QNetworkInterface().allAddresses().at(1).toString());   //获取本地IP
    ui->btnConnect->setEnabled(true);
    ui->btnSend_2->setEnabled(false);

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(NewConnectionSlot()));
}

TCPServer::~TCPServer()
{
    delete ui;
}
// newConnection -> newConnectionSlot 新连接建立的槽函数
void TCPServer::NewConnectionSlot()
{
    currentClient = tcpServer->nextPendingConnection();
    tcpClient.append(currentClient);
    ui->cbxConnection->addItem(tr("%1:%2").arg(currentClient->peerAddress().toString().split("::ffff:")[1])\
            .arg(currentClient->peerPort()));
    connect(currentClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(currentClient, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
}

void TCPServer::disconnectedSlot()
{
    //由于disconnected信号并未提供SocketDescriptor，所以需要遍历寻找
    for(int i=0; i<tcpClient.length(); i++)
    {
        if(tcpClient[i]->state() == QAbstractSocket::UnconnectedState)
        {
            // 删除存储在combox中的客户端信息
            ui->cbxConnection->removeItem(ui->cbxConnection->findText(tr("%1:%2")\
                                                                      .arg(tcpClient[i]->peerAddress().toString().split("::ffff:")[1])\
                                          .arg(tcpClient[i]->peerPort())));
            // 删除存储在tcpClient列表中的客户端信息
            tcpClient[i]->destroyed();
            tcpClient.removeAt(i);
        }
    }
}

void TCPServer::ReadData()
{
    // 由于readyRead信号并未提供SocketDecriptor，所以需要遍历所有客户端
    for(int i=0; i<tcpClient.length(); i++)
    {
        QByteArray buffer = tcpClient[i]->readAll();
        if(buffer.isEmpty())    continue;

        static QString IP_Port, IP_Port_Pre;
        IP_Port = tr("[%1:%2]:").arg(tcpClient[i]->peerAddress().toString().split("::ffff:")[1])\
                .arg(tcpClient[i]->peerPort());

        // 若此次消息的地址与上次不同，则需显示此次消息的客户端地址
        if(IP_Port != IP_Port_Pre)
            ui->edtRecv_2->append(IP_Port);

        ui->edtRecv_2->append(buffer);

        //更新ip_port
        IP_Port_Pre = IP_Port;
    }
}

void TCPServer::on_btnConnect_clicked()
{
    if(ui->btnConnect->text()=="监听")
    {
        bool ok = tcpServer->listen(QHostAddress::Any, ui->edtPort->text().toInt());
        if(ok)
        {
            ui->btnConnect->setText("断开");
            ui->btnSend_2->setEnabled(true);
        }
    }
    else
    {
        for(int i=0; i<tcpClient.length(); i++)//断开所有连接
        {
            tcpClient[i]->disconnectFromHost();
//            bool ok = tcpClient[i]->waitForDisconnected(1000);
//            if(!ok)
//            {
//                // 处理异常
//                qDebug()<<"断开所有连接异常";
//            }
//            tcpClient.removeAt(i);  //从保存的客户端列表中取去除
        }
        tcpServer->close();     //不再监听端口
        ui->btnConnect->setText("监听");
        ui->btnSend_2->setEnabled(false);
    }
}

void TCPServer::on_btnSend_2_clicked()
{
    QString data = ui->edtSend_2->toPlainText();
    if(data == "")  return;    // 文本输入框为空时
    //全部连接
    if(ui->cbxConnection->currentIndex() == 0)
    {
        for(int i=0; i<tcpClient.length(); i++)
            tcpClient[i]->write(data.toLatin1()); //qt5除去了.toAscii()
    }
    //指定连接
    else
    {
        QString clientIP = ui->cbxConnection->currentText().split(":")[0];
        int clientPort = ui->cbxConnection->currentText().split(":")[1].toInt();
        //        qDebug() << clientIP;
        //        qDebug() << clientPort;
        for(int i=0; i<tcpClient.length(); i++)
        {
            if(tcpClient[i]->peerAddress().toString().split("::ffff:")[1]==clientIP\
                    && tcpClient[i]->peerPort()==clientPort)
            {
                tcpClient[i]->write(data.toLatin1());
                return; //ip:port唯一，无需继续检索
            }
        }
    }
}

void TCPServer::on_btnClear_clicked()
{
    ui->edtRecv_2->clear();
}
