#include "LeftBar.h"
#include "ui_LeftBar.h"

LeftBar::LeftBar(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LeftBar)
{
    ui->setupUi(this);
}

LeftBar::~LeftBar()
{
    delete ui;
}
