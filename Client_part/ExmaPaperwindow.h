#ifndef EXMAPAPERWINDOW_H
#define EXMAPAPERWINDOW_H

#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include "DataModel/ExamPaperModel.h"
#include "DataDelegate/ExamPaperDelegate.h"
#include <DataModeView/ExamRoomModelView.h>
#include "DataModel/ExamChoiceQusetion.h"
namespace Ui {
class ExmaPaperwindow;
}

class ExmaPaperwindow : public QWidget
{
    Q_OBJECT

public:
    explicit ExmaPaperwindow(QWidget *parent = 0);
    ~ExmaPaperwindow();
    void InitViewModelDelegate(ExamRoomModelView *ExamRoom);

private:

    void InitUI();
    int QustionIndex = 0;
    Ui::ExmaPaperwindow *ui;
    ExamRoomModelView *m_ExamRoom;
    QButtonGroup *btnGroup;
    ExamChoiceQusetion *CheckedQuestion ;
private slots:
    void on_Questions_clicked(const QModelIndex &index);
    void on_checkedA_toggled(bool checked);
    void on_checkedB_toggled(bool checked);
    void on_checkedC_toggled(bool checked);
    void on_checkedD_toggled(bool checked);
signals:
    void Checked(int num);
};

#endif // EXMAPAPERWINDOW_H
