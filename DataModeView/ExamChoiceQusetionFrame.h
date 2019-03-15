#ifndef EXAMCHOICEQUSETIONFRAME_H
#define EXAMCHOICEQUSETIONFRAME_H

#include <QFrame>
namespace Ui {
class ExamChoiceQusetionFrame;
}

class ExamChoiceQusetionFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ExamChoiceQusetionFrame(QWidget *parent = 0);
    ~ExamChoiceQusetionFrame();
    void setNumber(const int number);
    void setQuestion(const QString questionTxt);
    void setScore(const int score);
    void setTrueResult(const int result);
    void setCheckResult(const int result);
    void setResultA(QString Result);
    void setResultB(QString Result);
    void setResultC(QString Result);
    void setResultD(QString Result);
    void setSelected(bool selected);
private:
    Ui::ExamChoiceQusetionFrame *ui;

signals:
    void OnSelected();
};

#endif // EXAMCHOICEQUSETIONFRAME_H
