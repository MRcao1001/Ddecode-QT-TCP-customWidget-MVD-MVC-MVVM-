#include "ExamRoomModelView.h"
#include <QStringListModel>

ExamRoomModelView::ExamRoomModelView()
{
    InitModel();
}

void ExamRoomModelView::InitModel()
{
    examRoom = new ExamRoomModel();

    examRoom->UserList = new UserInfoModel();
    examRoom->UserList->add("123","12345",1234,"name","123243251");
    // TODO: 用户登陆时将生成的用户数据对象添加到用户数据视图模型中
    examRoom->UserListView = new UserInfoDelegate(examRoom->UserList );

    examRoom->ExamPaper = new ExamPaperModel();
    examRoom->ExamPaper->add(true,true,"sadsafdsfq",12,1,"123","234","3524","4532");
    // TODO: 该数据模型在选择列表中的试卷时自动生成，也可手动添加
    examRoom->ExamPaperView = new ExamPaperDelegate(examRoom->ExamPaper);

    examRoom->QuestionLib = new ExamPaperModel();
    examRoom->QuestionLib->add(true,true,"sadsafdsfq",12,1,"123","234","3524","4532");
    // TODO: 该数据模型通过初始化时遍历数据库来生成
    examRoom->QuestionLibView = new ExamPaperDelegate(examRoom->QuestionLib);

    examRoom->AllPaperList = new QStringList();
    examRoom->AllPaperList->append("测试信息");
    // TODO: 遍历数据库填充StringList
    examRoom->AllPaperListModel = new QStringListModel();
    examRoom->AllPaperListModel->setStringList(*examRoom->AllPaperList);
}
