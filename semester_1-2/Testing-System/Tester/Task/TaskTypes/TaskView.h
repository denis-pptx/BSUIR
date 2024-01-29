#ifndef TASKVIEW_H
#define TASKVIEW_H

#include <QDebug>
#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>

namespace Ui {
class TaskView;
}

// ВИДЫ ОТВЕТОВ
enum Answers {
    RIGHT, // Правильные
    USER   // Пользователя
};

// ВИЗУАЛЬНАЯ ЧАСТЬ ЗАДАНИЯ
class TaskView : public QWidget
{
    Q_OBJECT

protected:
    Ui::TaskView *ui;

    // layout и виджет с вариантами ответов
    QGridLayout* optionsLayout;
    QWidget* optionsWidget;

    Answers currentAnswers;

public:
    explicit TaskView(QWidget *parent);
    ~TaskView();
};

#endif // TASKVIEW_H
