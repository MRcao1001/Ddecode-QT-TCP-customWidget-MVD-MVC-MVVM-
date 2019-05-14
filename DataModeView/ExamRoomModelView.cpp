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
    //examRoom->UserList->add("123","12345","1234","name","123243251");
    // 用户登陆时将生成的用户数据对象添加到用户数据视图模型中
    examRoom->UserListView = new UserInfoDelegate(examRoom->UserList );

    examRoom->ExamPaper = new ExamPaperModel();
    //examRoom->ExamPaper->add(true,true,"sadsafdsfq","12","A","123","234","3524","4532");
    // 该数据模型在选择列表中的试卷时自动生成，也可新建试卷手动添加
    examRoom->ExamPaperView = new ExamPaperDelegate(examRoom->ExamPaper);

    examRoom->QuestionLib = new ExamPaperModel();
    // 该数据模型通过初始化时遍历数据库来生成
    if(DBManager != nullptr)
    {
        GetQuestionLib(examRoom->QuestionLib);
    }
    examRoom->QuestionLibView = new ExamPaperDelegate(examRoom->QuestionLib);

    examRoom->AllPaperList = new QStringList();
    // 遍历数据库填充StringList
    if(DBManager != nullptr)
    {
        GetPaperLib(examRoom->AllPaperList);
    }
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
int  ExamRoomModelView::SavePaperToLib(int type)
{
    //将试卷保存到试卷库
    if(type == 0)
    {
        for(int i = 0; i< examRoom->AllPaperList->size();++i)
        {
            if(examRoom->AllPaperList->at(i).split(',').at(0) == examRoom->ExamPaper->PaperName)
            {
                return -9;
            }
        }
        examRoom->AllPaperList->append(examRoom->ExamPaper->PaperName+","+examRoom->ExamPaper->TotalTestTime);
        examRoom->AllPaperListModel->setStringList(*examRoom->AllPaperList);
        DBState state = DBManager->InsertNewPaper(examRoom->ExamPaper);
        if(state == SQLERROR)
            return -4;
    }
    else {
        DBState state = DBManager->UpdatePaperInfo(examRoom->ExamPaper);
        if(state == SQLERROR)
            return -4;
    }

    return 0;
}

/**
 * @brief ExamRoomModelView::SaveQuestionToLib 新增试题到题库
 * @param question
 * @return
 */
int ExamRoomModelView::SaveQuestionToLib(ExamChoiceQusetion *question, int type)
{
    //判断是否存在此ID的题目,如果保存现有的则判断是否现有，否则存为新的
    if(type == 0)
    {
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
    }
    question->setNumber(examRoom->QuestionLib->ExamNumber++);
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

int ExamRoomModelView::DeletePaperInfo(QString PaperName)
{
    DBState state = DBManager->DeletePaperInfo(PaperName);
    if(state == SQLERROR)
        return -4;
    for(int i = 0; i< examRoom->AllPaperList->size();++i)
    {
        if(examRoom->AllPaperList->at(i).split(',').at(0) == examRoom->ExamPaper->PaperName)
        {
            examRoom->AllPaperList->removeAt(i);
            examRoom->AllPaperListModel->setStringList(*examRoom->AllPaperList);
            return 0;
        }
    }
}



/**
 * @brief ExamRoomModelView::serialization
 * @return stringlist： 结构
 * 是否可以复制#是否可以粘贴#是否自动判卷#自动统计
 * 试卷名#试卷总时间
 * 试题1的信息（&分割）#试题2的信息（$分割）
 */
QString ExamRoomModelView::serialization()
{
    QString ExamRoomInfo;
    ExamRoomInfo.append(QString::number(examRoom->AllowCopy));
    ExamRoomInfo.append("##");
    ExamRoomInfo.append(QString::number(examRoom->AllowPaste));
    ExamRoomInfo.append("##");
    ExamRoomInfo.append(QString::number(examRoom->AutoJudging));
    ExamRoomInfo.append("##");
    ExamRoomInfo.append(QString::number(examRoom->AutoStatistics));

    QString ExamPaperInfo;
    ExamPaperInfo.append(examRoom->ExamPaper->PaperName);
    ExamPaperInfo.append("##");
    ExamPaperInfo.append(examRoom->ExamPaper->TotalTestTime);

    QString ExamQuestions;
    for(auto i : examRoom->ExamPaper->getExamList())
    {
        ExamQuestions.append(i->getScore()!= ""?i->getScore():"NOINFO!");
        ExamQuestions.append("$$");
        ExamQuestions.append(QString::number(i->getNumber())!= ""?QString::number(i->getNumber()):"NOINFO!");
        ExamQuestions.append("$$");
        ExamQuestions.append(i->getResultA()!=""?i->getResultA():"NOINFO!");
        ExamQuestions.append("$$");
        ExamQuestions.append(i->getResultB()!=""?i->getResultB():"NOINFO!");
        ExamQuestions.append("$$");
        ExamQuestions.append(i->getResultC()!=""?i->getResultC():"NOINFO!");
        ExamQuestions.append("$$");
        ExamQuestions.append(i->getResultD()!=""?i->getResultD():"NOINFO!");
        ExamQuestions.append("$$");
        ExamQuestions.append(i->getQuestion()!=""?i->getQuestion():"NOINFO!");
        ExamQuestions.append("$$");
        ExamQuestions.append(i->getTrueResult()!=""?i->getTrueResult():"N/A");
        if(i != examRoom->ExamPaper->getExamList().back())
        {
            ExamQuestions.append("##");
        }
    }
    QString tempList;
    tempList.append(ExamRoomInfo);
    tempList.append("%%");
    tempList.append(ExamPaperInfo);
    tempList.append("%%");
    tempList.append(ExamQuestions);
    return tempList;
}

int ExamRoomModelView::re_serialization(QString InfoListString)
{
    QStringList InfoList = InfoListString.split("%%");
    if(InfoList.length() == 3)
    {
        QString ExamRoomInfo = InfoList.at(0);
        QStringList ExamRoomInfoSplit = ExamRoomInfo.split("##");
        if(ExamRoomInfoSplit.length() == 4)
        {
            QVariant temp = ExamRoomInfoSplit.at(0);
            examRoom->AllowCopy = temp.toBool();
            temp = ExamRoomInfoSplit.at(1);
            examRoom->AllowPaste = temp.toBool();
            temp = ExamRoomInfoSplit.at(2);
            examRoom->AutoJudging = temp.toBool();
            temp = ExamRoomInfoSplit.at(3);
            examRoom->AutoStatistics = temp.toBool();
        }
        QString ExamPaperInfo = InfoList.at(1);
        QStringList ExamPaperInfoSplit = ExamPaperInfo.split("##");
        if(ExamPaperInfoSplit.length() == 2)
        {
            examRoom->ExamPaper->PaperName = ExamPaperInfoSplit.at(0);
            examRoom->ExamPaper->TotalTestTime = ExamPaperInfoSplit.at(1);
        }
        QString ExamQuestions = InfoList.at(2);
        QStringList ExamQuestionsSplit = ExamQuestions.split("##");
        for(auto ExamQuestionInfo : ExamQuestionsSplit)
        {
            ExamChoiceQusetion* examcq = new ExamChoiceQusetion();
            QStringList examinfo = ExamQuestionInfo.split("$$");
            if(examinfo.length() == 8)
            {
                examcq->setScore(examinfo.at(0));
                examcq->setNumber(examinfo.at(1).toInt());
                examcq->setResultA(examinfo.at(2));
                examcq->setResultB(examinfo.at(3));
                examcq->setResultC(examinfo.at(4));
                examcq->setResultD(examinfo.at(5));
                examcq->setQuestion(examinfo.at(6));
                examcq->setTrueResult(examinfo.at(7));
            }
            else {
                return -1;
            }
            examRoom->ExamPaper->add(examcq);

        }
    }
    return 0;
}





