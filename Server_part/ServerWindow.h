#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QWidget>
#include "TCP_part/TCPServer.h"
#include "DataBase_patr/DataBaseManager.h"
#include "DataModel/UserInfoModel.h"
#include <DataModeView/ExamRoomModelView.h>

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
    void InitExamRoom();
private:
    Ui::ServerWindow *ui;
    TCPServer *m_tcpServer;
    DataBaseManager *DBManager;
    UserInfoModel *m_userInfoModel;
    QGraphicsDropShadowEffect *TopBarFrameShadow;
    QString qss_Checked;
    QString qss_Unchecked;
    QWidget *m_parent;
    ExamRoomModelView *ExamRoom;
    ExamChoiceQusetion *TempQuestion;

    void SetupINFOtoUI(ExamChoiceQusetion* exq);
    ExamChoiceQusetion* GetINFOfromUI();
public slots:
    void GetLoginRequest(QString LoginInfo);
    void GetRegistRequest(QString RegistInfo);
    void ToolButtonCliced();
private slots:
    void on_ExamPaperListView_clicked(const QModelIndex &index);
    void on_AllExamPapersListView_clicked(const QModelIndex &index);
    void on_AddExamQuestion_clicked();
    void on_RemoveExamItem_clicked();
    void on_SaveExamPaperToLib_clicked();
    void on_SaveExamPaper_clicked();
    void on_SaveExamQuestionToLib_clicked();
    void on_AddQuestion_clicked();
    void on_SaveQuestion_clicked();
    void on_EditQuestion_clicked();
    void on_QsestionListView_clicked(const QModelIndex &index);
    void on_DeleteQuestion_clicked();
};

#endif // SERVERWINDOW_H
