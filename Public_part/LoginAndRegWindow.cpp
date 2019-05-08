#include "LoginAndRegWindow.h"
#include "ui_LoginAndRegWindow.h"
//静态的自定义提示框
#include "Public_part/MessageWindow.h"
Q_GLOBAL_STATIC(MessageWindow, messageWindow);
LoginAndRegWindow::LoginAndRegWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginAndRegWindow)
{
    m_parent = parent;
    ui->setupUi(this);
    ReadConfig();
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
        messageWindow->ShowMessage(m_parent, "考场创建成功");
        // 正确，关闭登陆界面，发送许可证正确指令
        emit CreateExamRoomSuccess();
    }
    if(Result == -1)
    {
        this->ui->ERLTip->setIcon(QIcon(":/img/error.png"));
        messageWindow->ShowMessage(m_parent, "许可证不存在，请联系caoyong_work@outlook.com");
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
        //写入配置信息到文件
        if(!Tickets->contains(ui->TICKETChoice->lineEdit()->text()))
        {
            Tickets->append(ui->TICKETChoice->lineEdit()->text());
            IPs->append(ui->ServerIp->text());
            Ports->append(ui->ServerPort->text());
            Names->append(ui->UserName->text());
            Numbers->append(ui->UserNumber->text());
            WriteConfig();
        }

        QMessageBox message(QMessageBox::NoIcon, "提示", "登录成功");
        message.setIconPixmap(QPixmap(":/img/Tip.png"));
        message.exec();
        emit LoginSuccessfuly(LoginInfo);
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
    QString info = "LoginRequest_"+ui->ServerIp->text()+":"+ui->ServerPort->text()+"_"+ui->UserName->text()+"_"+ui->UserNumber->text()+"_"+ui->TICKETChoice->lineEdit()->text();
    char*  LoginRequest;
    QByteArray ba = info.toLatin1();
    LoginRequest=ba.data();
    m_tcpClient->SendInfo(LoginRequest);
    LoginInfo = info;
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
    {
        this->ui->stackedWidget->setCurrentIndex(1);
    }

    if(ui->TAB_SIGNIN == &btn)
    {
        this->ui->stackedWidget->setCurrentIndex(2);
    }

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

    //设置下拉输入框的数据源
    TICKETModel = new QStringListModel();
    TICKETModel->setStringList(*Tickets);
    ui->TICKETChoice->setModel(TICKETModel);

    // 设置当前使用人数
    ui->userNum->setText(QString::number(Tickets->length()));
    //设置阴影效果
    CreateGroupBoxEffect = new QGraphicsDropShadowEffect;
    CreateGroupBoxEffect->setOffset(0,0);
    CreateGroupBoxEffect->setColor(QColor(0,0,0,50));
    CreateGroupBoxEffect->setBlurRadius(20);

    // 绑定
    connect(this->ui->TAB_WELCOME, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
    connect(this->ui->TAB_INFO, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
    connect(this->ui->TAB_SIGNIN, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
    connect(this->ui->TAB_UPDATE, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
    connect(this->ui->TAB_CREATEER, SIGNAL(clicked()), this, SLOT(ToolButtonCliced()));
}




void LoginAndRegWindow::on_GetLicence_clicked()
{

}

void LoginAndRegWindow::ReadConfig()
{
    QString ConfigDirectory  = QApplication::applicationDirPath() + "/Config/";
    QString logFileName = ConfigDirectory + (QApplication::applicationName()+".Config");
    QFile file;
    Tickets = new QStringList();
    IPs = new QStringList();
    Ports = new QStringList();
    Names = new QStringList();
    Numbers = new QStringList();
    Licences = new QStringList();
    file.setFileName(logFileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray t ;
        while(!file.atEnd())
        {
            t += file.readLine();
            QList<QByteArray> strlist = t.split(',');
            if(strlist.at(0) == "ClientConfig" && strlist.count() == 7)
            {
                Tickets->append(strlist.at(1));
                IPs->append(strlist.at(2));
                Ports->append(strlist.at(3));
                Names->append(strlist.at(4));
                Numbers->append(strlist.at(5));
            }
            else if(strlist.at(0) == "ServerConfig" && strlist.count() == 3)
            {
                Licences->append(strlist.at(1));
            }
        }
        file.close();
    }

}

void LoginAndRegWindow::WriteConfig()
{
    QString ConfigDirectory  = QApplication::applicationDirPath() + "/Config/";
    QDir dir(ConfigDirectory);
    if(!dir.exists())
        dir.mkdir(ConfigDirectory);
    QString logFileName = ConfigDirectory + (QApplication::applicationName()+".Config");
    QString text;
    QFile file;
    file.setFileName(logFileName);
    file.open(QIODevice::WriteOnly);
    QTextStream textStream;
    textStream.setDevice(&file);
    for(int i = 0; i <Tickets->length(); i++)
    {
        text += "ClientConfig,";
        text += Tickets->at(i) + ",";
        text += IPs->at(i) + ",";
        text += Ports->at(i) + ",";
        text += Names->at(i) + ",";
        text += Numbers->at(i) + ",";
        textStream << text << endl;
        text = "";
    }
    for(auto i : *Licences)
    {
        text += "ServerConfig,";
        text += i;
        textStream << text << endl;
    }
    file.close();
}


void LoginAndRegWindow::on_TICKETChoice_currentIndexChanged(const QString &arg1)
{
    for(int i =0 ; i <Tickets->length(); i++)
    {
        if(Tickets->at(i) == arg1)
        {
            ui->Ticket->setText(Tickets->at(i));
            ui->ServerIp->setText(IPs->at(i));
            ui->ServerPort->setText(Ports->at(i));
            ui->UserName->setText(Names->at(i));
            ui->UserNumber->setText(Numbers->at(i));
        }
    }
}
