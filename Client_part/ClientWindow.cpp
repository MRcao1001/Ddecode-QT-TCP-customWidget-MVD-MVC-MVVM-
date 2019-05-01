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
    if(tcp != nullptr)
    {
        this->m_tcpclient = tcp;
        connect(m_tcpclient,SIGNAL(ExaminationBegins()), this, SLOT(ExaminationBegins()));
    }
}

void ClientWindow::InitUI()
{
    examPaperWindow = new ExmaPaperwindow();
    ui->ExampaperArea->addWidget(examPaperWindow);

    ExamRoom = new ExamRoomModelView(nullptr);
    examPaperWindow->m_examPaperModel = ExamRoom->examRoom->ExamPaper;
    examPaperWindow->m_examPaperDelegate = ExamRoom->examRoom->ExamPaperView;
}

void ClientWindow::SetConnect()
{

}

void ClientWindow::ExaminationBegins(QString ExamRoomInfo)
{
    QStringList strlist = ExamRoomInfo.split("%%");
    QString tempstr = strlist.at(1)+"%%"+strlist.at(2)+"%%"+strlist.at(3);
    ExamRoom->re_serialization(tempstr);
}
