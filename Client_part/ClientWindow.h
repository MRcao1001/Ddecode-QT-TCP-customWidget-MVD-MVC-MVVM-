#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include "TCP_part/TCPClient.h"
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
    void InitUI();
    void SetConnect();
};

#endif // CLIENTWINDOW_H
