#include "ExamChoiceQusetionFrame.h"
#include "ui_ExamChoiceQusetionFrame.h"

ExamChoiceQusetionFrame::ExamChoiceQusetionFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ExamChoiceQusetionFrame)
{
    ui->setupUi(this);
}

ExamChoiceQusetionFrame::~ExamChoiceQusetionFrame()
{
    delete ui;
}

void ExamChoiceQusetionFrame::setNumber(const int number)
{
    ui->Number->setText(QString::number(number));
}

void ExamChoiceQusetionFrame::setQuestion(const QString questionTxt)
{
    ui->Question->setText(questionTxt);
}

void ExamChoiceQusetionFrame::setScore(const int score)
{
    ui->score->setText(QString::number(score));
}

void ExamChoiceQusetionFrame::setTrueResult(const int result)
{

}

void ExamChoiceQusetionFrame::setCheckResult(const int result)
{

}

void ExamChoiceQusetionFrame::setResultA(QString Result)
{
    ui->Result_A->setText(Result);
}

void ExamChoiceQusetionFrame::setResultB(QString Result)
{
    ui->Result_B->setText(Result);
}

void ExamChoiceQusetionFrame::setResultC(QString Result)
{
    ui->Result_C->setText(Result);
}

void ExamChoiceQusetionFrame::setResultD(QString Result)
{
    ui->Result_D->setText(Result);
}

void ExamChoiceQusetionFrame::setSelected(bool selected)
{
    if(selected)
    {
        this->setStyleSheet("#ExamChoiceQusetionFrame{border:2px solid red;}");
    }
    else{
        this->setStyleSheet("#ExamChoiceQusetionFrame{border:none;}");
    }
    emit OnSelected();
}
