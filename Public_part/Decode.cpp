#include "Decode.h"
#include "ui_Decode.h"
#include <QMessageBox>
Decode::Decode(QWidget *parent) :
    DecodeBaseWindow(parent),
    ui(new Ui::Decode)
{
    ui->setupUi(this);

    InitObject();//初始化所有对象
    InitUI();//初始化界面
}

Decode::~Decode()
{
    delete ui;
    delete DBManager;
}

void Decode::InitUI()
{
    this->SetCustomTitleBarStyle(NOTITLEBAR);
    addWidgetToMainArea(LARW);
    addWidgetToMainArea(SW);
    addWidgetToMainArea(CW);
}

void Decode::InitObject()
{
    //初始化内置TCP模块---这两个对象必须最先初始化
    m_tcpClient = new TCPClient();
    m_tcpServer = new TCPServer();
    // 初始化用户数据模型
    m_userInfoModel = new UserInfoModel(this);
    m_userInfoDelegate = new UserInfoDelegate(m_userInfoModel,this);
    //初始化数据库模块
    DBManager = new DataBaseManager();
    //初始化登陆界面模块
    LARW = new LoginAndRegWindow(this);
    LARW->SetTcpClient(this->m_tcpClient);// 必须
    LARW->SetUserInfoModel(this->m_userInfoModel);// 必须

    //初始化考场（服务器）界面
    SW = new ServerWindow(this);
    SW->SetTcpServer(this->m_tcpServer);
    SW->SetUserInfoModel(this->m_userInfoModel);
    SW->setVisible(false);

    //初始化用户端（客户端）界面
    CW = new ClientWindow();
    CW->SetClient(this->m_tcpClient);
    CW->setVisible(false);

    // 信号槽绑定
    // 获取到许可证验证通过的信号和槽函数
    connect(LARW, SIGNAL(CreateExamRoomSuccess()), this, SLOT(on_CreateExamRoomSuccess_emit()));
    // 登录成功的信号和槽的绑定
    connect(LARW, SIGNAL(LoginSuccessfuly(QString)), this, SLOT(on_LoginSuccessfuly_emit(QString)));

}

void Decode::on_pushButton_clicked()
{
//    m_userInfoModel->add(13141,"iloveyou");
}

void Decode::on_pushButton_3_clicked()
{
    //    m_examPaperModel->add(false,false,"没有题目",10,1,"QWE23","436543","43543","312412");
}

// 创建考场通过验证，则隐藏登陆界面并显示考场配置
void Decode::on_CreateExamRoomSuccess_emit()
{
    this->LARW->setVisible(false);
    this->SW->setVisible(true);
}

void Decode::on_LoginSuccessfuly_emit(QString LoginInfo)
{
    this->LARW->setVisible(false);
    this->CW->setVisible(true);
    this->CW->InitFinish = true;
    this->CW->InitUserInfo(LoginInfo);
}
