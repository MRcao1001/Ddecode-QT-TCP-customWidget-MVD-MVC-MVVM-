#ifndef USERINFOMODEL_H
#define USERINFOMODEL_H

#include <QAbstractItemModel>
#include <QSize>
#include <DataModel/UserInfo.h>
class UserInfoModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit UserInfoModel(QObject *parent = nullptr);
    ~UserInfoModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    ///向模型中添加数据
    void add(QString IP, QString Port, QString ID, QString Name, QString Ticket);
    void add(UserInfo* userInfo);
    ///以下标来获取模型中的Item
    UserInfo *at(int index);
    void Clear();
private:
    QList<UserInfo* > m_userInfoList;
    int indexNumber;
};

#endif // USERINFOMODEL_H
