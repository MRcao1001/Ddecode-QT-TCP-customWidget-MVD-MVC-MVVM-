#include "UserInfo.h"

UserInfo::UserInfo()
{
    m_name = "";
    m_id = "0000000";
    m_ip = "127.0.0.1";
    m_Port = "0000";
    m_Ticket = "zn-000000";
}

void UserInfo::setUserID(QString ID)
{
    this->m_id = ID;
}

void UserInfo::setUserName(QString Name)
{
    this->m_name = Name;
}

void UserInfo::setUserIP(QString IP)
{
    this->m_ip = IP;
}

void UserInfo::setUserPort(QString Port)
{
    this->m_Port = Port;
}

void UserInfo::setUserTicket(QString Ticket)
{
    this->m_Ticket = Ticket;
}

QString UserInfo::getUserID()
{
    return m_id;
}

QString UserInfo::getUserName()
{
    return m_name;
}

QString UserInfo::getUserIP()
{
    return  m_ip;
}

QString UserInfo::getUserPort()
{
    return m_Port;
}

QString UserInfo::getUserTicket()
{
    return m_Ticket;
}
