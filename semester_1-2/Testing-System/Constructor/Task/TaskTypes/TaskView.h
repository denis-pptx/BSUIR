#ifndef TASKVIEW_H
#define TASKVIEW_H

#include <QDebug>
#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>

namespace Ui {
class TaskView;
}

// Максимальная длина имени задания
#define MAX_TASK_NAME_LEN 20

// ВИЗУАЛЬНАЯ ЧАСТЬ ЗАДАНИЯ
class TaskView : public QWidget
{
    Q_OBJECT

public:
    explicit TaskView(QWidget *parent);
    ~TaskView();

signals:
    // Задание и название задания изменено
    void taskEdited();
    void nameEdited();

protected:
    Ui::TaskView *ui;

    // layout и виджет с вариантами ответов
    QGridLayout* optionsLayout;
    QWidget* optionsWidget;
};

#endif // TASKVIEW_H
