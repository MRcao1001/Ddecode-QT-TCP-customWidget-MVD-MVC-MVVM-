#include "ExmaPaperwindow.h"
#include "ui_ExmaPaperwindow.h"

ExmaPaperwindow::ExmaPaperwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExmaPaperwindow)
{
    ui->setupUi(this);
    InitViewModelDelegate();
}

ExmaPaperwindow::~ExmaPaperwindow()
{
    delete ui;
}

void ExmaPaperwindow::InitViewModelDelegate()
{
    m_examPaperModel = new ExamPaperModel(this);
    m_examPaperDelegate = new ExamPaperDelegate(m_examPaperModel, this);
    ui->Questions->setModel(m_examPaperModel);
    ui->Questions->setItemDelegate(m_examPaperDelegate);
}
