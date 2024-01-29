#include "MainWindow/mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::connectTestSignals(Test* test) {
    connect(test, &Test::testRemoved, this, &MainWindow::slot_testRemoved);
    connect(test, &Test::testOpened, this, &MainWindow::slot_testOpened);
    connect(test, &Test::testCreated, this, &MainWindow::slot_testCreated);
    connect(test, &Test::testEdited, ui->fileNameLine, &TestNameLine::addStar);
    connect(test, &Test::testSaved, ui->fileNameLine, &TestNameLine::removeStar);
}

void MainWindow::slot_testRemoved() {

    // menuBar
    ui->SaveTest->setEnabled(false);
    ui->SaveAsTest->setEnabled(false);
    ui->RemoveTest->setEnabled(false);
    ui->exportPDF->setEnabled(false);

    // addTask, removeTask buttons
    ui->addTaskButton->setEnabled(false);
    ui->removeTaskButton->setEnabled(false);

    // timeCheckBox
    ui->timeCheckBox->setChecked(false);
    ui->timeCheckBox->setEnabled(false);

    // timeSpinBox
    ui->timeSpinBox->setEnabled(false);
    ui->timeSpinBox->setValue(1);

    // taskViewWidget, taskListView, fileNameLine
    ui->taskViewWidget->setNoTest();
    ui->taskListView->clear();
    ui->fileNameLine->setFileUrl(QUrl(""));
}

void MainWindow::slot_testOpened() {

    // menuBar
    ui->SaveTest->setEnabled(true);
    ui->SaveAsTest->setEnabled(true);
    ui->RemoveTest->setEnabled(true);
    ui->exportPDF->setEnabled(true);

    // addTask, removeTask buttons
    checkTasksLimit();

    // timeCheckBox, timeSpinBox
    ui->timeCheckBox->setEnabled(true);
    ui->timeCheckBox->setChecked(test->getPassingTime().first);
    ui->timeSpinBox->setEnabled(test->getPassingTime().first);
    ui->timeSpinBox->setValue(test->getPassingTime().second);

    // fileNameLine, taskChoose
    ui->fileNameLine->setFileUrl(test->getUrl());
    taskChoose->reset();

    // taskListView, taskViewWidget
    taskListViewPrint();
    if (test->size() > 0) {
        ui->taskListView->setCurrentRow(0);
        ui->taskViewWidget->setTask((*test)[0]);
    } else {
        ui->taskViewWidget->setNoTasks();
    }


    // Соединить изменение названия задания с изменением всех названий в списке заданий
    for (int i = 0; i < test->size(); i++)
        connect((*test)[i], &TaskView::nameEdited, this, &MainWindow::taskListViewPrint);
}

void MainWindow::slot_testCreated() {

    // menuBar
    ui->SaveTest->setEnabled(true);
    ui->SaveAsTest->setEnabled(true);
    ui->RemoveTest->setEnabled(true);
    ui->exportPDF->setEnabled(true);

    // addTask, removeTask buttons
    checkTasksLimit();

    // timeCheckBox, timeSpinBox
    ui->timeCheckBox->setEnabled(true);
    ui->timeCheckBox->setChecked(false);
    ui->timeSpinBox->setEnabled(false);
    ui->timeSpinBox->setValue(1);

    // taskViewWidget, taskListView, fileNameLine, taskChoose
    ui->taskViewWidget->setNoTasks();
    taskListViewPrint();
    ui->fileNameLine->setFileUrl(test->getUrl());
    taskChoose->reset();
}


