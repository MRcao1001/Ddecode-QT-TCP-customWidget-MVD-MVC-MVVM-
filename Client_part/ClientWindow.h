#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QString>
#include "TCP_part/TCPClient.h"
#include <DataModeView/ExamRoomModelView.h>
#include "ExmaPaperwindow.h"
#include "AnswerSheet.h"
#include "LeftBar.h"
namespace Ui {
class ClientWindow;
}

class ClientWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = 0);
    ~ClientWindow();
    void SetClient(TCPClient *tcp);
    bool InitFinish = false;
private:
    Ui::ClientWindow *ui;
    LeftBar *leftbar;
    TCPClient *m_tcpclient;
    // 考场模型
    ExamRoomModelView *ExamRoom;
    ExmaPaperwindow *examPaperWindow;
    AnswerSheet *answerSheet;
    void InitUI();
    void InitExamRoom();
    void SetConnect();

public slots:
    // 考试开始执行函数
    void ExaminationBegins(QString ExamRoomInfo);
    // 结束考试执行函数
    void markExamPapers();
private slots:
    void on_HandInHand_clicked();
};

#endif // CLIENTWINDOW_H
