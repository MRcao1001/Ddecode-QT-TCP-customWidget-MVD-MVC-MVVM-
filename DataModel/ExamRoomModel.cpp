#include "ExamRoomModel.h"

ExamRoomModel::ExamRoomModel(QObject *parent) : QObject(parent)
{

}

QDataStream & operator<<(QDataStream & output, const ExamRoomModel &obj)
{
    output <<obj.PastTestTime<<obj.AllowCopy<<obj.AllowPaste<<obj.AutoJudging<<obj.AutoStatistics;
    return output ;
}

QDataStream & operator>>(QDataStream & input, ExamRoomModel & obj)
{
    input >> obj.PastTestTime<<obj.AllowCopy<<obj.AllowPaste<<obj.AutoJudging<<obj.AutoStatistics;
    return input;
}

