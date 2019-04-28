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
    // 用户登陆时将生成的用户数据对象添加到用户数据视图模型中
    examRoom->UserListView = new UserInfoDelegate(examRoom->UserList );

    examRoom->ExamPaper = new ExamPaperModel();
    examRoom->ExamPaper->add(true,true,"sadsafdsfq","12","A","123","234","3524","4532");
    // 该数据模型在选择列表中的试卷时自动生成，也可新建试卷手动添加
    examRoom->ExamPaperView = new ExamPaperDelegate(examRoom->ExamPaper);

    examRoom->QuestionLib = new ExamPaperModel();
    // 该数据模型通过初始化时遍历数据库来生成
    GetQuestionLib(examRoom->QuestionLib);
    examRoom->QuestionLibView = new ExamPaperDelegate(examRoom->QuestionLib);

    examRoom->AllPaperList = new QStringList();
    // 遍历数据库填充StringList
    GetPaperLib(examRoom->AllPaperList);
    examRoom->AllPaperListModel = new QStringListModel();
    examRoom->AllPaperListModel->setStringList(*examRoom->AllPaperList);


}

/**
 * @brief ExamRoomModelView::SetPaper
 * @param ExamPaperName
 * @param ExamPaperID
 * 根据试卷名和试卷ID列表，从题库中获取题库中的题目
 */
int ExamRoomModelView::SetPaper(ExamPaperModel *ExamPaper,QStringList ExamQuestionsList ,QString PaperInfo)
{
    ExamPaper->Clear();
    ExamPaper->PaperName = PaperInfo.split(',')[0];
    ExamPaper->TotalTestTime = PaperInfo.split(',')[1];
    foreach(QString examQusetionID , ExamQuestionsList)
    {
        ExamChoiceQusetion* ecq = FindQuestionByID(examQusetionID);
        if(ecq != nullptr)
        {
            ExamPaper->add(ecq);
        }

    }
    return 0;
}

/**
 * @brief ExamRoomModelView::FindQuestionByID 根据试题ID查询并返回题目
 * @param ID
 * @return
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
 * @brief ExamRoomModelView::GetQuestionLib 从数据库遍历并初始化题库
 * @param exampaper
 *
 */
void ExamRoomModelView::GetQuestionLib(ExamPaperModel* paperModel)
{
    DBManager->searchExamQuestionLib(paperModel);
}

/**
 * @brief ExamRoomModelView::GetPaperLib 从数据库遍历并初始化试卷库
 * @param paperList
 */
void ExamRoomModelView::GetPaperLib(QStringList *paperList)
{
    DBManager->searchExamPaper(paperList);
}

/**
 * @brief ExamRoomModelView::GetPaperQuestionList 根据试卷名获取试卷包含的题目ID列表
 * @param PaperName 试卷名
 * @return 题目ID列表
 */
QStringList ExamRoomModelView::GetPaperQuestionList(QString PaperName)
{
    QStringList getExamPaperQuestionList;
    DBManager->searchExamPaperQuestion(&getExamPaperQuestionList,PaperName);
    return getExamPaperQuestionList;
}

/**
 * @brief ExamRoomModelView::SavePaperToLib 保存当前试卷到试卷库
 */
int  ExamRoomModelView::SavePaperToLib()
{
    for(int i = 0; i< examRoom->AllPaperList->size();++i)
    {
        if(examRoom->AllPaperList->at(i).split(',').at(0) == examRoom->ExamPaper->PaperName)
        {
            return -9;
        }
    }
    examRoom->AllPaperList->append(examRoom->ExamPaper->PaperName);
    examRoom->AllPaperListModel->setStringList(*examRoom->AllPaperList);
    //将试卷保存到试卷库
    DBState state = DBManager->InsertNewPaper(examRoom->ExamPaper);
    if(state == SQLERROR)
        return -4;
    return 0;
}

/**
 * @brief ExamRoomModelView::SaveQuestionToLib 新增试题到题库
 * @param question
 * @return
 */
int ExamRoomModelView::SaveQuestionToLib(ExamChoiceQusetion *question)
{
    //判断是否存在此ID的题目
    for(auto i:examRoom->QuestionLib->getExamList())
    {
        if(i->getNumber() == question->getNumber())
        {
            //执行修改
            DBState state = DBManager->UpdataQuestion(question);
            if(state == SQLERROR)
                return -4;
            return 0;
        }
    }
    //执行新增
    DBState state = DBManager->InsertNewQuestion(question);
    if(state == SQLERROR)
        return -4;
    return 0;
}

int ExamRoomModelView::DeleteQuestion(ExamChoiceQusetion *question, int index)
{
    examRoom->QuestionLib->remove(index);
    //执行"删除"
    DBState state = DBManager->DeleteQuestion(question);
    if(state == SQLERROR)
        return -4;
    return 0;
}





