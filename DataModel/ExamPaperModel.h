#ifndef EXAMPAPERMODEL_H
#define EXAMPAPERMODEL_H

#include <QAbstractItemModel>
#include <QSize>
#include <DataModeView/ExamChoiceQusetion.h>
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
    void add(bool isMarkd, bool isCollection, QString questionTxt, int score, int trueResult, QString ResultA, QString ResultB, QString ResultC, QString ResultD);
    ///以下标来获取模型中的Item
    ExamChoiceQusetion *at(int index);
private:
    QList<ExamChoiceQusetion* > m_examChoiceQusetionList;
    int indexNumber;
signals:
    void selectionChanged();
};


#endif // EXAMPAPERMODEL_H
