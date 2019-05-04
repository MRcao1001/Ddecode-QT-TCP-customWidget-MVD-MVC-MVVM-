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
        connect(m_tcpclient,SIGNAL(ExaminationBegins(QString)), this, SLOT(ExaminationBegins(QString)));
    }
}

void ClientWindow::InitUI()
{
    ExamRoom = new ExamRoomModelView(nullptr);
    examPaperWindow = new ExmaPaperwindow();
    ui->ExampaperArea->addWidget(examPaperWindow);
    InitExamRoom();
    answerSheet = new AnswerSheet();
    //answerSheet->InitAnswerSheet(ExamRoom);
    ui->AnswerSheetArea->addWidget(answerSheet);

}

void ClientWindow::InitExamRoom()
{
    examPaperWindow->InitViewModelDelegate(ExamRoom);
}

void ClientWindow::SetConnect()
{
    connect(examPaperWindow, SIGNAL(Checked(int)),answerSheet, SLOT(setAnswerSheetStyle(int)));
    connect(m_tcpclient, &TCPClient::DoHandInPaper, this, &ClientWindow::markExamPapers);
}

void ClientWindow::markExamPapers()
{
    //判卷
    int score = 0;
    for(auto i : ExamRoom->examRoom->ExamPaper->getExamList())
    {
        if(i->getTrueResult() == i->getCheckResult())
        {
            score += i->getScore().toInt();
        }
    }
    ExamRoom->examRoom->ExamPaper->TotalScore =QString::number(score);
    QString info = "HandInPaper_"+ExamRoom->examRoom->ExamPaper->TotalScore;
    m_tcpclient->SendInfo(info.toLocal8Bit());
    QMessageBox msgBox;
    msgBox.setText("本次考试结束，得分："+ExamRoom->examRoom->ExamPaper->TotalScore);
    msgBox.exec();
    // 收卷
    ExamRoom->examRoom->ExamPaper->Clear();
}

void ClientWindow::ExaminationBegins(QString ExamRoomInfo)
{
    if(InitFinish)
    {
        QStringList strlist = ExamRoomInfo.split("%%");
        QString tempstr = strlist.at(1)+"%%"+strlist.at(2)+"%%"+strlist.at(3);
        ExamRoom->re_serialization(tempstr);
        answerSheet->InitAnswerSheet(ExamRoom);
    }
}

void ClientWindow::on_HandInHand_clicked()
{
    markExamPapers();
}
