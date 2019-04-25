#include "ServerWindow.h"
#include "ui_ServerWindow.h"

ServerWindow::ServerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    this->DBManager = new DataBaseManager();
    QString tableColums = "IP varchar(255) not NULL, PORT varchar(255) not NULL,Name varchar(255) not NULL,Number varchar(255) primary key not NULL,Ticket varchar(255) not NULL";
    DBManager->createDataTable("ExamineeInfo",tableColums);

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
    /// 绑定界面ListView和数据模型
    // 绑定所有试卷列表和数据模型
    ui->AllExamPapersListView->setModel(ExamRoom->examRoom->AllPaperListModel);
    // 绑定当前试卷视图和模型
    ui->ExamPaperListView->setModel(ExamRoom->examRoom->ExamPaper);
    ui->ExamPaperListView->setItemDelegate(ExamRoom->examRoom->ExamPaperView);
    // 绑定题库视图和模型
    ui->QusetionLibListView->setModel(ExamRoom->examRoom->QuestionLib);
    ui->QusetionLibListView->setItemDelegate(ExamRoom->examRoom->QuestionLibView);
    // 绑定用户列表视图和模型
    ui->UserListView->setModel(ExamRoom->examRoom->UserList);
    ui->UserListView->setItemDelegate(ExamRoom->examRoom->UserListView);

    //设置阴影效果
    TopBarFrameShadow = new QGraphicsDropShadowEffect;
    TopBarFrameShadow->setOffset(0,0);
    TopBarFrameShadow->setColor(QColor(0,0,0,50));
    TopBarFrameShadow->setBlurRadius(20);
    ui->TopBarFrame->setGraphicsEffect(TopBarFrameShadow);

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
    ExamRoom = new ExamRoomModelView();
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
        //this->ui->ServerArea->addWidget(m_tcpServer);
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
        //用户对象置入模型
        m_userInfoModel->add(userInfo);
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
