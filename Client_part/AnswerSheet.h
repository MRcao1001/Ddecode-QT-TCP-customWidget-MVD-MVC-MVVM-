#ifndef ANSWERSHEET_H
#define ANSWERSHEET_H

#include <QFrame>

namespace Ui {
class AnswerSheet;
}

class AnswerSheet : public QFrame
{
    Q_OBJECT

public:
    explicit AnswerSheet(QWidget *parent = nullptr);
    ~AnswerSheet();

private:
    Ui::AnswerSheet *ui;
};

#endif // ANSWERSHEET_H
