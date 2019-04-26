#include "ExamRoomModelView.h"
#include <QStringListModel>

ExamRoomModelView::ExamRoomModelView(DataBaseManager *dbManager)
{
    DBManager = dbManager;
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
    examRoom->ExamPaper->add(true,true,"sadsafdsfq",12,"A","123","234","3524","4532");
    // TODO: 该数据模型在选择列表中的试卷时自动生成，也可手动添加
    examRoom->ExamPaperView = new ExamPaperDelegate(examRoom->ExamPaper);

    examRoom->QuestionLib = new ExamPaperModel();
    // 该数据模型通过初始化时遍历数据库来生成
    DBManager->searchExamQuestionLib(examRoom->QuestionLib);
    examRoom->QuestionLibView = new ExamPaperDelegate(examRoom->QuestionLib);

    examRoom->AllPaperList = new QStringList();
    examRoom->AllPaperList->append("测试信息");
    // TODO: 遍历数据库填充StringList
    examRoom->AllPaperListModel = new QStringListModel();
    examRoom->AllPaperListModel->setStringList(*examRoom->AllPaperList);
}

/**
 * @brief ExamRoomModelView::SetPaper
 * @param ExamPaperName
 * @param ExamPaperID
 * 根据试卷名和试卷ID列表，从题库中获取题库中的题目
 */
int ExamRoomModelView::SetPaper(QString ExamPaperName, QStringList ExamQuestionsList)
{
    foreach(QString examQusetionID , ExamQuestionsList)
    {
        ExamChoiceQusetion* ecq = FindQuestionByID(examQusetionID);
        if(ecq != nullptr)
        {
            examRoom->ExamPaper->add(ecq);
        }

    }
    return 0;
}

/**
 * @brief ExamRoomModelView::FindQuestionByID
 * @param ID
 * @return
 * 根据试题ID查询并返回题目
 */
ExamChoiceQusetion* ExamRoomModelView::FindQuestionByID(QString ID)
{
    foreach(ExamChoiceQusetion* Question, examRoom->QuestionLib->getExamList())
    {
        if(Question->getNumber() == ID.toInt())
        {
            return Question;
        }
    }
    return nullptr;
}

/**
 * @brief ExamRoomModelView::GetQuestionLib
 * @param exampaper
 * 从数据库遍历并初始化题库
 */
void ExamRoomModelView::GetQuestionLib(ExamPaperModel *exampaper)
{

}

