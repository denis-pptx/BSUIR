#include "MainWindow/mainwindow.h"
#include "ui_mainwindow.h"


// Удаление задания из теста
void MainWindow::removeTask()
{
    // Номер удаляемого задания
    int index = ui->taskListView->currentIndex().row();

    if (!(index >= 0 && index < test->size()))
        return;

    int ret = QMessageBox::warning(this, windowTitle(),
                                   QString("Do you want to delete task \"") + (*test)[index]->getName() + QString("\"?"),
                                   QMessageBox::Yes | QMessageBox::No
                                   );

    if (ret != QMessageBox::Yes)
        return;

    // Удаление задания
    test->removeTask(index);

    // Распечатать список заданий теста
    taskListViewPrint();

    ui->taskListView->rowDeleted(index);

    // Установка в окно показа другого задания
    if (test->size() == 0) {

        // Установить в окно показа задания "Нет заданий"
       ui->taskViewWidget->setNoTasks();

    } else {

        if (index >= test->size())
            index--;

        ui->taskViewWidget->setTask((*test)[index]);
        ui->taskListView->setCurrentRow(index);

    }

    checkTasksLimit();
}
