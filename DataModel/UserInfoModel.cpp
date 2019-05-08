#include "UserInfoModel.h"

UserInfoModel::UserInfoModel(QObject *parent)
    : QAbstractListModel(parent)
{
    indexNumber = 10000;
}

UserInfoModel::~UserInfoModel()
{

}

int UserInfoModel::rowCount(const QModelIndex &parent) const
{
//    if (!parent.isValid())
//        return 0;
    return m_userInfoList.size();
    // FIXME: Implement me!
}

int UserInfoModel::columnCount(const QModelIndex &parent) const
{
//    if (!parent.isValid())
//        return 0;
    return 1;
    // FIXME: Implement me!
}

QVariant UserInfoModel::data(const QModelIndex &index, int role) const
{
    UserInfo* userinfo = m_userInfoList.at(index.row());
    if(userinfo == nullptr)
    {
        return QVariant();
    }
    else
    {
        switch (role) {
        case Qt::UserRole:
            return userinfo->getUserID();
        case Qt::DisplayRole:
            return userinfo->getUserName();
        case Qt::SizeHintRole:
            return QSize(0,100);
        default:
            return QVariant();
        }
    }
//    if (!index.isValid())
//        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

void UserInfoModel::add(QString IP, QString Port,QString ID, QString Name, QString Ticket)
{
    UserInfo* userinfo = new UserInfo();
    userinfo->setUserID(ID);
    userinfo->setUserName(Name);
    userinfo->setUserIP(IP);
    userinfo->setUserPort(Port);
    userinfo->setUserTicket(Ticket);
    m_userInfoList.push_back(userinfo);
    // 通知界面更新
    emit layoutChanged();
}

void UserInfoModel::add(UserInfo *userInfo)
{
    add(userInfo->getUserIP(), userInfo->getUserPort(),userInfo->getUserID(), userInfo->getUserName(), userInfo->getUserTicket());
}

UserInfo *UserInfoModel::at(int index)
{
    return m_userInfoList.at(index);
}

void UserInfoModel::Clear()
{
    m_userInfoList.clear();
}
