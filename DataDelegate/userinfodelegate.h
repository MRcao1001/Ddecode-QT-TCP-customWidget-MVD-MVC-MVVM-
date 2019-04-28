#ifndef USERINFODELEGATE_H
#define USERINFODELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <DataModel/UserInfoModel.h>
#include <DataModeView/UserInfoFrame.h>
class UserInfoDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit UserInfoDelegate(UserInfoModel *userInfoModel, QObject *parent = 0);
    ~UserInfoDelegate();

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    UserInfoModel *m_userInfoModel;
    UserInfoFrame *m_userInfoFrame;
    QMutex *mutex;
};

#endif // USERINFODELEGATE_H
