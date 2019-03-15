#include "LoginAndRegWindow.h"
#include "ui_LoginAndRegWindow.h"

LoginAndRegWindow::LoginAndRegWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginAndRegWindow)
{
    ui->setupUi(this);
}

LoginAndRegWindow::~LoginAndRegWindow()
{
    delete ui;
}
