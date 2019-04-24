#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include <QWidget>
#include <QEventLoop>
#include <QCloseEvent>
namespace Ui {
class MessageWindow;
}

class MessageWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MessageWindow(QWidget *parent = nullptr);
    ~MessageWindow();
    void closeEvent(QCloseEvent *event);
    short ShowMessage(QWidget *parent = nullptr, QString MessageInfo = "默认提示");
    QEventLoop *m_eventLoop;
    short Result;

private slots:
    void on_Btn_OK_clicked();

    void on_Btn_Cancle_clicked();

private:
    Ui::MessageWindow *ui;
    void InitUI();

};

#endif // MESSAGEWINDOW_H
