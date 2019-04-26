#include "UserInfoFrame.h"
#include "ui_UserInfoFrame.h"

UserInfoFrame::UserInfoFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::UserInfoFrame)
{
    ui->setupUi(this);
}

UserInfoFrame::~UserInfoFrame()
{
    ui->IconButton->setFixedSize(100,100);
    delete ui;
}

void UserInfoFrame::setName(const QString Name)
{
    ui->UserNameLabel->setText(Name);
}

void UserInfoFrame::SetIP(const QString IP)
{
    ui->UserIPLabel->setText(IP);
}

void UserInfoFrame::SetTicket(const QString Ticket)
{
    ui->UserTicketLabel->setText(Ticket);
}

void UserInfoFrame::setSelected(bool selected)
{
    if(selected)
    {
        this->setStyleSheet("#UserInfoFrame{border:2px solid red;}");
    }
    else{
        this->setStyleSheet("#UserInfoFrame{border:none;}");
    }
}

