#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QWidget>
namespace Ui {
class ServerWindow;
}

class ServerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();

private:
    Ui::ServerWindow *ui;
};

#endif // SERVERWINDOW_H
