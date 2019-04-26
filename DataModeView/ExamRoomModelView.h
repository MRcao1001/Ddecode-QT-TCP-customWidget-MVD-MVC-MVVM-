#ifndef EXAMROOMMODELVIEW_H
#define EXAMROOMMODELVIEW_H

#include <DataModel/ExamPaperModel.h>
#include <DataDelegate/ExamPaperDelegate.h>
#include <DataModel/UserInfoModel.h>
#include <DataDelegate/userinfodelegate.h>
#include <DataModel/ExamRoomModel.h>
#include <DataBase_patr/DataBaseManager.h>
class ExamRoomModelView
{

public:
    ExamRoomModelView(DataBaseManager *DBManager);
    ExamRoomModel *examRoom;
    DataBaseManager *DBManager;
    void InitModel();
    int SetPaper(QString ExamPaperName, QStringList ExamQuestionsList);
    ExamChoiceQusetion *FindQuestionByID(QString ID);
    void GetQuestionLib(ExamPaperModel *exampaper);
};

#endif // EXAMROOMMODELVIEW_H
