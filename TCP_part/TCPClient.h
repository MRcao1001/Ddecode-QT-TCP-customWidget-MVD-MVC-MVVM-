#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
namespace Ui {
class TCPClient;
}

class TCPClient : public QWidget
{
    Q_OBJECT

public:
    explicit TCPClient(QWidget *parent = 0);
    ~TCPClient();

private:
    Ui::TCPClient *ui;
    QTcpSocket *tcpClient;

private slots:
    //客户端槽函数
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);

    void on_btnConnect_clicked();
    void on_btnSend_clicked();
    void on_pushButton_clicked();
};

#endif // TCPCLIENT_H
