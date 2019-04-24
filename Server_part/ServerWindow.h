#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QWidget>
#include "TCP_part/TCPServer.h"
#include "DataBase_patr/DataBaseManager.h"
#include "DataModel/UserInfoModel.h"
#include <QGraphicsDropShadowEffect>
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
    void SetUserInfoModel(UserInfoModel *userInfoModel);
    void InitUI();
    void SetTopBarButtonStyleDefult();

private:
    Ui::ServerWindow *ui;
    TCPServer *m_tcpServer;
    DataBaseManager *DBManager;
    UserInfoModel *m_userInfoModel;
    QGraphicsDropShadowEffect *TopBarFrameShadow;
    QString qss_Checked;
    QString qss_Unchecked;
public slots:
    void GetLoginRequest(QString LoginInfo);
    void GetRegistRequest(QString RegistInfo);
    void ToolButtonCliced();
};

#endif // SERVERWINDOW_H
