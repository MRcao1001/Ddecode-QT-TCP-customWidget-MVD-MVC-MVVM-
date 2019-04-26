#include "UserInfoDelegate.h"

UserInfoDelegate::UserInfoDelegate(UserInfoModel *userInfoModel, QObject *parent): QStyledItemDelegate(parent)
{
    this->m_userInfoModel = userInfoModel;
    m_userInfoFrame = new UserInfoFrame();
}

UserInfoDelegate::~UserInfoDelegate()
{
    if(m_userInfoFrame)
    {
        m_userInfoFrame->deleteLater();
        m_userInfoFrame = nullptr;
    }
}

void UserInfoDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        UserInfo *userinfo = m_userInfoModel->at(index.row());
        if(userinfo != nullptr)
        {
            m_userInfoFrame->setName(userinfo->getUserName());
            m_userInfoFrame->SetIP(userinfo->getUserIP());
            m_userInfoFrame->SetTicket(userinfo->getUserTicket());
            m_userInfoFrame->resize(option.rect.width(),option.rect.height());
            if(option.state & QStyle::State_Selected)
            {
                m_userInfoFrame->setSelected(true);
            }
            else {
                m_userInfoFrame->setSelected(false);
            }
            QPixmap pixmap = m_userInfoFrame->grab();
            painter->drawPixmap(option.rect, pixmap);
            return;
        }
    }
    QStyledItemDelegate::paint(painter,option,index);
}
