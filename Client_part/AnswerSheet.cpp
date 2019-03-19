#include "AnswerSheet.h"
#include "ui_AnswerSheet.h"

AnswerSheet::AnswerSheet(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::AnswerSheet)
{
    ui->setupUi(this);
}

AnswerSheet::~AnswerSheet()
{
    delete ui;
}
