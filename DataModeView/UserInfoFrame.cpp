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
    delete ui;
}

void UserInfoFrame::setName(const QString Name)
{
    ui->UserNameLabel->setText(Name);
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

