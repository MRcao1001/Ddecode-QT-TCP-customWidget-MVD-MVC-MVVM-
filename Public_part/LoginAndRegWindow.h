#ifndef LOGINANDREGWINDOW_H
#define LOGINANDREGWINDOW_H

#include <QWidget>

namespace Ui {
class LoginAndRegWindow;
}

class LoginAndRegWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginAndRegWindow(QWidget *parent = 0);
    ~LoginAndRegWindow();

private:
    Ui::LoginAndRegWindow *ui;
};

#endif // LOGINANDREGWINDOW_H
