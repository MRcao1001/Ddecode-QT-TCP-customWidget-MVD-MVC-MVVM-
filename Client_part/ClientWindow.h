#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QString>
#include <QTimer>
#include "TCP_part/TCPClient.h"
#include <DataModeView/ExamRoomModelView.h>
#include "ExmaPaperwindow.h"
#include "AnswerSheet.h"
#include "LeftBar.h"
namespace Ui {
class ClientWindow;
}

class ClientWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = 0);
    ~ClientWindow();
    void SetClient(TCPClient *tcp);
    // 该模块已经初始化完成,否则对于客户端发来的请求不予理会
    bool InitFinish = false;
    void InitUserInfo(QString LoginInfo);
private:
    Ui::ClientWindow *ui;
    // TCP客户端实例
    TCPClient *m_tcpclient;
    // 样式文件实例
    QString qss_Checked;
    QString qss_Unchecked;
    // 考场模型
    ExamRoomModelView *ExamRoom;
    // 答卷组件
    ExmaPaperwindow *examPaperWindow;
    // 答题卡组件
    AnswerSheet *answerSheet;
    // 用户数据模型
    UserInfo *userInfo;
    // 考试记录数据源和模型
    QStringList *ExamHiStoryList;
    QStringListModel *ExamHistoryModel;
    // 消息通知数据源和模型
    QStringList *InfoList;
    QStringListModel *InfoListModel;
    QTimer *ExamRoomStartAndStopTimer;
    bool Marked = false;
    void InitUI();
    void InitExamRoom();
    void SetConnect();
    void SetTopBarButtonStyleDefult();
    // 初始化考试记录数据源
    void InitExamHistory();
    // 初始化消息通知数据源
    void InitInfo();
public slots:
    // 考试开始执行函数
    void ExaminationBegins(QString ExamRoomInfo);
    // 结束考试执行函数
    void markExamPapers();
    // 标题选项卡切换
    void ToolButtonCliced();
    // 获取/更新考试记录数据源
    void GetExamHistory(QString Historys);
    // 获取/更新消息列表
    void GetInfomation(QString Infomation);
    // 计时器更新信号
    void ExamRoomStartAndStop();
private slots:
    void on_HandInHand_clicked();
    void on_EditInfo_clicked();

};

#endif // CLIENTWINDOW_H
