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
#include <QVBoxLayout>
namespace Ui {
class Decode;
}

class Decode :public DecodeBaseWindow
{
    Q_OBJECT

public:
    explicit Decode(QWidget *parent = 0);
    ~Decode();
    void InitUI();
    void InitObject();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();
    void on_CreateExamRoomSuccess_emit();
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
};

#endif // DECODE_H
