#include "ExamChoiceQusetion.h"

ExamChoiceQusetion::ExamChoiceQusetion()
{
    this->m_isMarked = false;
    this->m_isCollection = false;
    this->m_number = 1;
    this->m_questionText = "";
    this->m_score = "0";
    this->m_checkResult = "N/A";
    this->m_trueResult = "A";
}



int ExamChoiceQusetion::getNumber()
{
    return m_number;
}

QString ExamChoiceQusetion::getQuestion()
{
    return m_questionText;
}

QString ExamChoiceQusetion::getScore()
{
    return m_score;
}

QString ExamChoiceQusetion::getTrueResult()
{
    return m_trueResult;
}

QString ExamChoiceQusetion::getCheckResult()
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

void ExamChoiceQusetion::setScore(QString score)
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

QDataStream &operator<<(QDataStream &output, const ExamChoiceQusetion &obj)
{
    output<< obj.m_score << obj.m_number<<obj.m_Result_A<<obj.m_Result_B<<obj.m_Result_C<<obj.m_Result_D<<obj.m_isMarked<<obj.m_trueResult<<obj.m_checkResult<<obj.m_isCollection<<obj.m_questionText;
    return output;
}

QDataStream &operator>>(QDataStream &input, ExamChoiceQusetion &obj)
{
    input >> obj.m_score >> obj.m_number>>obj.m_Result_A>>obj.m_Result_B>>obj.m_Result_C>>obj.m_Result_D>>obj.m_isMarked>>obj.m_trueResult>>obj.m_checkResult>>obj.m_isCollection>>obj.m_questionText;
    return input;
}
