#ifndef TASKVIEWWIDGET_H
#define TASKVIEWWIDGET_H

#include <QWidget>

namespace Ui {
class TaskViewWidget;
}

class TaskViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskViewWidget(QWidget *parent = nullptr);
    ~TaskViewWidget();


    void setTask(QWidget* task); // Установить задание в окно показа задания
    void setNoTasks();           // Надпись "NO TASKS"
    void setNoTest();            // Надпись "NO ACTIVE TEST"

private:
    Ui::TaskViewWidget *ui;


    QWidget* activeWidget; // Какой виджет сейчас стоит в окне
};

#endif // TASKVIEWWIDGET_H
