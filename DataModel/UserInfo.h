#ifndef USERINFO_H
#define USERINFO_H

#include <QString>
#include "DataModel/ExamPaperModel.h"
class UserInfo
{
public://属性set方法
    UserInfo();
    void setUserID(QString getUserID);
    void setUserName(QString Name);
    void setUserIP(QString IP);
    void setUserPort(QString Port);
    void setUserTicket(QString Ticket);
public://属性get方法
    QString getUserID();
    QString getUserName();
    QString getUserIP();
    QString getUserPort();
    QString getUserTicket();
private://字段
    QString m_ip;
    QString m_Port;
    QString m_name;
    QString m_id;
    QString m_Ticket;
    QList<ExamPaperModel* > HistoryExamPaper;
};

#endif // USERINFO_H
