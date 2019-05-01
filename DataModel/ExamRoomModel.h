#ifndef EXAMROOMMODEL_H
#define EXAMROOMMODEL_H

#include <QObject>
#include <QDataStream>
#include <DataModel/ExamPaperModel.h>
#include <DataDelegate/ExamPaperDelegate.h>
#include <DataModel/UserInfoModel.h>
#include <DataDelegate/userinfodelegate.h>
#include <QStringListModel>
/**
 * @brief The ExamRoomModel class
 * ExamRoomModel ExamRoomModelView 是 Client 和 Server 工作的基本单元
 * 它包含 试卷模型 试题库模型 考生集模型
 */
class ExamRoomModel : public QObject
{
    Q_OBJECT
public:
    explicit ExamRoomModel(QObject *parent = nullptr);
    /// 试卷集合
    QStringList *AllPaperList;
    QStringListModel *AllPaperListModel;
    /// 试卷模型和视图委托
    ExamPaperModel *ExamPaper;
    ExamPaperDelegate *ExamPaperView;
    /// 题库模型和视图委托
    ExamPaperModel *QuestionLib;
    ExamPaperDelegate *QuestionLibView;
    /// 考生集模型和视图委托
    UserInfoModel *UserList;
    UserInfoDelegate *UserListView;
    ///当前用户的身份(考生还是监考者)
    bool UserType;
    /// 考试时间（min）
    int TotalTestTime;
    /// 已经过去的时间
    int PastTestTime = 0;
    /// 是否允许复制
    bool AllowCopy = false;
    /// 是否允许粘贴
    bool AllowPaste = false;
    /// 是否自动判卷
    bool AutoJudging = false;
    /// 是否自动统计不及格学生名单
    bool AutoStatistics = false;
public:
    friend QDataStream &operator<<(QDataStream & , const ExamRoomModel &);
    friend QDataStream &operator>>(QDataStream & , ExamRoomModel &);
signals:

public slots:
};

#endif // EXAMROOMMODEL_H
