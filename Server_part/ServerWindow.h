﻿#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QWidget>
#include "TCP_part/TCPServer.h"
#include "DataBase_patr/DataBaseManager.h"
namespace Ui {
class ServerWindow;
}

class ServerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();

public:
    void SetTcpServer(TCPServer *tcp);
private:
    Ui::ServerWindow *ui;
    TCPServer *m_tcpServer;
    DataBaseManager *DBManager;
public slots:
    void GetLoginRequest(QString LoginInfo);
};

#endif // SERVERWINDOW_H