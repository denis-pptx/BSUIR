#include "mainwindow.h"
#include "ui_mainwindow.h"


// Распечатать список заданий теста
void MainWindow::taskListViewPrint() {

    ui->taskListView->clear();

    if (!test) return;

    for (int i = 0; i < test->size(); i++)
        ui->taskListView->addItem("");

    // Множество встреченных имен
    QSet<QString> met;

    for (int i = 0; i < test->size(); i++) {

        QString name = (*test)[i]->getName();

        QVector<int> repeatingNames;

        if (!met.contains(name)) {

            for (int j = i; j < test->size(); j++) {

                if ((*test)[j]->getName() == name)
                    repeatingNames.push_back(j);

            }

            if (repeatingNames.size() > 1) {
                int k = 1;
                for (const auto& j : repeatingNames)
                    ui->taskListView->item(j)->setText(QString::number(j + 1) + ". " + name + " (" + QString::number(k++) + ")");

            } else {
                ui->taskListView->item(i)->setText(QString::number(i + 1) + ". " + name);
            }

        }

        met.insert(name);
    }
}

void MainWindow::taskListView_clicked(const QModelIndex &index) {
    ui->taskViewWidget->setTask((*test)[index.row()]);
}

void MainWindow::taskListView_rowsMoved(const QModelIndex&, int start, int, const QModelIndex &, int row) {

    int from = start;
    int to = (start < row) ? (row - 1) : (row);

    test->moveTask(from, to);

    ui->taskListView->rowMoved(from, to);

    taskListViewPrint();

    ui->taskListView->setCurrentRow(to);


    ui->taskViewWidget->setTask((*test)[ui->taskListView->currentRow()]);
}

void MainWindow::on_taskPasted(int numberOfPasted, int currentRow) {

    ui->statusBar->taskPasted((*test)[numberOfPasted]->getName());

    test->pasteTask(numberOfPasted, currentRow + 1);
    taskListViewPrint();
    ui->taskViewWidget->setTask((*test)[currentRow + 1]);
    ui->taskListView->setCurrentRow(currentRow + 1);

    connect((*test)[currentRow + 1], &TaskView::nameEdited, this, &MainWindow::taskListViewPrint);

    checkTasksLimit();


}

void MainWindow::on_taskCopied(int numberOfCopied) {
    ui->statusBar->taskCopied((*test)[numberOfCopied]->getName());
}
