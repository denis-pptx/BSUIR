#include "MainWindow/mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::checkTasksLimit() {
    if (test->size() == MAX_TASK_NUM) {
        ui->addTaskButton->setEnabled(false);
        ui->removeTaskButton->setEnabled(true);
    } else if (test->size() == MIN_TASK_NUM) {
        ui->addTaskButton->setEnabled(true);
        ui->removeTaskButton->setEnabled(false);
    } else {
        ui->addTaskButton->setEnabled(true);
        ui->removeTaskButton->setEnabled(true);
    }
}
