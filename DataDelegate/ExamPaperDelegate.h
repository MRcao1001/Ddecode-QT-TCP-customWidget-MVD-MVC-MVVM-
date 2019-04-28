#ifndef EXAMPAPERDELEGATE_H
#define EXAMPAPERDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <DataModel/ExamPaperModel.h>
#include <DataModel/ExamChoiceQusetion.h>
#include <DataModeView/ExamChoiceQusetionFrame.h>
class ExamPaperDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ExamPaperDelegate(ExamPaperModel *examPaperModel, QObject *parent = 0);
    ~ExamPaperDelegate();

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
private:
    ExamPaperModel *m_examPaperModel;
    ExamChoiceQusetionFrame *m_examChoiceQusetionFrame;
    QMutex *mutex;
    int parentHeight;
};
#endif // EXAMPAPERDELEGATE_H
