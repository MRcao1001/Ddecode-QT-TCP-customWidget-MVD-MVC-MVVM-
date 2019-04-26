#include "ExamChoiceQusetion.h"

ExamChoiceQusetion::ExamChoiceQusetion()
{
    this->m_isMarked = false;
    this->m_isCollection = false;
    this->m_number = 1;
    this->m_questionText = "";
    this->m_score = 0;
    this->m_checkResult = 0;
    this->m_trueResult = 0;
}



int ExamChoiceQusetion::getNumber()
{
    return m_number;
}

QString ExamChoiceQusetion::getQuestion()
{
    return m_questionText;
}

int ExamChoiceQusetion::getScore()
{
    return m_score;
}

int ExamChoiceQusetion::getTrueResult()
{
    return m_trueResult;
}

int ExamChoiceQusetion::getCheckResult()
{
    return m_checkResult;
}

QString ExamChoiceQusetion::getResultA()
{
    return m_Result_A;
}

QString ExamChoiceQusetion::getResultB()
{
    return m_Result_B;
}

QString ExamChoiceQusetion::getResultC()
{
    return m_Result_C;
}

QString ExamChoiceQusetion::getResultD()
{
    return m_Result_D;
}


void ExamChoiceQusetion::setNumber(int number)
{
    this->m_number = number;
}

void ExamChoiceQusetion::setQuestion(QString questionTxt)
{
    this->m_questionText = questionTxt;
}

void ExamChoiceQusetion::setScore(int score)
{
    this->m_score = score;
}

void ExamChoiceQusetion::setTrueResult(QString result)
{
    if(result>="A" && result <="D")
    {
        this->m_trueResult = result;
    }

}

void ExamChoiceQusetion::setCheckResult(QString result)
{
    if(result>="A" && result <="D")
    {
        this->m_checkResult = result;
    }
}

void ExamChoiceQusetion::setResultA(QString Result)
{
    this->m_Result_A = Result;
}

void ExamChoiceQusetion::setResultB(QString Result)
{
    this->m_Result_B = Result;
}

void ExamChoiceQusetion::setResultC(QString Result)
{
    this->m_Result_C = Result;
}

void ExamChoiceQusetion::setResultD(QString Result)
{
    this->m_Result_D = Result;
}
