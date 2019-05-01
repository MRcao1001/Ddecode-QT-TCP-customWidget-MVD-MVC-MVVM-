#ifndef EXAMCHOICEQUSETION_H
#define EXAMCHOICEQUSETION_H

#include <QString>
#include <QMetaType>
#include <QDataStream>
enum Result{
    N = 0,
    A = 1,
    B,
    C,
    D
};
class ExamChoiceQusetion
{
public:
    ExamChoiceQusetion();
    bool getMark();
    bool getCollection();
    int getNumber();
    QString getQuestion();
    QString getScore();
    QString getTrueResult();
    QString getCheckResult();
    QString getResultA();
    QString getResultB();
    QString getResultC();
    QString getResultD();
public:
    void setNumber(int number);
    void setQuestion(QString questionTxt);
    void setScore(QString score);
    void setTrueResult(QString result);
    void setCheckResult(QString result);
    void setResultA(QString Result);
    void setResultB(QString Result);
    void setResultC(QString Result);
    void setResultD(QString Result);
    friend QDataStream &operator<<(QDataStream & , const ExamChoiceQusetion &);
    friend QDataStream &operator>>(QDataStream & , ExamChoiceQusetion &);
private:
    bool m_isMarked;
    bool m_isCollection;
    int m_number;
    QString m_score;
    QString m_trueResult;
    QString m_checkResult;
    QString m_questionText;
    QString m_Result_A;
    QString m_Result_B;
    QString m_Result_C;
    QString m_Result_D;
};
Q_DECLARE_METATYPE(ExamChoiceQusetion);
#endif // EXAMCHOICEQUSETION_H
