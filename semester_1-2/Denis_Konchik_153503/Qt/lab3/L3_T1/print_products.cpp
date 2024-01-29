#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::printProducts()
{
    delete productModel;

    productModel = new QStandardItemModel(warehouse.size(), 4,this);
    QString productModelColumnName[] = {"Наименование", "Количество", "Цена", "Дата \nпоступления" };

    for (int column = 0; column < 4; column++)
        productModel->setHeaderData(column, Qt::Horizontal, productModelColumnName[column]);

    connect(ui->productView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(setSpinBoxNumber(const QModelIndex&)));
    ui->productView->setModel(productModel);

    int row = 0;
    for (node_list::list<Product>::iterator it = warehouse.begin(); it != nullptr; ++it, ++row) {

        for (int column = 0; column < productModel->columnCount(); column++) {

            QModelIndex index = productModel->index(row, column);
            productModel->setData(index, (*it).getColumnByIndex(column));
            productModel->item(row, column)->setEditable(false);
        }
    }

}

bool MainWindow::isSuitableProduct(node_list::list<Product>::iterator& it) {

    int days = (*it).getDate().daysTo(QDate::currentDate());
    double price = (*it).getPrice();
    int amount = (*it).getAmount();

    if (((ui->storedFromSpinBox->value() <= days && days <= ui->storedToSpinBox->value()) || !ui->storedCheckBox->isChecked()) &&
            ((ui->priceFromSpinBox->value() <= price && price <= ui->priceToSpinBox->value()) || !ui->priceCheckBox->isChecked()) &&
            ((ui->amountFromSpinBox->value() <= amount && amount <= ui->amountToSpinBox->value()) || !ui->amountCheckBox->isChecked()))
        return true;

    return false;
}

void MainWindow::printProductWithSettings()
{
    QStandardItemModel* modelWindow = new QStandardItemModel(0, 4,this);
    QString productModelColumnName[] = {"Наименование", "Количество", "Цена", "Дата \nпоступления" };

    for (int column = 0; column < 4; column++)
        modelWindow->setHeaderData(column, Qt::Horizontal, productModelColumnName[column]);

    viewWindow->setModel(modelWindow);

    int row = 0;
    for (node_list::list<Product>::iterator it = warehouse.begin(); it != nullptr; ++it) {

        if (isSuitableProduct(it)) {

            modelWindow->insertRow(row);

            for (int column = 0; column < modelWindow->columnCount(); column++) {

                QModelIndex index = modelWindow->index(row, column);
                modelWindow->setData(index, (*it).getColumnByIndex(column));
                modelWindow->item(row, column)->setEditable(false);
            }

            row++;
        }
    }


    if (modelWindow->rowCount() == 0) {
        QMessageBox::warning(this, "Warning", "Товары не найдены");;
    } else {
        viewWindow->setWindowTitle("Товары с параметрами");
        viewWindow->setFixedSize(ui->productView->size());
        viewWindow->show();
    }

}

void MainWindow::printExpectedProduct() {
    QStandardItemModel* modelWindow = new QStandardItemModel(0, 4,this);

    QString productModelColumnName[] = {"Наименование", "Цена", "Количество", "Дата последнего \nпоступления" };

    for (int column = 0; column < 4; column++)
        modelWindow->setHeaderData(column, Qt::Horizontal, productModelColumnName[column]);

    viewWindow->setModel(modelWindow);

    int row = 0;
    for (node_list::list<Product>::iterator it = warehouse.begin(); it != nullptr; ++it) {

        if ((*it).getAmount() == 0) {

            modelWindow->insertRow(row);

            for (int column = 0; column < modelWindow->columnCount(); column++) {

                QModelIndex index = modelWindow->index(row, column);
                modelWindow->setData(index, (*it).getColumnByIndex(column));
                modelWindow->item(row, column)->setEditable(false);
            }

            row++;
        }
    }

    if (modelWindow->rowCount() == 0) {
        QMessageBox::warning(this, "Warning", "Товары не найдены");;
    } else {
        viewWindow->setWindowTitle("Отсутствующие товары");
        viewWindow->setFixedSize(ui->productView->size());
        viewWindow->show();
    }
}

void MainWindow::printProductByName(QString product) {


    QStandardItemModel* modelWindow = new QStandardItemModel(0, 4,this);

    QString productModelColumnName[] = {"Наименование", "Цена", "Количество", "Дата \nпоступления" };

    for (int column = 0; column < 4; column++)
        modelWindow->setHeaderData(column, Qt::Horizontal, productModelColumnName[column]);

    viewWindow->setModel(modelWindow);

    int row = 0;
    for (node_list::list<Product>::iterator it = warehouse.begin(); it != nullptr; ++it) {

        if ((*it).getName() == product) {

            modelWindow->insertRow(row);

            for (int column = 0; column < modelWindow->columnCount(); column++) {

                QModelIndex index = modelWindow->index(row, column);
                modelWindow->setData(index, (*it).getColumnByIndex(column));
                modelWindow->item(row, column)->setEditable(false);
            }

            row++;
        }
    }

    if (modelWindow->rowCount() == 0) {
        QMessageBox::warning(this, "Warning", "Товары не найдены");;
    } else {
        viewWindow->setWindowTitle("Товары по названию");
        viewWindow->setFixedSize(ui->productView->size());
        viewWindow->show();
    }
}

