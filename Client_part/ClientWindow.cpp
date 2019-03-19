#include "ClientWindow.h"
#include "ui_ClientWindow.h"
ClientWindow::ClientWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    InitUI();
    SetConnect();
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::SetClient(TCPClient *tcp)
{

}

void ClientWindow::InitUI()
{

}

void ClientWindow::SetConnect()
{

}
