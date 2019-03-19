#include "ServerWindow.h"
#include "ui_ServerWindow.h"

ServerWindow::ServerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    this->DBManager = new DataBaseManager();
    QString tableColums = "IP_PORT varchar(255),Name varchar(255),Number varchar(255),Ticket varchar(255)";
    DBManager->createDataTable("ExamineeInfor",tableColums);
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::SetTcpServer(TCPServer *tcp)
{
    if(tcp != nullptr)
    {
        this->m_tcpServer = tcp;
        this->ui->ServerArea->addWidget(m_tcpServer);
        this->m_tcpServer->on_btnConnect_clicked();
        // 绑定接收到数据信号和判断槽函数
        connect(m_tcpServer, SIGNAL(LoginRequest(QString)), this, SLOT(GetLoginRequest(QString)));
    }
}

// login Info : "LoginRequset"+ip-port+name+number+Ticket;
void ServerWindow::GetLoginRequest(QString LoginInfo)
{
    QStringList requset = LoginInfo.split('_');
    int result = DBManager->searchData("SELECT * FROM ExamineeInfor WHERE Number='"+requset.at(3)+"' AND Ticket = '"+requset.at(4)+"'");
    if(result == 0)
    {
        // 查找到了对应的登陆信息，准许登陆
        m_tcpServer->SendInfoToClient(requset.at(1).split(':').at(0), requset.at(1).split(':').at(1).toInt(), "INFO_IS_RIGHT");
    }
}
