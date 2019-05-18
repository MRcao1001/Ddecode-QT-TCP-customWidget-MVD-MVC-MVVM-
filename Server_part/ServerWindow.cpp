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
    InitDataBase();
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

void ServerWindow::InitDataBase()
{
    //创建考生表如果不存在的话
    QString tableColums = "IP varchar(255) not NULL, PORT varchar(255) not NULL,Name varchar(255) not NULL UNIQUE,Number varchar(255) primary key not NULL UNIQUE,Ticket varchar(255) not NULL UNIQUE";
    DBManager->createDataTable("ExamineeInfo",tableColums);
    //创建考试记录表如果不存在的话
    tableColums = "NUMBER integer PRIMARY KEY autoincrement,TIME varchar(12)not null,USERNUMBER varchar(50) not null,SCORE varchar(20)not null ,DECISION varchar(12) not null";
    DBManager->createDataTable("ExamHistory",tableColums);
    //创建题库表如果不存在的话
    tableColums = "ID varchar(255)  primary key not NULL, SCORE varchar(255) not NULL,RESULT varchar(255) not NULL,TEXT varchar(255) not NULL";
    DBManager->createDataTable("ExamQuestionLib",tableColums);
    //创建试卷库表如果不存在的话
    tableColums = "ID  varchar(255) primary key not NULL, NAME varchar(255) not NULL, QUESTIONS varchar(255),TIME varchar(255) not NULL";
    DBManager->createDataTable("AllPaper",tableColums);
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
    //ui->AllExamPapersListView2->setModel(ExamRoom->examRoom->AllPaperListModel);
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

/**
 * @brief ServerWindow::GetINFOfromUI
 * @param type 1->新试题  0->修改试题
 * @return
 */
ExamChoiceQusetion *ServerWindow::GetINFOfromUI(int type)
{
    ExamChoiceQusetion *newQuestion = new ExamChoiceQusetion();
    if(type == 1)
    {
        newQuestion->setNumber(ExamRoom->examRoom->ExamPaper->ExamNumber++);
    }

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
        connect(m_tcpServer, SIGNAL(LoginRequest(QString, int, QString)), this, SLOT(GetLoginRequest(QString, int, QString)));
        connect(m_tcpServer, SIGNAL(RegistRequset(QString, int, QString)), this, SLOT(GetRegistRequest(QString, int, QString)));
        connect(m_tcpServer, SIGNAL(HandInPaper(QString)), this, SLOT(WriteToDB(QString)));
        connect(m_tcpServer, SIGNAL(GetExamHistoryRequest(QString, int, QString)), this, SLOT(SendExamHistory(QString, int, QString)));
        connect(m_tcpServer, SIGNAL(ShowHelpInfo(QString, int)), this, SLOT(ShowHelpInfo(QString, int)));
        connect(m_tcpServer, SIGNAL(ChangeUserInfo(QString)),this, SLOT(ChangeUserInfo(QString)));
    }
}


/**
 * @brief ServerWindow::ToolButtonCliced
 * 标题栏按钮槽函数
 */
void ServerWindow::ToolButtonCliced()
{
    QToolButton &btn = *qobject_cast <QToolButton*>(sender());
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
        ui->TAB_Students->setText("考生管理");
        UNReadInfo = 0;
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

/**
 * @brief ServerWindow::WriteToDB 将考试记录写入buffer
 * @param buffer HandInPaper_年月日时分 星期_学号_得分_等级判定
 */
void ServerWindow::WriteToDB(QString buffer)
{
    // 将数据写入到考试记录表中
    QStringList strList = buffer.split("_");
    if(strList.length() == 5)
    {
        if(DBManager->InsertNewExamHistory(strList.at(1),strList.at(2),strList.at(3),strList.at(4)) != DBState::NOERROR)
        {
            //提示出错
        }
    }
}

/**
 * @brief ServerWindow::SendExamHistory 发送历史记录信息
 */
void ServerWindow::SendExamHistory(QString buffer,int Port, QString Ip)
{
    QStringList strList;
    QString UserNumber =  buffer.split("_").at(1);
    DBManager->GetExamHistory(strList, UserNumber);
    QString ExamHistory = "ExamHistory";
    for(auto i : strList)
    {
        ExamHistory.append("%%");
        ExamHistory.append(i);
    }
    m_tcpServer->SendInfoToClient(Ip, Port, ExamHistory.toLocal8Bit());
}

void ServerWindow::ShowHelpInfo(QString IP, int Port)
{
    UNReadInfo ++;
    QString ButtonName = "考生管理 ";
    ButtonName += "(未处理: ";
    ButtonName += QString::number(UNReadInfo)+")";
    ui->TAB_Students->setText(ButtonName);
}

void ServerWindow::ChangeUserInfo(QString info)
{
    QStringList strList = info.split("_");
    UserInfo* tempInfo = new UserInfo();
    tempInfo->setUserTicket(strList.at(1));
    tempInfo->setUserName(strList.at(2));
    tempInfo->setUserID(strList.at(3));
    DBManager->UpdateUserData(tempInfo);
    delete tempInfo;
}


// login Info : "LoginRequset"+ip-port+name+number+Ticket;
/**
 * @brief ServerWindow::GetLoginRequest
 * @param LoginInfo
 * 登陆信号传来时的槽函数，判断登陆信息是否正确
 */
void ServerWindow::GetLoginRequest(QString IP, int Port, QString LoginInfo)
{
    //创建一个用户数据对象
    UserInfo *userInfo = new UserInfo();
    QStringList requset = LoginInfo.split('_');
    userInfo->setUserIP(requset.at(1).split(':').at(0));
    userInfo->setUserPort(requset.at(1).split(':').at(1));
    userInfo->setUserName(requset.at(2));
    userInfo->setUserID(requset.at(3));
    userInfo->setUserTicket(requset.at(4));
    int result = DBManager->searchUserData(userInfo);
    if(result == 0)
    {
        // 查找到了对应的登陆信息，准许登陆
        m_tcpServer->SendInfoToClient(IP,Port, "INFO_IS_RIGHT");
        //用户对象置入考场的用户表
        ExamRoom->examRoom->UserList->add(userInfo);
    }
    else {
         m_tcpServer->SendInfoToClient(IP,Port, "INFO_IS_NOT_RIGHT");
    }
}

// Regist Info : "RegistRequset"+ip-port+name+number+Ticket;
/**
 * @brief ServerWindow::GetRegistRequest
 * @param RegistInfo
 * 注册信号传来时的槽函数，并执行注册操作
 */
void ServerWindow::GetRegistRequest(QString IP, int Port, QString RegistInfo)
{
    //创建一个用户数据对象
    UserInfo *userInfo = new UserInfo();
    QStringList requset = RegistInfo.split('_');
    userInfo->setUserIP(requset.at(1).split(':').at(0));
    userInfo->setUserPort(requset.at(1).split(':').at(1));
    userInfo->setUserName(requset.at(2));
    userInfo->setUserID(requset.at(3));
    userInfo->setUserTicket(requset.at(4));
    int result = DBManager->insertUserData(userInfo);
    if(result == 0)
    {
        //插入成功
        m_tcpServer->SendInfoToClient(IP,Port, "REGIST_SUCCESS");
    }
    else {
        m_tcpServer->SendInfoToClient(IP,Port, "USER_EXIST");
    }
}

void ServerWindow::on_ExamPaperListView_clicked(const QModelIndex &index)
{


}

void ServerWindow::on_AllExamPapersListView_clicked(const QModelIndex &index)
{
//    if(ExamRoom->examRoom->ExamPaper->rowCount() != 0)
//    {
//        short result = messageWindow->ShowMessage(m_parent,"当前试卷非空，您是否需要先将试题保存到试题库中");
//        if(result == 1)
//        {
//            on_SaveQuestion_clicked();
//        }
//    }
//    QMap<int , QVariant> currentItem = ExamRoom->examRoom->AllPaperListModel->itemData(index);
//    QString data = currentItem.last().toString();
//    QString PaperName = currentItem.last().toString().split(',').at(0);
//    ///为试卷列表绑定的model赋值
//    ExamRoom->SetPaper(ExamRoom->examRoom->ExamPaper,ExamRoom->GetPaperQuestionList(PaperName),data);
}



void ServerWindow::on_RemoveExamItem_clicked()
{
    QModelIndex index = ui->ExamPaperListView->currentIndex();
    ExamRoom->examRoom->ExamPaper->remove(index.row());
}

/**
 * @brief ServerWindow::on_AddExamQuestion_clicked 新增试题,需要考虑题号
 */
void ServerWindow::on_AddExamQuestion_clicked()
{
    ExamChoiceQusetion *newQuestion = GetINFOfromUI(1);
    ExamRoom->examRoom->ExamPaper->add(newQuestion);
    ExamRoom->TempExamQuestionNum++;
}

/**
 * @brief ServerWindow::on_SaveExamPaperToLib_clicked 创建一个新的试卷
 */
void ServerWindow::on_SaveExamPaperToLib_clicked()
{
    if(ui->ExamPaperName->text()=="" || ui->ExampaperTime->text() =="")
    {
        messageWindow->ShowMessage(m_parent,"还未完成对试卷时长和试卷名称的配置");
        return;
    }

    ExamRoom->examRoom->ExamPaper->PaperName = ui->ExamPaperName->text();
    ExamRoom->examRoom->ExamPaper->TotalTestTime = ui->ExampaperTime->text();
    ExamRoom->examRoom->ExamPaper->Clear();
    ExamRoom->examRoom->ExamPaper->ExamNumber = 0;
    int ret = ExamRoom->SavePaperToLib(0);
    if(ret == 0)
        messageWindow->ShowMessage(m_parent,"创建成功成功");
    else if(ret == -9) {
        messageWindow->ShowMessage(m_parent,"试卷名已经存在，请重试");
    }
    else {
         messageWindow->ShowMessage(m_parent,"保存数据出现错误，详情请查阅日志");
    }
}

/**
 * @brief ServerWindow::on_SaveExamPaper_clicked  保存对试卷的修改
 */
void ServerWindow::on_SaveExamPaper_clicked()
{
    int ret = ExamRoom->SavePaperToLib(1);
    if(ret == 0)
        messageWindow->ShowMessage(m_parent,"保存成功");
    else {
         messageWindow->ShowMessage(m_parent,"保存数据出现错误，详情请查阅日志");
    }
}

/**
 * @brief ServerWindow::on_SaveExamQuestionToLib_clicked 增 题库新增试题
 */
void ServerWindow::on_SaveExamQuestionToLib_clicked()
{
    ExamChoiceQusetion *newQuestion = GetINFOfromUI(0);
    ExamRoom->examRoom->QuestionLib->add(newQuestion);
    int ret = ExamRoom->SaveQuestionToLib(newQuestion,1);
    if(ret == 0)
        messageWindow->ShowMessage(m_parent,"新增试题成功");
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
    TempQuestion= GetINFOfromUI(0);
    int ret = ExamRoom->SaveQuestionToLib(TempQuestion,0);
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
    ExamChoiceQusetion *tempQuestion = ExamRoom->examRoom->QuestionLib->at(index.row());
    ExamRoom->examRoom->ExamPaper->ExamNumber = tempQuestion->getNumber();
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
        //结束考试
        ExamRoomStartAndStopTimer->stop();
        ui->ExamStart->setText("开始本场考试");
        ui->lcdNumber->display("0:00");
        ui->progressBar->setValue(0);
        m_tcpServer->BroadCast("HandInPaper");
        ExamStarting = false;
        return;
    }
    ExamStarting = true;
    /// 设定考场对象
    ExamRoomModel *examRoom = ExamRoom->examRoom;
    if(ui->TotalTestTime->text() == "")
    {
        messageWindow->ShowMessage(m_parent,"您还未输入输入考试时间！");
        return;
    }
    examRoom->ExamPaper->TotalTestTime = ui->TotalTestTime->text();
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
    ExamRoom->examRoom->TotalTestTime = ExamRoom->examRoom->ExamPaper->TotalTestTime.toInt();
    ui->lcdNumber->display(QString::number(ExamRoom->examRoom->TotalTestTime-ExamRoom->examRoom->PastTestTime));
    ui->progressBar->setRange(0, examRoom->TotalTestTime);
    ui->progressBar->setValue(0);
    ExamRoomStartAndStopTimer->start(60000);
    ui->ExamStart->setText("结束本场考试");
}

void ServerWindow::on_SetPaper_clicked()
{
//    QMap<int , QVariant> currentItem = ExamRoom->examRoom->AllPaperListModel->itemData(ui->AllExamPapersListView->currentIndex());
//    QString data = currentItem.last().toString();
//    QString PaperName = currentItem.last().toString().split(',').at(0);
//    ///为试卷列表绑定的model赋值
//    ExamRoom->SetPaper(ExamRoom->examRoom->ExamPaper,ExamRoom->GetPaperQuestionList(PaperName),data);
    if(ExamRoom->examRoom->ExamPaper->rowCount() != 0)
    {
        short result = messageWindow->ShowMessage(m_parent,"当前试卷非空，您是否需要先将试题保存到试题库中");
        if(result == 1)
        {
            on_SaveQuestion_clicked();
        }
    }

    QMap<int , QVariant> currentItem = ExamRoom->examRoom->AllPaperListModel->itemData(ui->AllExamPapersListView->currentIndex());
    QString data = currentItem.last().toString();
    QString PaperName = currentItem.last().toString().split(',').at(0);
    ///为试卷列表绑定的model赋值
    ExamRoom->SetPaper(ExamRoom->examRoom->ExamPaper,ExamRoom->GetPaperQuestionList(PaperName),data);
    ui->NowPaper->setText(PaperName);
}

void ServerWindow::on_AllExamPapersListView2_clicked(const QModelIndex &index)
{

}


void ServerWindow::on_DeletePaper_clicked()
{
    if(ui->NowPaper->text() == "未选择试卷")
    {
        messageWindow->ShowMessage(m_parent,"请先将选中试卷设为当前试卷，才能对其执行操作");
        return;
    }
    int ret = ExamRoom->DeletePaperInfo(ui->NowPaper->text());
    if(ret == 0)
        messageWindow->ShowMessage(m_parent,"删除成功");
    else {
        messageWindow->ShowMessage(m_parent,"删除时出现错误，错误代码:"+ QString::number(ret));
    }
}

void ServerWindow::on_attach_Update_clicked()
{
     this->ui->stackedWidget->setCurrentIndex(0);
}

void ServerWindow::on_attach_Create_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void ServerWindow::on_attach_Edit_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void ServerWindow::on_attach_Delete_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(1);
}
