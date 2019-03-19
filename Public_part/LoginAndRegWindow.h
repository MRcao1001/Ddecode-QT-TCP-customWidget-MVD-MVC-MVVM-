#ifndef LOGINANDREGWINDOW_H
#define LOGINANDREGWINDOW_H

#include <QWidget>
#include "TCP_part/TCPClient.h"
#include "DecodeAnimation.h"
namespace Ui {
class LoginAndRegWindow;
}

class LoginAndRegWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginAndRegWindow(QWidget *parent = 0);
    ~LoginAndRegWindow();
    void SetTcpClient(TCPClient *tcp);

private slots:

    void on_tabWidget_currentChanged(int index);
    void on_CreateExamRoom_clicked();
    void LicenceProofreading(QString Licence);

    void GetLicenceResult(int Result);
    // 许可证判断返回时触发的槽函数
    void on_pushButton_7_clicked();

private:
    Ui::LoginAndRegWindow *ui;
    TCPClient *m_tcpClient;
signals:
    void CreateExamRoomSuccess();

};

#endif // LOGINANDREGWINDOW_H
