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
    void InitModel();
    int SetPaper(ExamPaperModel *ExamPaper, QStringList ExamQuestionsList, QString PaperName);
    ExamChoiceQusetion *FindQuestionByID(QString ID);
    void GetQuestionLib(ExamPaperModel *paperModel);
    void GetPaperLib(QStringList *paperList);
    QStringList GetPaperQuestionList(QString PaperName);
    QStringList GetQuestionIDList(QString PaperName);
    int SavePaperToLib();
    int SaveQuestionToLib(ExamChoiceQusetion* question);
    int DeleteQuestion(ExamChoiceQusetion* question,int index);
};

#endif // EXAMROOMMODELVIEW_H
