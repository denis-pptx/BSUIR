#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::setSpinboxesRange() {
    if (statement.size() == 0) {
        ui->editSpinBox->setRange(0, 0);
        ui->editSpinBox->setValue(0);
        ui->deleteSpinBox->setRange(0,0);
        ui->deleteSpinBox->setValue(0);
    }
    else {
        ui->editSpinBox->setRange(1, statement.size());
        ui->editSpinBox->setValue(1);
        ui->deleteSpinBox->setRange(1, statement.size());
        ui->deleteSpinBox->setValue(1);
    }
}

void MainWindow::closeWindows() {
    enrolleeMenuAdd->close();
    enrolleeMenuEdit->close();
    // enrolleeMenuView->close();
    sortMenu->close();
    viewWindow->close();
}

void MainWindow::setSpinBoxNumber(const QModelIndex& index)
{
    ui->deleteSpinBox->setValue(index.row() + 1);
    ui->editSpinBox->setValue(index.row() + 1);
}
