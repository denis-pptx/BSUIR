#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_addProductButton_clicked()
{
    closeWindows();
    productMenuAdd->activate();

    if(productMenuAdd->exec() == QDialog::Accepted) {

        warehouse.push_back(
                    Product(productMenuAdd->getName(), productMenuAdd->getAmount(),
                            productMenuAdd->getPrice(), productMenuAdd->getDate()));

        printProducts();
        setSpinboxesRange();
        fileRewrite();
    }
}

void MainWindow::on_editProductButton_clicked()
{
    int editNumber = ui->editSpinBox->value();

    closeWindows();
    if (!warehouse.size()) {
        QMessageBox::warning(this, "Warning", "Список пуст");;
        return;
    }

    node_list::list<Product>::iterator it = warehouse.begin();
    for (int i = 0; i < editNumber - 1; i++)
        ++it;

    productMenuEdit->activate(it);

    if(productMenuEdit->exec() == QDialog::Accepted) {

        (*it).setName(productMenuEdit->getName());
        (*it).setAmount(productMenuEdit->getAmount());
        (*it).setPrice(productMenuEdit->getPrice());
        (*it).setDate(productMenuEdit->getDate());

        printProducts();
        fileRewrite();
    }

}

void MainWindow::on_productView_doubleClicked(const QModelIndex &index)
{
    ui->editSpinBox->setValue(index.row() + 1);
    on_editProductButton_clicked();
}


