#include "LoginAndRegWindow.h"
#include "ui_LoginAndRegWindow.h"

LoginAndRegWindow::LoginAndRegWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginAndRegWindow)
{
    ui->setupUi(this);
    InitUI();
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
        connect(m_tcpClient, SIGNAL(DoLogin(int)), this,SLOT(GetLoginResult(int)));
        connect(m_tcpClient, SIGNAL(DoRegiste(int)), this,SLOT(GetRegistResult(int)));
    }

}

void LoginAndRegWindow::SetUserInfoModel(UserInfoModel *userInfoModel)
{
    m_userInfoModel = userInfoModel;

}

void LoginAndRegWindow::SetToolButtonToDefult()
{
    this->ui->TAB_INFO->setStyleSheet(qss_Unchecked);
    this->ui->TAB_SIGNIN->setStyleSheet(qss_Unchecked);
    this->ui->TAB_UPDATE->setStyleSheet(qss_Unchecked);
    this->ui->TAB_WELCOME->setStyleSheet(qss_Unchecked);
    this->ui->TAB_CREATEER->setStyleSheet(qss_Unchecked);
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

/*!
 * \brief LoginAndRegWindow::GetLoginResult 处理登录判断结果的信号和槽
 * \param Result
 */
void LoginAndRegWindow::GetLoginResult(int Result)
{
    if(Result == 0)
    {
        //登录成功
        QMessageBox message(QMessageBox::NoIcon, "提示", "登录成功");
        message.setIconPixmap(QPixmap(":/img/Tip.png"));
        message.exec();
        emit LoginSuccessfuly();
    }
    else {
        //登录失败
    }
}

/*!
 * \brief LoginAndRegWindow::GetRegistResult 处理注册判断结果的信号和槽
 * \param Result
 */
void LoginAndRegWindow::GetRegistResult(int Result)
{
    if(Result == 0)
    {
        // 注册成功
        QMessageBox message(QMessageBox::NoIcon, "提示", "注册成功");
        message.setIconPixmap(QPixmap(":/img/Tip.png"));
        message.exec();
        emit RegistSuccessfuly();
    }
    else {
        // 注册失败
    }
}

void LoginAndRegWindow::on_SignIn_clicked()
{
    m_tcpClient->ConnectToServer(ui->ServerIp->text(),ui->ServerPort->text().toUShort());
    QString info = "LoginRequest_"+ui->ServerIp->text()+":"+ui->ServerPort->text()+"_"+ui->UserName->text()+"_"+ui->UserNumber->text()+"_"+ui->Ticket->text();
    char*  LoginRequest;
    QByteArray ba = info.toLatin1();
    LoginRequest=ba.data();
    m_tcpClient->SendInfo(LoginRequest);
}

void LoginAndRegWindow::on_SignUp_clicked()
{
    m_tcpClient->ConnectToServer(ui->ServerIp->text(),ui->ServerPort->text().toUShort());
    QString info = "RegistRequest"+ui->ServerIp->text()+":"+ui->ServerPort->text()+"_"+ui->UserName->text()+"_"+ui->UserNumber->text()+"_"+ui->Ticket->text();
    char*  RegistRequest;
    QByteArray ba = info.toLatin1();
    RegistRequest=ba.data();
    m_tcpClient->SendInfo(RegistRequest);
}

void LoginAndRegWindow::ToolButtonCliced()
{
    QToolButton &btn = *qobject_cast<QToolButton*>(sender());
    SetToolButtonToDefult();
    btn.setStyleSheet(qss_Checked);
    if(ui->TAB_WELCOME == &btn)
        this->ui->stackedWidget->setCurrentIndex(0);
    if(ui->TAB_CREATEER == &btn)
        this->ui->stackedWidget->setCurrentIndex(1);
    if(ui->TAB_SIGNIN == &btn)
        this->ui->stackedWidget->setCurrentIndex(2);
    if(ui->TAB_INFO == &btn)
        this->ui->stackedWidget->setCurrentIndex(3);
    if(ui->TAB_UPDATE == &btn)
        this->ui->stackedWidget->setCurrentIndex(4);
}

void LoginAndRegWindow::InitUI()
{
    QString path = QCoreApplication::applicationDirPath();
    IndexMovie = new QMovie(path+"/Img/IndexGif3.gif");
    this->ui->IndexGif->setMovie(IndexMovie);
    IndexMovie->start();

    QFile file(":/qss/Checked.css");
    file.open(QIODevice::ReadOnly);
    if (file.isOpen())
    {
        qss_Checked = file.readAll();
        file.close();
    }

    QFile fileB(":/qss/UnChecked.css");
    fileB.open(QIODevice::ReadOnly);
    if (fileB.isOpen())
    {
        qss_Unchecked = fileB.readAll();
        fileB.close();
    }

    // 绑定
    connect(this->ui->TAB_WELCOME, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
    connect(this->ui->TAB_INFO, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
    connect(this->ui->TAB_SIGNIN, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
    connect(this->ui->TAB_UPDATE, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
    connect(this->ui->TAB_CREATEER, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
}



