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
    flowLayout->deleteLater();
}

void AnswerSheet::InitAnswerSheet(ExamRoomModelView *ExamRoom)
{
    if(PushButtonList->count() >= 1)
    {
        for(auto i : *PushButtonList)
        {
            flowLayout->removeWidget(i);
            PushButtonList->removeOne(i);
            i->deleteLater();
        }
    }
    //根据试卷内容自动生成对应的按钮
    ExamPaperModel *examPaper = ExamRoom->examRoom->ExamPaper;
    for(auto examQuestion : examPaper->getExamList())
    {
        QPushButton * tempPushButton = new QPushButton(QString::number(examQuestion->getNumber()));
        flowLayout->addWidget(tempPushButton);
        PushButtonList->append(tempPushButton);
    }
}

void AnswerSheet::setAnswerSheetStyle(int num)
{
   if(num >=0 && num < PushButtonList->count())
   {
       PushButtonList->at(num)->setStyleSheet("background: #800880");
   }
}
