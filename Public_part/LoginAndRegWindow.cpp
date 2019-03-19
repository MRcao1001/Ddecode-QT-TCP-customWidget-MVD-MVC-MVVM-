#include "LoginAndRegWindow.h"
#include "ui_LoginAndRegWindow.h"

LoginAndRegWindow::LoginAndRegWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginAndRegWindow)
{
    ui->setupUi(this);
}

LoginAndRegWindow::~LoginAndRegWindow()
{
    delete ui;
}

void LoginAndRegWindow::SetTcpClient(TCPClient *tcp)
{
    if(tcp != nullptr)
    {
        this->m_tcpClient = tcp;
        // 绑定接收到数据信号和判断槽函数
        connect(m_tcpClient, SIGNAL(LicenceResult(int)), this, SLOT(GetLicenceResult(int)));
    }

}

void LoginAndRegWindow::on_tabWidget_currentChanged(int index)
{

}

void LoginAndRegWindow::on_CreateExamRoom_clicked()
{
    if(ui->ExamRoomIP->text() == "")
    {
        this->ui->ERTip->setIcon(QIcon(":/img/error.png"));
        return;
    }
    else {
        this->ui->ERTip->setIcon(QIcon(":/img/yes.png"));
    }

    if(ui->Invigilator->text() == "")
    {
        this->ui->INVTip->setIcon(QIcon(":/img/error.png"));
        return;
    }
    else {
        this->ui->INVTip->setIcon(QIcon(":/img/yes.png"));
    }

    if(ui->UserNum->text() == "")
    {
        this->ui->UNTip->setIcon(QIcon(":/img/error.png"));
        return;
    }
    else {
        this->ui->UNTip->setIcon(QIcon(":/img/yes.png"));
    }

    if(ui->ExamRoomLicence->text() == "")
    {
        this->ui->ERLTip->setIcon(QIcon(":/img/error.png"));
        return;
    }
    //信息填写无误之后校对许可证
    LicenceProofreading(ui->ExamRoomLicence->text());
}

void LoginAndRegWindow::LicenceProofreading(QString Licence)
{
    QByteArray ba = ("Licence_"+Licence).toLatin1();
    char* LicenceChar = ba.data();
    m_tcpClient->ConnectToServer("193.112.137.246",12345);
    m_tcpClient->SendInfo(LicenceChar);
    return ;
}

void LoginAndRegWindow::GetLicenceResult(int Result)
{
    if(Result == 0)
    {
        this->ui->ERLTip->setIcon(QIcon(":/img/yes.png"));
        QMessageBox message(QMessageBox::NoIcon, "提示", "考场创建成功");
        message.setIconPixmap(QPixmap(":/img/Tip.png"));
        message.exec();
        // 正确，关闭登陆界面，发送许可证正确指令
        emit CreateExamRoomSuccess();
    }
    if(Result == -1)
    {
        this->ui->ERLTip->setIcon(QIcon(":/img/error.png"));
        //
        QMessageBox message(QMessageBox::NoIcon, "提示", "许可证不存在，请联系caoyong_work@outlook.com");
        message.setIconPixmap(QPixmap(":/img/Tip.png"));
        message.exec();
    }
    m_tcpClient->DisConnectToServer();
}

void LoginAndRegWindow::on_pushButton_7_clicked()
{
    m_tcpClient->ConnectToServer(ui->ServerIp->text(),ui->ServerPort->text().toUShort());
    QString info = "LoginRequest_"+ui->ServerIp->text()+"-"+ui->ServerPort->text()+"_"+ui->UserName->text()+"_"+ui->UserNumber->text()+"_"+ui->Ticket->text();
    char*  ch;
    QByteArray ba = info.toLatin1();
    ch=ba.data();
    m_tcpClient->SendInfo(ch);
}
