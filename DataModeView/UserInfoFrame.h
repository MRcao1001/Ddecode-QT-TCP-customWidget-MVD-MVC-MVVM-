#ifndef USERINFOFRAME_H
#define USERINFOFRAME_H

#include <QFrame>

namespace Ui {
class UserInfoFrame;
}

class UserInfoFrame : public QFrame
{
    Q_OBJECT

public:
    explicit UserInfoFrame(QWidget *parent = 0);
    ~UserInfoFrame();
    void setName(const QString Name);
    void SetIP(const QString IP);
    void SetTicket(const QString Ticket);
    void setSelected(bool selected);
private:
    Ui::UserInfoFrame *ui;
};

#endif // USERINFOFRAME_H
