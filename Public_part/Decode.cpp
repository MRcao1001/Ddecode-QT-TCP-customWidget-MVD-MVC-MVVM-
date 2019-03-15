#include "Decode.h"
#include "ui_Decode.h"
#include <QMessageBox>
Decode::Decode(QWidget *parent) :
    DecodeBaseWindow(parent),
    ui(new Ui::Decode)
{
    ui->setupUi(this);

    InitUI();
    InitObject();
    int i = DBManager->searchData(m_userInfoModel,"UserInfo","EncreCroe","1234567890");
    if(i == 0)
    {
       QMessageBox::information(this, "info", "ok", QMessageBox::Yes);
    }

//    //this->ui->tableView->setModel(userInfoModel);
//    m_userInfoModel = new UserInfoModel(this);
//    m_userInfoDelegate = new UserInfoDelegate(m_userInfoModel,this);
//    ui->listView->setModel(m_userInfoModel);
//    ui->listView->setItemDelegate(m_userInfoDelegate);

//    m_examPaperModel = new ExamPaperModel(this);
//    m_examPaperDelegate = new ExamPaperDelegate(m_examPaperModel, this);
//    ui->listView_2->setModel(m_examPaperModel);
//    ui->listView_2->setItemDelegate(m_examPaperDelegate);

//    mtc = new TCPClient();
//    mts = new TCPServer();
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
    LARW = new LoginAndRegWindow();
    addWidgetToMainArea(LARW);
}

void Decode::InitObject()
{
    DBManager = new DataBaseManager();
//    userInfoModel = new UserInfoModel();
}

void Decode::on_pushButton_clicked()
{
//    m_userInfoModel->add(13141,"iloveyou");
}

void Decode::on_pushButton_3_clicked()
{
//    m_examPaperModel->add(false,false,"没有题目",10,1,"QWE23","436543","43543","312412");
}
