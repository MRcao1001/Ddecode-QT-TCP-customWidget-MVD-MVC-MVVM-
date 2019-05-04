#include "ServerWindow.h"
#include "ui_ServerWindow.h"
#include "Public_part/MessageWindow.h"
Q_GLOBAL_STATIC(MessageWindow, messageWindow);
ServerWindow::ServerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    /// 初始化对应的数据库，如果不存在该表则创建表
    this->DBManager = new DataBaseManager();
    QString tableColums = "IP varchar(255) not NULL, PORT varchar(255) not NULL,Name varchar(255) not NULL,Number varchar(255) primary key not NULL,Ticket varchar(255) not NULL";
    DBManager->createDataTable("ExamineeInfo",tableColums);
    m_parent = parent;
    ExamRoomStartAndStopTimer = new QTimer();
    InitExamRoom();
    InitUI();

}

ServerWindow::~ServerWindow()
{
    delete ui;
}

/**
 * @brief ServerWindow::SetUserInfoModel
 * @param userInfoModel
 * 初始化UserInfoModel
 */
void ServerWindow::SetUserInfoModel(UserInfoModel *userInfoModel)
{
    this->m_userInfoModel = userInfoModel;
}

/**
 * @brief ServerWindow::InitUI
 * 初始化界面UI元素和信号槽绑定
 */
void ServerWindow::InitUI()
{
    ui->TotalTestTime->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    //设置阴影效果
    TopBarFrameShadow = new QGraphicsDropShadowEffect;
    TopBarFrameShadow->setOffset(0,0);
    TopBarFrameShadow->setColor(QColor(0,0,0,50));
    TopBarFrameShadow->setBlurRadius(20);
    ui->TopBarFrame->setGraphicsEffect(TopBarFrameShadow);

    // 置入TCP服务器控制台
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

    // 绑定
    connect(this->ui->TAB_ExamPaperConfigure, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
    connect(this->ui->TAB_ExamRoomConfigure, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
    connect(this->ui->TAB_Students, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
    connect(this->ui->TAB_ExamPaperSet, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
    connect(this->ui->TAB_ExamQusetionSet, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
    connect(ExamRoomStartAndStopTimer, SIGNAL(timeout()),this,SLOT(ExamRoomStartAndStop()));
}

/**
 * @brief ServerWindow::SetTopBarButtonStyleDefult
 * 设置标题栏按钮的样式为默认样式
 */
void ServerWindow::SetTopBarButtonStyleDefult()
{
    this->ui->TAB_ExamPaperConfigure->setStyleSheet(qss_Unchecked);
    this->ui->TAB_ExamRoomConfigure->setStyleSheet(qss_Unchecked);
    this->ui->TAB_Students->setStyleSheet(qss_Unchecked);
    this->ui->TAB_ExamPaperSet->setStyleSheet(qss_Unchecked);
    this->ui->TAB_ExamQusetionSet->setStyleSheet(qss_Unchecked);
}

/**
 * @brief ServerWindow::SetExamRoomModel
 * 初始化考场模型
 */
void ServerWindow::InitExamRoom()
{
    ExamRoom = new ExamRoomModelView(DBManager);
    /// 绑定界面ListView和数据模型
    // 绑定所有试卷列表和数据模型
    ui->AllExamPapersListView->setModel(ExamRoom->examRoom->AllPaperListModel);
    ui->AllExamPapersListView2->setModel(ExamRoom->examRoom->AllPaperListModel);
    ui->AllExamPapersListView3->setModel(ExamRoom->examRoom->AllPaperListModel);
//    修改模型数据后重新绑定
//    ExamRoom->examRoom->AllPaperList->append("txt");
//    ExamRoom->examRoom->AllPaperListModel->setStringList(*ExamRoom->examRoom->AllPaperList);
    // 绑定当前试卷视图和模型
    ui->ExamPaperListView->setModel(ExamRoom->examRoom->ExamPaper);
    ui->ExamPaperListView->setItemDelegate(ExamRoom->examRoom->ExamPaperView);
    // 绑定题库视图和模型
    ui->QsestionListView->setModel(ExamRoom->examRoom->QuestionLib);
    ui->QsestionListView->setItemDelegate(ExamRoom->examRoom->QuestionLibView);

    // 绑定用户列表视图和模型
    ui->UserListView->setModel(ExamRoom->examRoom->UserList);
    ui->UserListView->setItemDelegate(ExamRoom->examRoom->UserListView);
}

void ServerWindow::SetupINFOtoUI(ExamChoiceQusetion *exq)
{
    if( ui->ExamQuestionText->toPlainText() != "")
    {
        short result = messageWindow->ShowMessage(m_parent,"当前试卷非空，您是否需要先将试题保存到试题库中");
        if(result == 1)
        {
            on_SaveQuestion_clicked();
        }
    }
    QString name = exq->getScore();;
    ui->ExamQuestionSocre->setText(exq->getScore());
    ui->ExamQuestionReSult->setText( exq->getTrueResult());
    ui->ResultA->setText( exq->getResultA());
    ui->ResultB->setText( exq->getResultB());
    ui->ResultC->setText(exq->getResultC());
    ui->ResultD->setText(exq->getResultD());
    ui->ExamQuestionText->setPlainText(exq->getQuestion());
}

ExamChoiceQusetion *ServerWindow::GetINFOfromUI()
{
    ExamChoiceQusetion *newQuestion = new ExamChoiceQusetion();
    newQuestion->setScore(ui->ExamQuestionSocre->text());
    newQuestion->setTrueResult(ui->ExamQuestionReSult->text());
    newQuestion->setResultA(ui->ResultA->text());
    newQuestion->setResultB(ui->ResultB->text());
    newQuestion->setResultC(ui->ResultC->text());
    newQuestion->setResultD(ui->ResultD->text());
    newQuestion->setQuestion(ui->ExamQuestionText->toPlainText());
    return newQuestion;
}

/**
 * @brief ServerWindow::SetTcpServer
 * @param tcp
 * 初始化TCP组件
 */
void ServerWindow::SetTcpServer(TCPServer *tcp)
{
    if(tcp != nullptr)
    {
        this->m_tcpServer = tcp;
        this->ui->ServerArea->addWidget(m_tcpServer);
        this->m_tcpServer->on_btnConnect_clicked();
        // 绑定接收到数据信号和判断槽函数
        connect(m_tcpServer, SIGNAL(LoginRequest(QString)), this, SLOT(GetLoginRequest(QString)));
        connect(m_tcpServer, SIGNAL(RegistRequset(QString)), this, SLOT(GetRegistRequest(QString)));
    }
}


/**
 * @brief ServerWindow::ToolButtonCliced
 * 标题栏按钮槽函数
 */
void ServerWindow::ToolButtonCliced()
{
    QToolButton &btn = *qobject_cast<QToolButton*>(sender());
    SetTopBarButtonStyleDefult();
    btn.setStyleSheet(qss_Checked);
    if(ui->TAB_ExamPaperSet == &btn)
        this->ui->stackedWidget->setCurrentIndex(3);
    if(ui->TAB_ExamQusetionSet == &btn)
    {
        this->ui->stackedWidget->setCurrentIndex(4);
    }

    if(ui->TAB_Students == &btn)
    {
        this->ui->stackedWidget->setCurrentIndex(2);
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
 * @brief ServerWindow::ExamRoomStartAndStop 考试开始和结束的槽函数
 */
void ServerWindow::ExamRoomStartAndStop()
{
    ExamRoom->examRoom->PastTestTime += 1;

    ui->lcdNumber->display(QString::number(ExamRoom->examRoom->TotalTestTime-ExamRoom->examRoom->PastTestTime));
    ui->progressBar->setValue(ExamRoom->examRoom->PastTestTime);
    if(ExamRoom->examRoom->PastTestTime == ExamRoom->examRoom->TotalTestTime)
    {
         m_tcpServer->BroadCast("EndOfExamination");
         ExamRoomStartAndStopTimer->stop();
    }
}


// login Info : "LoginRequset"+ip-port+name+number+Ticket;
/**
 * @brief ServerWindow::GetLoginRequest
 * @param LoginInfo
 * 登陆信号传来时的槽函数，判断登陆信息是否正确
 */
void ServerWindow::GetLoginRequest(QString LoginInfo)
{
    //创建一个用户数据对象
    UserInfo *userInfo = new UserInfo();
    QStringList requset = LoginInfo.split('_');
    userInfo->setUserIP(requset.at(1).split(':').at(0));
    userInfo->setUserPort(requset.at(1).split(':').at(1));
    userInfo->setUserName(requset.at(2));
    userInfo->setUserID(requset.at(3).toInt());
    userInfo->setUserTicket(requset.at(4));
    int result = DBManager->searchUserData(userInfo);
    if(result == 0)
    {
        // 查找到了对应的登陆信息，准许登陆
        m_tcpServer->SendInfoToClient(userInfo->getUserIP(),userInfo->getUserPort().toInt(), "INFO_IS_RIGHT");
        //用户对象置入考场的用户表
        ExamRoom->examRoom->UserList->add(userInfo);
    }
    else {
         m_tcpServer->SendInfoToClient(userInfo->getUserIP(),userInfo->getUserPort().toInt(), "INFO_IS_NOT_RIGHT");
    }
}

// Regist Info : "RegistRequset"+ip-port+name+number+Ticket;
/**
 * @brief ServerWindow::GetRegistRequest
 * @param RegistInfo
 * 注册信号传来时的槽函数，并执行注册操作
 */
void ServerWindow::GetRegistRequest(QString RegistInfo)
{
    //创建一个用户数据对象
    UserInfo *userInfo = new UserInfo();
    QStringList requset = RegistInfo.split('_');
    userInfo->setUserIP(requset.at(1).split(':').at(0));
    userInfo->setUserPort(requset.at(1).split(':').at(1));
    userInfo->setUserName(requset.at(2));
    userInfo->setUserID(requset.at(3).toInt());
    userInfo->setUserTicket(requset.at(4));
    int result = DBManager->insertUserData(userInfo);
    if(result == 0)
    {
        //插入成功
        m_tcpServer->SendInfoToClient(userInfo->getUserIP(),userInfo->getUserPort().toInt(), "REGIST_SUCCESS");
    }
    else {
        m_tcpServer->SendInfoToClient(userInfo->getUserIP(),userInfo->getUserPort().toInt(), "USER_EXIST");
    }
}

void ServerWindow::on_ExamPaperListView_clicked(const QModelIndex &index)
{


}

void ServerWindow::on_AllExamPapersListView_clicked(const QModelIndex &index)
{
    if(ExamRoom->examRoom->ExamPaper->rowCount() != 0)
    {
        short result = messageWindow->ShowMessage(m_parent,"当前试卷非空，您是否需要先将试题保存到试题库中");
        if(result == 1)
        {
            on_SaveQuestion_clicked();
        }
    }
    QMap<int , QVariant> currentItem = ExamRoom->examRoom->AllPaperListModel->itemData(index);
    QString data = currentItem.last().toString();
    QString PaperName = currentItem.last().toString().split(',').at(0);
    ///为试卷列表绑定的model赋值
    ExamRoom->SetPaper(ExamRoom->examRoom->ExamPaper,ExamRoom->GetPaperQuestionList(PaperName),data);
}

/**
 * @brief ServerWindow::on_AddExamQuestion_clicked 新增试题
 */
void ServerWindow::on_AddExamQuestion_clicked()
{
    ExamChoiceQusetion *newQuestion = GetINFOfromUI();
    ExamRoom->examRoom->ExamPaper->add(newQuestion);
}

void ServerWindow::on_RemoveExamItem_clicked()
{
    QModelIndex index = ui->ExamPaperListView->currentIndex();
    ExamRoom->examRoom->ExamPaper->remove(index.row());
}


void ServerWindow::on_SaveExamPaperToLib_clicked()
{
    on_SaveExamPaper_clicked();
    int ret = ExamRoom->SavePaperToLib();
    if(ret == 0)
        messageWindow->ShowMessage(m_parent,"保存成功");
    else {
        messageWindow->ShowMessage(m_parent,"保存时出现错误，错误代码:"+ QString::number(ret));
    }
}

void ServerWindow::on_SaveExamPaper_clicked()
{
    if(ui->ExamPaperName->text()=="" || ui->ExampaperTime->text() =="")
    {
        messageWindow->ShowMessage(m_parent,"还未完成对试卷时长和试卷名称的配置");
        return;
    }
    ExamRoom->examRoom->ExamPaper->PaperName = ui->ExamPaperName->text();
    ExamRoom->examRoom->ExamPaper->TotalTestTime = ui->ExampaperTime->text();

}

/**
 * @brief ServerWindow::on_SaveExamQuestionToLib_clicked 增 题库新增试题
 */
void ServerWindow::on_SaveExamQuestionToLib_clicked()
{
    ExamChoiceQusetion *newQuestion = GetINFOfromUI();
    ExamRoom->examRoom->QuestionLib->add(newQuestion);
    int ret = ExamRoom->SaveQuestionToLib(newQuestion);
    if(ret == 0)
        messageWindow->ShowMessage(m_parent,"保存成功");
    else {
        messageWindow->ShowMessage(m_parent,"保存时出现错误，错误代码:"+ QString::number(ret));
    }
}

void ServerWindow::on_AddQuestion_clicked()
{
    emit ui->TAB_ExamPaperConfigure->click();
}

void ServerWindow::on_SaveQuestion_clicked()
{
    TempQuestion= GetINFOfromUI();
    int ret = ExamRoom->SaveQuestionToLib(TempQuestion);
    if(ret == 0)
        messageWindow->ShowMessage(m_parent,"保存成功");
    else {
        messageWindow->ShowMessage(m_parent,"保存时出现错误，错误代码:"+ QString::number(ret));
    }
}

void ServerWindow::on_EditQuestion_clicked()
{
    if(ExamRoom->examRoom->QuestionLib->rowCount() == 0)
    {
        ui->EditQuestion->setEnabled(false);
        ui->DeleteQuestion->setEnabled(false);
        return;
    }
    emit ui->TAB_ExamPaperConfigure->click();
    QModelIndex tempindex = ui->QsestionListView->currentIndex();
    TempQuestion = ExamRoom->examRoom->QuestionLib->at(tempindex.row());
    SetupINFOtoUI(TempQuestion);
}


void ServerWindow::on_QsestionListView_clicked(const QModelIndex &index)
{
    ui->EditQuestion->setEnabled(true);
    ui->DeleteQuestion->setEnabled(true);
}

void ServerWindow::on_DeleteQuestion_clicked()
{
    if(ExamRoom->examRoom->QuestionLib->rowCount() == 0)
    {
        ui->EditQuestion->setEnabled(false);
        ui->DeleteQuestion->setEnabled(false);
        return;
    }
    QModelIndex tempindex = ui->QsestionListView->currentIndex();
    TempQuestion = ExamRoom->examRoom->QuestionLib->at(tempindex.row());
    int ret = ExamRoom->DeleteQuestion(TempQuestion, tempindex.row());
    if(ret == 0)
        messageWindow->ShowMessage(m_parent,"删除成功");
    else {
        messageWindow->ShowMessage(m_parent,"删除时出现错误，错误代码:"+ QString::number(ret));
    }
}

/**
 * @brief ServerWindow::on_ExamStart_clicked 开始考试
 */
void ServerWindow::on_ExamStart_clicked()
{
    if(ExamStarting)
    {
        ExamRoomStartAndStopTimer->stop();
        ui->ExamStart->setText("开始本场考试");
        ui->lcdNumber->display("0:00");
        ui->progressBar->setValue(0);
        m_tcpServer->BroadCast("HandInPaper");
        return;
    }
    /// 设定考场对象
    ExamRoomModel *examRoom = ExamRoom->examRoom;
    if(ui->TotalTestTime->text() == "")
    {
        messageWindow->ShowMessage(m_parent,"您还未输入输入考试时间！");
        return;
    }
    examRoom->TotalTestTime = ui->TotalTestTime->text().toInt();
    if(ui->allowCopy->isChecked())
    {
        examRoom->AllowCopy = true;
    }
    if(ui->allowPaste->isChecked())
    {
        examRoom->AllowPaste = true;
    }
    if(ui->AutoJudging->isChecked())
    {
        examRoom->AutoJudging = true;
    }
    if(ui->AutoStatistics->isChecked())
    {
        examRoom->AutoStatistics = true;
    }
    // 序列化现在的考场模型类
    QString temp = ExamRoom->serialization();
    // 使用TCP发送试卷库信息
    m_tcpServer->BroadCast("ExaminationBegins%%"+temp);
    // 开始考试计时
    ui->lcdNumber->display(QString::number(ExamRoom->examRoom->TotalTestTime-ExamRoom->examRoom->PastTestTime));
    ui->progressBar->setRange(0, examRoom->TotalTestTime);
    ui->progressBar->setValue(0);
    ExamRoomStartAndStopTimer->start(60000);
    ui->ExamStart->setText("结束本场考试");
}
