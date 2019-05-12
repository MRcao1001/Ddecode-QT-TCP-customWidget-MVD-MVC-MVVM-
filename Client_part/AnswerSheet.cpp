#include "AnswerSheet.h"
#include "ui_AnswerSheet.h"

AnswerSheet::AnswerSheet(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::AnswerSheet)
{
    ui->setupUi(this);
    PushButtonList = new QList<QPushButton* >();
    //初始化流式布局
    flowLayout = new QFlowLayout();
    //ui->verticalLayout->addLayout(flowLayout);
    ui->mainArea->addLayout(flowLayout);
}

AnswerSheet::~AnswerSheet()
{
    delete ui;
    for(auto i : *PushButtonList)
    {
        i->deleteLater();
    }
    PushButtonList->clear();
    delete PushButtonList;
    flowLayout->deleteLater();
}

void AnswerSheet::InitAnswerSheet(ExamRoomModelView *ExamRoom)
{
    if(PushButtonList->count() >= 1)
    {
        for(auto i : *PushButtonList)
        {
            flowLayout->removeWidget(i);
            delete  i;
        }
        PushButtonList->clear();
        qInfo()<<"AnswerSheetClearFinish";
    }
    //根据试卷内容自动生成对应的按钮
    ExamPaperModel *examPaper = ExamRoom->examRoom->ExamPaper;
    for(auto examQuestion : examPaper->getExamList())
    {
        //创建答题卡按钮
        QPushButton * tempPushButton = new QPushButton(QString::number(examQuestion->getNumber()));
        //绑定信号槽
        connect(tempPushButton, &QPushButton::clicked, this, &AnswerSheet::AnswersheetClicked);
        flowLayout->addWidget(tempPushButton);
        PushButtonList->append(tempPushButton);
    }
}

void AnswerSheet::setAnswerSheetStyle(int num, int type)
{
   if(num >=0 && num < PushButtonList->count())
   {
       if(type == 1)
       {
           PushButtonList->at(num)->setStyleSheet("background: #007acc; color: #fff");
       }
       else {
           PushButtonList->at(num)->setStyleSheet("background: #fff; color: #007acc");
       }

   }
}

void AnswerSheet::AnswersheetClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    for(int i = 0; i < PushButtonList->length(); i++)
    {
        if(btn == PushButtonList->at(i))
        {
            emit LocateTo(i);
        }
    }
}
