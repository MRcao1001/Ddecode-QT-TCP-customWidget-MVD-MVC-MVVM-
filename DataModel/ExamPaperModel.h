#ifndef EXAMPAPERMODEL_H
#define EXAMPAPERMODEL_H

#include <QAbstractItemModel>
#include <QSize>
#include <DataModel/ExamChoiceQusetion.h>
#include <QMutex>
#include <qglobal.h>
#include <QDataStream>
class ExamPaperModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ExamPaperModel(QObject *parent = nullptr);
    ~ExamPaperModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    ///向模型中添加数据
    void add(bool isMarkd, bool isCollection, QString questionTxt, QString score, QString trueResult, QString ResultA, QString ResultB, QString ResultC, QString ResultD);
    void add(ExamChoiceQusetion* examChoiceQusetion);
    ///以下标来获取模型中的Item
    ExamChoiceQusetion *at(int index);
    void remove(int index);
    void Clear();
    friend QDataStream &operator<<(QDataStream & , const ExamPaperModel &);
    friend QDataStream &operator>>(QDataStream & , ExamPaperModel &);
public:
    /// 获取模型中的试题集合
    QList<ExamChoiceQusetion* > getExamList();
    QString PaperName;
    /// 考试时间（min）
    QString TotalTestTime;
    QString TotalScore;
    int ExamNumber = 0;
private:
    QList<ExamChoiceQusetion* > m_examChoiceQusetionList;
    int indexNumber;
    QMutex *mutex;
signals:
    void selectionChanged();
};


#endif // EXAMPAPERMODEL_H
