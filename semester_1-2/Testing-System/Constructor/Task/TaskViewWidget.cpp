#include "TaskViewWidget.h"
#include "ui_TaskViewWidget.h"

TaskViewWidget::TaskViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskViewWidget),
    activeWidget(nullptr)
{
    ui->setupUi(this);
}

TaskViewWidget::~TaskViewWidget()
{
    delete ui;
}

void TaskViewWidget::setTask(QWidget* task) {

    ui->label->hide();

    if (!activeWidget) {
        ui->gridLayout->addWidget(task, 0, 0);

    }
    else {
        ui->gridLayout->replaceWidget(activeWidget, task);
        activeWidget->hide();
    }

    task->show();

    activeWidget = task;
}

void TaskViewWidget::setNoTasks() {

    if (activeWidget)
        activeWidget->hide();

    ui->label->setText("NO TASKS");
    ui->label->show();
}

void TaskViewWidget::setNoTest() {

    if (activeWidget)
        activeWidget->hide();

    ui->label->setText("NO ACTIVE TEST");
    ui->label->show();
}

