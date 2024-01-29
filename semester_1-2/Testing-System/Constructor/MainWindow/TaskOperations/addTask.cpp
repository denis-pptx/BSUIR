#include "MainWindow/mainwindow.h"
#include "ui_mainwindow.h"


// Добавление задания в тест
void MainWindow::addTask() {
    // Показать меню выбора задания
    taskChoose->show();


    if (taskChoose->exec() != QDialog::Accepted) return;


    // Добавить в тест выбранный тип задания
    test->addTask(taskChoose->getTask());

    // Распечатать список заданий теста
    taskListViewPrint();

    ui->taskListView->setCurrentRow(test->size() - 1);

    // Показать выбранное задание
    ui->taskViewWidget->setTask(test->back());

    // Соединить изменение названия задания с функцией изменения названия задания в списке всех заданий
    connect(test->back(), &TaskView::nameEdited, this, &MainWindow::taskListViewPrint);

    checkTasksLimit();
}
