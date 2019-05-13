#include "ClientWindow.h"
#include "ui_ClientWindow.h"
ClientWindow::ClientWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    ExamRoomStartAndStopTimer = new QTimer();
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
        ui->ClientControllerArea->addWidget(m_tcpclient);
        connect(m_tcpclient,SIGNAL(ExaminationBegins(QString)), this, SLOT(ExaminationBegins(QString)));
        connect(m_tcpclient, &TCPClient::DoHandInPaper, this, &ClientWindow::markExamPapers);
        connect(m_tcpclient, SIGNAL(SetExamHistory(QString)), this, SLOT(GetExamHistory(QString)));
        connect(m_tcpclient, SIGNAL(SetInfomation(QString)), this, SLOT(GetInfomation(QString)));

    }
}

void ClientWindow::InitUI()
{
    ExamRoom = new ExamRoomModelView(nullptr);
    examPaperWindow = new ExmaPaperwindow();
    ui->ExampaperArea->addWidget(examPaperWindow);
    answerSheet = new AnswerSheet();
    //answerSheet->InitAnswerSheet(ExamRoom);
    ui->AnswerSheetArea->addWidget(answerSheet);
    InitExamRoom();
    InitExamHistory();
    InitInfo();
    // 读取qss
    QFile file(":/qss/Checked_TopBar.css");
    file.open(QIODevice::ReadOnly);
    if (file.isOpen())
    {
        qss_Checked = file.readAll();
        file.close();
    }

    QFile fileB(":/qss/UnChecked_TopBar.css");
    fileB.open(QIODevice::ReadOnly);
    if (fileB.isOpen())
    {
        qss_Unchecked = fileB.readAll();
        fileB.close();
    }
}

void ClientWindow::InitExamRoom()
{
    examPaperWindow->InitViewModelDelegate(ExamRoom);
}

void ClientWindow::SetConnect()
{
    connect(examPaperWindow, SIGNAL(Checked(int,int)),answerSheet, SLOT(setAnswerSheetStyle(int,int)));
    connect(answerSheet, SIGNAL(LocateTo(int)), examPaperWindow, SLOT(LocateToQuestion(int)));
    connect(this->ui->TAB_ExamPaperConfigure, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
    connect(this->ui->TAB_ExamRoomConfigure, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
    connect(this->ui->TAB_ExamPaperSet, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
    connect(this->ui->TAB_ExamQusetionSet, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
    connect(ExamRoomStartAndStopTimer, SIGNAL(timeout()),this,SLOT(ExamRoomStartAndStop()));
}

void ClientWindow::SetTopBarButtonStyleDefult()
{
    this->ui->TAB_ExamPaperConfigure->setStyleSheet(qss_Unchecked);
    this->ui->TAB_ExamRoomConfigure->setStyleSheet(qss_Unchecked);
    this->ui->TAB_ExamPaperSet->setStyleSheet(qss_Unchecked);
    this->ui->TAB_ExamQusetionSet->setStyleSheet(qss_Unchecked);
}

/**
 * @brief ClientWindow::InitExamHistory 初始化考试模型数据源和模型，并绑定到界面（在InitUI中调用）
 */
void ClientWindow::InitExamHistory()
{
    ExamHiStoryList = new QStringList();
    ExamHistoryModel = new QStringListModel();
    ExamHistoryModel->setStringList(*ExamHiStoryList);
    ui->ExamHistoryListView->setModel(ExamHistoryModel);

}

/**
 * @brief ClientWindow::InitInfo 初始化消息通知数据模型和数据源， 并绑定到界面（在InitUI中调用）
 */
void ClientWindow::InitInfo()
{
    InfoList = new QStringList();
    InfoListModel = new QStringListModel();
    InfoListModel->setStringList(*InfoList);
    ui->InfoListView->setModel(InfoListModel);
    InfoList->append("这是测试信息--消息通知001");
    InfoListModel->setStringList(*InfoList);
}


void ClientWindow::InitUserInfo(QString LoginInfo)
{
    //创建一个用户数据对象
    userInfo = new UserInfo();
    QStringList requset = LoginInfo.split('_');
    userInfo->setUserIP(requset.at(1).split(':').at(0));
    userInfo->setUserPort(requset.at(1).split(':').at(1));
    userInfo->setUserName(requset.at(2));
    userInfo->setUserID(requset.at(3));
    userInfo->setUserTicket(requset.at(4));

    ui->UserName->setText(userInfo->getUserName());
    ui->Ticket->setText(userInfo->getUserTicket());
    ui->IDNumber->setText(userInfo->getUserID());
    ui->IpAddress->setText((userInfo->getUserIP()));
}

void ClientWindow::markExamPapers()
{
    if(Marked)
        return;
    //停止计时
    ExamRoomStartAndStopTimer->stop();
    //判卷
    int score = 0;
    QString Decision = "";
    for(auto i : ExamRoom->examRoom->ExamPaper->getExamList())
    {
        if(i->getTrueResult() == i->getCheckResult())
        {
            score += i->getScore().toInt();
        }
    }
    ExamRoom->examRoom->ExamPaper->TotalScore =QString::number(score);
    if(score < ExamRoom->TotalScore*0.6)
    {
        Decision = "D";
    }
    else if (score >= ExamRoom->TotalScore*0.6 && score < ExamRoom->TotalScore*0.7) {
        Decision = "C";
    }
    else if (score >= ExamRoom->TotalScore*0.7 && score < ExamRoom->TotalScore*0.8) {
        Decision = "B";
    }
    else if (score >= ExamRoom->TotalScore*0.8 && score < ExamRoom->TotalScore*0.9) {
        Decision = "A";
    }
    else if (score >= ExamRoom->TotalScore*0.9 && score < ExamRoom->TotalScore*0.95) {
        Decision = "S";
    }
    else if (score >= ExamRoom->TotalScore*0.95 && score < ExamRoom->TotalScore) {
        Decision = "SS";
    }
    else if (score == ExamRoom->TotalScore) {
        Decision = "SSS";
    }
    QString info = "HandInPaper_"+QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm ddd")+"_"+userInfo->getUserID()+"_"+QString::number(score)+"_"+Decision;
    QString temp = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm ddd") +" "+ userInfo->getUserID() +" "+QString::number(score)+" "+Decision;
    ExamHiStoryList->insert(0,temp);
    ui->ExamHistoryNumber->setText(QString::number(ui->ExamHistoryNumber->text().toInt() + 1));
    ExamHistoryModel->setStringList(*ExamHiStoryList);
    m_tcpclient->SendInfo(info.toLocal8Bit());
    QMessageBox msgBox;
    msgBox.setText("本次考试结束，得分："+ExamRoom->examRoom->ExamPaper->TotalScore);
    msgBox.exec();
    // 收卷
    ExamRoom->examRoom->ExamPaper->Clear();
    Marked = true;
}

void ClientWindow::ToolButtonCliced()
{
    QToolButton &btn = *qobject_cast<QToolButton*>(sender());
    SetTopBarButtonStyleDefult();
    btn.setStyleSheet(qss_Checked);
    if(ui->TAB_ExamPaperSet == &btn)
        this->ui->stackedWidget->setCurrentIndex(2);
    if(ui->TAB_ExamQusetionSet == &btn)
    {
        this->ui->stackedWidget->setCurrentIndex(3);
    }

    if(ui->TAB_ExamRoomConfigure == &btn)
    {
        this->ui->stackedWidget->setCurrentIndex(1);
    }
    if(ui->TAB_ExamPaperConfigure == &btn)
    {
        this->ui->stackedWidget->setCurrentIndex(0);
    }
}

/**
 * @brief ClientWindow::GetExamHistory 获取所有的历史考试记录信息，并添加到考试记录数据模型
 * @param Historys ExamHistory%%examhistory1%%examhistory2
 */
void ClientWindow::GetExamHistory(QString Historys)
{
    if(InitFinish)
    {
        QStringList strlist = Historys.split("%%");
        //去掉头部信息
        strlist.removeAt(0);
        if(strlist.length()>0)
        {
            ExamHiStoryList->clear();
            for(auto i : strlist)
            {
                ExamHiStoryList->insert(0,i);
            }
            ExamHistoryModel->setStringList(*ExamHiStoryList);
            ui->ExamHistoryNumber->setText(QString::number(ExamHiStoryList->length()));
        }

    }
}

/**
 * @brief ClientWindow::GetInfomation
 * @param Infomation Infomation%%Info1%%info2
 */
void ClientWindow::GetInfomation(QString Infomation)
{
    if(InitFinish)
    {
        QStringList strlist = Infomation.split("%%");
        //去掉头部信息
        strlist.removeAt(0);
        if(strlist.length()>0)
        {
            for(auto i : strlist)
            {
                InfoList->insert(0,i);
            }
            InfoListModel->setStringList(*InfoList);
        }

    }
}

void ClientWindow::ExamRoomStartAndStop()
{
    ExamRoom->examRoom->PastTestTime += 1;
    ui->lcdNumber->display(QString::number(ExamRoom->examRoom->TotalTestTime-ExamRoom->examRoom->PastTestTime));
    ui->progressBar->setValue(ExamRoom->examRoom->PastTestTime);
}

void ClientWindow::ExaminationBegins(QString ExamRoomInfo)
{
    if(InitFinish)
    {
        ui->HandInHand->setEnabled(true);
        QStringList strlist = ExamRoomInfo.split("%%");
        QString tempstr = strlist.at(1)+"%%"+strlist.at(2)+"%%"+strlist.at(3);
        ExamRoom->re_serialization(tempstr);
        answerSheet->InitAnswerSheet(ExamRoom);
        for(auto i : ExamRoom->examRoom->ExamPaper->getExamList())
        {
            ExamRoom->TotalScore += i->getScore().toInt();
        }
        ui->PaperName->setText(ExamRoom->examRoom->ExamPaper->PaperName);
        ui->TotalTime->setText(ExamRoom->examRoom->ExamPaper->TotalTestTime);
        ui->TotalScore->setText(QString::number(ExamRoom->TotalScore));

        // 开始考试计时
        ExamRoom->examRoom->PastTestTime = 0;
        ExamRoom->examRoom->TotalTestTime = ExamRoom->examRoom->ExamPaper->TotalTestTime.toInt();
        ui->lcdNumber->display(ExamRoom->examRoom->ExamPaper->TotalTestTime);
        ui->progressBar->setRange(0, ExamRoom->examRoom->ExamPaper->TotalTestTime.toInt());
        ui->progressBar->setValue(0);
        ExamRoomStartAndStopTimer->start(60000);
        Marked = false;
    }
}

void ClientWindow::on_HandInHand_clicked()
{
    markExamPapers();
}

void ClientWindow::on_EditInfo_clicked()
{
    if(ui->UserName->isReadOnly())
    {
        ui->UserName->setReadOnly(false);
        ui->IDNumber->setReadOnly(false);
    }
    else if(ui->UserName->text()!=""&& ui->IDNumber->text()!=""&&ui->UserName->isReadOnly()==false){
        ui->UserName->setReadOnly(true);
        ui->IDNumber->setReadOnly(true);
        // 保存到数据库
        QString info = "ChangeUserInfo_"+ui->Ticket->text()+"_"+ui->UserName->text()+"_"+ui->IDNumber->text();
        m_tcpclient->SendInfo(info.toLocal8Bit());
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("修改过的信息不允许未空");
        msgBox.exec();
    }
}


