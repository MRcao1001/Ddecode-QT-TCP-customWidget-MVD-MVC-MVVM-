#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include "TCP_part/TCPClient.h"
#include <DataModeView/ExamRoomModelView.h>
#include "ExmaPaperwindow.h"
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
private:
    Ui::ClientWindow *ui;
    LeftBar *leftbar;
    TCPClient *m_tcpclient;
    // 考场模型
    ExamRoomModelView *ExamRoom;
    ExmaPaperwindow *examPaperWindow;
    void InitUI();
    void SetConnect();
    // 考试开始执行函数
    void ExaminationBegins(QString ExamRoomInfo);
};

#endif // CLIENTWINDOW_H
