#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QMessageBox>
#include <QPushButton>
namespace Ui {
class TCPServer;
}

class TCPServer : public QWidget
{
    Q_OBJECT

public:
    explicit TCPServer(QWidget *parent = 0);
    ~TCPServer();
public slots:
    void CreateServer(QString IP, QString Port);
private:
    Ui::TCPServer *ui;
    QTcpServer *tcpServer;
    QList<QTcpSocket*> tcpClient;
    QTcpSocket *currentClient;

private slots:
    void NewConnectionSlot();
    void disconnectedSlot();
    void ReadData();
public slots:
    void on_btnConnect_clicked();
    void on_btnClear_clicked();
    void on_ServerSendInfo_clicked();
    void SendInfoToClient(QString IP, int Port, QString Info);
    void BroadCast(QString data);

signals:
    void LoginRequest(QString LoginInfo);
    void RegistRequset(QString RegistInfo);
};

#endif // TCPSERVER_H
