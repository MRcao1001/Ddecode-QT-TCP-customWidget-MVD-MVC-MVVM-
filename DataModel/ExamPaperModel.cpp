#include "ExamPaperModel.h"

ExamPaperModel::ExamPaperModel(QObject *parent)
    : QAbstractListModel(parent)
{
    indexNumber = 1;
}

ExamPaperModel::~ExamPaperModel()
{

}

int ExamPaperModel::rowCount(const QModelIndex &parent) const
{
//    if (!parent.isValid())
//        return 0;
    return m_examChoiceQusetionList.size();
    // FIXME: Implement me!
}

int ExamPaperModel::columnCount(const QModelIndex &parent) const
{
//    if (!parent.isValid())
//        return 0;
    return 1;
    // FIXME: Implement me!
}

bool ExamPaperModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        int row = index.row();
        //根据行号从内部数据结构中定位，然后将其改编成value
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

QVariant ExamPaperModel::data(const QModelIndex &index, int role) const
{
    ExamChoiceQusetion* examChoiceQusetion = m_examChoiceQusetionList.at(index.row());
    if(examChoiceQusetion == nullptr)
    {
        return QVariant();
    }
    else
    {
        switch (role) {
        case Qt::UserRole:
            return examChoiceQusetion->getNumber();
        case Qt::DisplayRole:
            return examChoiceQusetion->getCheckResult();
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

void ExamPaperModel::add(bool isMarkd, bool isCollection, QString questionTxt, int score, QString trueResult, QString ResultA, QString ResultB, QString ResultC, QString ResultD)
{
    ExamChoiceQusetion* examChoiceQusetion = new ExamChoiceQusetion();
    examChoiceQusetion->setNumber(indexNumber);
    examChoiceQusetion->setQuestion(questionTxt);
    examChoiceQusetion->setScore(score);
    examChoiceQusetion->setTrueResult(trueResult);
    examChoiceQusetion->setResultA(ResultA);
    examChoiceQusetion->setResultB(ResultB);
    examChoiceQusetion->setResultC(ResultC);
    examChoiceQusetion->setResultD(ResultD);
    add(examChoiceQusetion);
    emit layoutChanged();
}
void ExamPaperModel::add(ExamChoiceQusetion* examChoiceQusetion)
{
    indexNumber += 1;
    m_examChoiceQusetionList.push_back(examChoiceQusetion);
    emit layoutChanged();
}
ExamChoiceQusetion *ExamPaperModel::at(int index)
{
    return m_examChoiceQusetionList.at(index);
}

QList<ExamChoiceQusetion *> ExamPaperModel::getExamList()
{
    return m_examChoiceQusetionList;
}
