#include "MessageWindow.h"
#include "ui_MessageWindow.h"
MessageWindow::MessageWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageWindow)
{
    ui->setupUi(this);
    InitUI();
}

MessageWindow::~MessageWindow()
{
    delete ui;
}

void MessageWindow::closeEvent(QCloseEvent *event)
{
    // 关闭窗口时结束事件循环，在exec()方法中返回选择结果;
    if (m_eventLoop != nullptr)
    {
        m_eventLoop->exit();
    }
    event->accept();
}

void MessageWindow::InitUI()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    m_eventLoop = new QEventLoop();
}

short MessageWindow::ShowMessage(QWidget *parent, QString MessageInfo)
{
    if(parent != nullptr)
    {
        ui->Infomation->setText(MessageInfo);
        this->setGeometry(parent->geometry());
        this->setWindowModality(Qt::ApplicationModal);
        this->show();
        m_eventLoop = new QEventLoop(this);
        m_eventLoop->exec();

    }
    return Result;
}

void MessageWindow::on_Btn_OK_clicked()
{
    Result = 1;
    close();
}

void MessageWindow::on_Btn_Cancle_clicked()
{
    Result = 0;
    close();
}
