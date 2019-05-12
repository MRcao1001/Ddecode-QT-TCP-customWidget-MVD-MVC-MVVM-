#ifndef ANSWERSHEET_H
#define ANSWERSHEET_H

#include <QFrame>
#include <QPushButton>
#include <QDebug>
#include <DataModeView/ExamRoomModelView.h>
#include <Public_part/QFlowLayout.h>
namespace Ui {
class AnswerSheet;
}

class AnswerSheet : public QFrame
{
    Q_OBJECT

public:
    explicit AnswerSheet(QWidget *parent = nullptr);
    ~AnswerSheet();
    void InitAnswerSheet(ExamRoomModelView *ExamRoom);
private:
    QList<QPushButton* > *PushButtonList;
    QFlowLayout *flowLayout;
    Ui::AnswerSheet *ui;
public slots:
    void setAnswerSheetStyle(int num, int type);
    void AnswersheetClicked();
signals:
    void LocateTo(int index);
};

#endif // ANSWERSHEET_H
