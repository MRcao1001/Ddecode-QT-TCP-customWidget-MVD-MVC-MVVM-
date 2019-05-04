#include "ExmaPaperwindow.h"
#include "ui_ExmaPaperwindow.h"



ExmaPaperwindow::ExmaPaperwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExmaPaperwindow)
{
    ui->setupUi(this);
    InitUI();
}

ExmaPaperwindow::~ExmaPaperwindow()
{
    delete ui;
}

void ExmaPaperwindow::InitViewModelDelegate(ExamRoomModelView* ExamRoom)
{
    this->m_ExamRoom = ExamRoom;
    ui->Questions->setModel(ExamRoom->examRoom->ExamPaper);
    ui->Questions->setItemDelegate(ExamRoom->examRoom->ExamPaperView);
}



void ExmaPaperwindow::InitUI()
{
    btnGroup = new QButtonGroup();
    btnGroup->addButton(ui->checkedA);
    btnGroup->addButton(ui->checkedB);
    btnGroup->addButton(ui->checkedC);
    btnGroup->addButton(ui->checkedD);
    btnGroup->addButton(ui->checkedNA);

}


void ExmaPaperwindow::on_Questions_clicked(const QModelIndex &index)
{
    QustionIndex = index.row();
    CheckedQuestion = m_ExamRoom->examRoom->ExamPaper->at(index.row());
    if(CheckedQuestion->getCheckResult() == "N/A")
    {
        ui->checkedNA->setChecked(true);
    }
    else if(CheckedQuestion->getCheckResult() == "A")
    {
        ui->checkedA->setChecked(true);
    }
    else if(CheckedQuestion->getCheckResult() == "B")
    {
        ui->checkedB->setChecked(true);
    }
    else if(CheckedQuestion->getCheckResult() == "C")
    {
        ui->checkedC->setChecked(true);
    }
    else if(CheckedQuestion->getCheckResult() == "D")
    {
        ui->checkedD->setChecked(true);
    }
    ui->QuestionNum->setText(QString::number(CheckedQuestion->getNumber()));
}

void ExmaPaperwindow::on_checkedA_toggled(bool checked)
{
    if(CheckedQuestion != nullptr && checked)
    {
        CheckedQuestion->setCheckResult("A");
        emit Checked(QustionIndex);
    }
}

void ExmaPaperwindow::on_checkedB_toggled(bool checked)
{
    if(CheckedQuestion != nullptr&& checked)
    {
        CheckedQuestion->setCheckResult("B");
        emit Checked(QustionIndex);
    }
}

void ExmaPaperwindow::on_checkedC_toggled(bool checked)
{
    if(CheckedQuestion != nullptr&& checked)
    {
        CheckedQuestion->setCheckResult("C");
        emit Checked(QustionIndex);
    }
}

void ExmaPaperwindow::on_checkedD_toggled(bool checked)
{
    if(CheckedQuestion != nullptr&& checked)
    {
        CheckedQuestion->setCheckResult("D");
        emit Checked(QustionIndex);
    }
}
