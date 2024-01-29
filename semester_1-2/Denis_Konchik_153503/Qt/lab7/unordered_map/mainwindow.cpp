#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    hash_table = new my_hash::unordered_map<QString, QString, HashFunctor>(10);
    menu = new Menu;

    model = new QStandardItemModel;
    printHashTable();

    setWindowTitle("unordered_map");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printHashTable() {
    delete model;

    int arr_size = hash_table->get_arr_size();
    list<pair<const QString, QString>>* arr = hash_table->get_arr();

    model = new QStandardItemModel(0, arr_size, this);

    for (int i = 0; i < arr_size; i++)
        model->setHeaderData(i, Qt::Horizontal, QString::number(i));

    ui->tableView->setModel(model);


    for (int i = 0; i < arr_size; i++) {
        int row = 0;

        for (const auto& it : arr[i]) {
            if (row > model->rowCount() - 1)
                model->insertRow(row);

            QModelIndex index = model->index(row++, i);

            QString text = it.first + '\n' + it.second;
            model->setData(index, text);
            model->item(index.row(), index.column())->setEditable(false);
        }
    }

    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->amountLabel->setText(QString::number(hash_table->get_N()));
}

void MainWindow::on_insertButton_clicked()
{
    menu->activate(MenuSettings::ADD);

    if(menu->exec() == QDialog::Accepted) {
        hash_table->insert(make_pair(menu->getKey(), menu->getValue()));
        printHashTable();
    }
}


void MainWindow::on_eraseButton_clicked()
{
    menu->activate(MenuSettings::ERASE);

    if (menu->exec() == QDialog::Accepted) {
        hash_table->erase(menu->getKey());
        printHashTable();
    }
}


void MainWindow::on_clearButton_clicked()
{
    hash_table->clear();
    printHashTable();
}


void MainWindow::on_searchButton_clicked()
{
    menu->activate(MenuSettings::FIND);

    if (menu->exec() == QDialog::Accepted) {

        pair<const QString, QString>* item = hash_table->search(menu->getKey());

        menu->setKey(menu->getKey());
        menu->setValue(!item ? "NOT FOUND" : (*item).second);

        menu->activate(MenuSettings::SHOW);
    }
}


void MainWindow::on_equalButton_clicked()
{
    (*hash_table)[ui->keyEdit->text()] = ui->valueEdit->text();
    printHashTable();
}


void MainWindow::on_returnButton_clicked()
{
    ui->returnValueEdit->setText((*hash_table)[ui->returnKeyEdit->text()]);
    printHashTable();
}

