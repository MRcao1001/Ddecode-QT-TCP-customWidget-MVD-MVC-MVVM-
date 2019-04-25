#ifndef EXAMROOMMODELVIEW_H
#define EXAMROOMMODELVIEW_H

#include <DataModel/ExamPaperModel.h>
#include <DataDelegate/ExamPaperDelegate.h>
#include <DataModel/UserInfoModel.h>
#include <DataDelegate/userinfodelegate.h>
#include <DataModel/ExamRoomModel.h>
class ExamRoomModelView
{

public:
    ExamRoomModelView();
    ExamRoomModel *examRoom;

    void InitModel();
};

#endif // EXAMROOMMODELVIEW_H
