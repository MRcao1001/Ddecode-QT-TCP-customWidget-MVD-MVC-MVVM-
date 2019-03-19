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

//    int i = DBManager->searchData(m_userInfoModel,"UserInfo","EncreCroe","1234567890");
//    if(i == 0)
//    {
//       QMessageBox::information(this, "info", "ok", QMessageBox::Yes);
//    }

//    //this->ui->tableView->setModel(userInfoModel);
//    m_userInfoModel = new UserInfoModel(this);
//    m_userInfoDelegate = new UserInfoDelegate(m_userInfoModel,this);
//    ui->listView->setModel(m_userInfoModel);
//    ui->listView->setItemDelegate(m_userInfoDelegate);

//    m_examPaperModel = new ExamPaperModel(this);
//    m_examPaperDelegate = new ExamPaperDelegate(m_examPaperModel, this);
//    ui->listView_2->setModel(m_examPaperModel);
//    ui->listView_2->setItemDelegate(m_examPaperDelegate);


//    mtc->show();
//    mts->show();
//    ui->horizontalLayout->addWidget(mtc);
//    ui->horizontalLayout->addWidget(mts);
}

Decode::~Decode()
{
    delete ui;
    delete DBManager;
}

void Decode::InitUI()
{
    this->SetCustomTitleBarStyle(ONLYBTN);
    addWidgetToMainArea(LARW);
    addWidgetToMainArea(SW);
}

void Decode::InitObject()
{
    //初始化内置TCP模块---这两个对象必须最先初始化
    m_tcpClient = new TCPClient();
    m_tcpServer = new TCPServer();
    //初始化数据库模块
    DBManager = new DataBaseManager();
    //初始化登陆界面模块
    LARW = new LoginAndRegWindow();
    LARW->SetTcpClient(this->m_tcpClient);
    //初始化考场（服务器）界面
    SW = new ServerWindow();
    SW->SetTcpServer(this->m_tcpServer);
    SW->setVisible(false);
    // 信号槽绑定
    // 获取到许可证验证通过的信号和槽函数
    connect(LARW, SIGNAL(CreateExamRoomSuccess()), this, SLOT(on_CreateExamRoomSuccess_emit()));


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
