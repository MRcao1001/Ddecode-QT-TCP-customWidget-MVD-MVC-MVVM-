#ifndef LEFTBAR_H
#define LEFTBAR_H

#include <QFrame>

namespace Ui {
class LeftBar;
}

class LeftBar : public QFrame
{
    Q_OBJECT

public:
    explicit LeftBar(QWidget *parent = nullptr);
    ~LeftBar();

private:
    Ui::LeftBar *ui;
};

#endif // LEFTBAR_H
