#ifndef EXAMROOMMODELVIEW_H
#define EXAMROOMMODELVIEW_H

#include <DataModel/ExamPaperModel.h>
#include <DataDelegate/ExamPaperDelegate.h>
#include <DataModel/UserInfoModel.h>
#include <DataDelegate/userinfodelegate.h>
#include <DataModel/ExamRoomModel.h>
#include <DataModel/ExamChoiceQusetion.h>
#include <DataBase_patr/DataBaseManager.h>
class ExamRoomModelView
{

public:
    ExamRoomModelView(DataBaseManager *DBManager);
    ExamRoomModel *examRoom;
    DataBaseManager *DBManager;
    int TempExamQuestionNum = 0;
public:
    void InitModel();
    int SetPaper(ExamPaperModel *ExamPaper, QStringList ExamQuestionsList, QString PaperName);
    ExamChoiceQusetion *FindQuestionByID(QString ID);
    void GetQuestionLib(ExamPaperModel *paperModel);
    void GetPaperLib(QStringList *paperList);
    QStringList GetPaperQuestionList(QString PaperName);
    QStringList GetQuestionIDList(QString PaperName);
    int SavePaperToLib(int type);
    int SaveQuestionToLib(ExamChoiceQusetion* question, int type);
    int DeleteQuestion(ExamChoiceQusetion* question,int index);
    int DeletePaperInfo(QString PaperName);
    QString serialization();
    int re_serialization(QString InfoList);
    // 该考场的试卷总分
    int TotalScore = 0;
};

#endif // EXAMROOMMODELVIEW_H
