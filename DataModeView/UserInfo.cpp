#include "UserInfo.h"

UserInfo::UserInfo()
{
    m_userName = "";
    m_id = 0;
}

void UserInfo::setUserID(int ID)
{
    this->m_id = ID;
}

void UserInfo::setUserName(QString Name)
{
    this->m_userName = Name;
}

int UserInfo::getUserID()
{
    return m_id;
}

QString UserInfo::getUserName()
{
    return m_userName;
}
