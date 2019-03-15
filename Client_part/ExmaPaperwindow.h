#ifndef EXMAPAPERWINDOW_H
#define EXMAPAPERWINDOW_H

#include <QWidget>
#include "DataModel/ExamPaperModel.h"
#include "DataDelegate/ExamPaperDelegate.h"
namespace Ui {
class ExmaPaperwindow;
}

class ExmaPaperwindow : public QWidget
{
    Q_OBJECT

public:
    explicit ExmaPaperwindow(QWidget *parent = 0);
    ~ExmaPaperwindow();
    void InitViewModelDelegate();
private:
    Ui::ExmaPaperwindow *ui;
    ExamPaperModel *m_examPaperModel;
    ExamPaperDelegate *m_examPaperDelegate;
};

#endif // EXMAPAPERWINDOW_H
