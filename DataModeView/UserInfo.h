#ifndef USERINFO_H
#define USERINFO_H

#include <QString>

class UserInfo
{
public://属性set方法
    UserInfo();
    void setUserID(int getUserID);
    void setUserName(QString Name);
public://属性get方法
    int getUserID();
    QString getUserName();
private://字段
    int m_id;
    QString m_userName;
};

#endif // USERINFO_H
