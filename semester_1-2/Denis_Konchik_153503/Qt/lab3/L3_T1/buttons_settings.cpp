#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::setSpinboxesRange() {
    if (warehouse.size() == 0) {
        ui->editSpinBox->setRange(0, 0);
        ui->editSpinBox->setValue(0);
        ui->deleteSpinBox->setRange(0,0);
        ui->deleteSpinBox->setValue(0);
    }
    else {
        ui->editSpinBox->setRange(1, warehouse.size());
        ui->editSpinBox->setValue(1);
        ui->deleteSpinBox->setRange(1, warehouse.size());
        ui->deleteSpinBox->setValue(1);
    }
}

void MainWindow::closeWindows() {
    productMenuEdit->close();
    productMenuAdd->close();
    // productMenuView->close();
    viewWindow->close();
    sortMenu->close();
}

void MainWindow::setSpinBoxNumber(const QModelIndex& index)
{
    ui->deleteSpinBox->setValue(index.row() + 1);
    ui->editSpinBox->setValue(index.row() + 1);
}


void MainWindow::on_storedFromSpinBox_valueChanged(int arg1)
{
    if (arg1 > ui->storedToSpinBox->value())
        ui->storedToSpinBox->setValue(arg1);
}



void MainWindow::on_priceFromSpinBox_valueChanged(double arg1)
{
    if (arg1 > ui->priceToSpinBox->value())
        ui->priceToSpinBox->setValue(arg1);
}



void MainWindow::on_amountFromSpinBox_valueChanged(int arg1)
{
    if (arg1 > ui->amountToSpinBox->value())
        ui->amountToSpinBox->setValue(arg1);
}


