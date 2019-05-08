#ifndef DECODE_H
#define DECODE_H

#include <QWidget>
#include "DecodeBaseWindow.h"
#include "DataBase_patr/DataBaseManager.h"
#include "DataModel/UserInfoModel.h"
#include "DataDelegate/userinfodelegate.h"
#include "DataModel/ExamPaperModel.h"
#include "DataDelegate/ExamPaperDelegate.h"
#include "TCP_part/TCPClient.h"
#include "TCP_part/TCPServer.h"
#include "LoginAndRegWindow.h"
#include "Server_part/ServerWindow.h"
#include "Client_part/ClientWindow.h"
#include <QVBoxLayout>
namespace Ui {
class Decode;
}

class Decode :public DecodeBaseWindow
{
    Q_OBJECT

public:
    explicit Decode(QWidget *parent = nullptr);
    ~Decode();
    void InitUI();
    void InitObject();
public slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();
    // 创建考场成功-显示考场界面
    void on_CreateExamRoomSuccess_emit();
    // 登录成功-显示用户界面
    void on_LoginSuccessfuly_emit(QString LoginInfo);
private:
    Ui::Decode *ui;
    UserInfoModel *m_userInfoModel;
    UserInfoDelegate *m_userInfoDelegate;

    ExamPaperModel *m_examPaperModel;
    ExamPaperDelegate *m_examPaperDelegate;
    DataBaseManager *DBManager;

    TCPClient *m_tcpClient;
    TCPServer *m_tcpServer;

    LoginAndRegWindow *LARW;
    ServerWindow *SW;
    ClientWindow *CW;
};

#endif // DECODE_H
