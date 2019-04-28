#include "ExamPaperDelegate.h"
ExamPaperDelegate::ExamPaperDelegate(ExamPaperModel *examPaperModel, QObject *parent)
{
    this->m_examPaperModel = examPaperModel;
    mutex = new QMutex();
    m_examChoiceQusetionFrame = new ExamChoiceQusetionFrame();
}

ExamPaperDelegate::~ExamPaperDelegate()
{
    if(m_examChoiceQusetionFrame)
    {
        m_examChoiceQusetionFrame->deleteLater();
        m_examChoiceQusetionFrame = nullptr;
    }
}

void ExamPaperDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        mutex->lock();
        ExamChoiceQusetion *examChoiceQuestion = m_examPaperModel->at(index.row());
        mutex->unlock();
        if(examChoiceQuestion != nullptr)
        {
            m_examChoiceQusetionFrame->setNumber(examChoiceQuestion->getNumber());
            m_examChoiceQusetionFrame->setQuestion(examChoiceQuestion->getQuestion());
            m_examChoiceQusetionFrame->setScore(examChoiceQuestion->getScore());
            m_examChoiceQusetionFrame->setResultA(examChoiceQuestion->getResultA());
            m_examChoiceQusetionFrame->setResultB(examChoiceQuestion->getResultB());
            m_examChoiceQusetionFrame->setResultC(examChoiceQuestion->getResultC());
            m_examChoiceQusetionFrame->setResultD(examChoiceQuestion->getResultD());
            m_examChoiceQusetionFrame->resize(option.rect.width(), option.rect.height());
            m_examChoiceQusetionFrame->setMinimumHeight(50);
            if(option.state & QStyle::State_Selected)
            {
                m_examChoiceQusetionFrame->setSelected(true);
            }
            else {
                m_examChoiceQusetionFrame->setSelected(false);
            }
            QPixmap pixmap = m_examChoiceQusetionFrame->grab();
            painter->drawPixmap(option.rect, pixmap);
            return;
        }
        QStyledItemDelegate::paint(painter,option,index);
    }
}

QSize ExamPaperDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight( size.height() + 100 );
    return size;
}
