#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), menu(new Menu)
{
    ui->setupUi(this);

    model = new QStandardItemModel(0, 2, this);
    model->setHeaderData(0, Qt::Horizontal, "Key");
    model->setHeaderData(1, Qt::Horizontal, "Value");
    ui->tableView->setModel(model);

    setWindowTitle("map");
    setFixedSize(size());


   // my_map::map<QString, QString>::it_list it = bts.begin_l();
   // my_map::map<QString, QString>::it_list it2 = bts.end_l();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printBts()
{

    delete model;
    model = new QStandardItemModel(0, 2, this);

    model->setHeaderData(0, Qt::Horizontal, "Key");
    model->setHeaderData(1, Qt::Horizontal, "Value");

    ui->tableView->setModel(model);

    for (const auto& item : bts) {
        model->insertRow(model->rowCount());

        QModelIndex index = model->index(model->rowCount() - 1, 0);
        model->setData(index, item.first);
        model->item(index.row(), index.column())->setEditable(false);

        index = model->index(model->rowCount() - 1, 1);
        model->setData(index, item.second);
        model->item(index.row(), index.column())->setEditable(false);

    }
}

void MainWindow::on_insertButton_clicked()
{

    menu->activate(MenuSettings::ADD);

    if(menu->exec() == QDialog::Accepted) {
        bts.insert(make_pair(menu->getKey(), menu->getValue()));
        printBts();
    }
}


void MainWindow::on_eraseButton_clicked()
{
    menu->activate(MenuSettings::ERASE);

    if (menu->exec() == QDialog::Accepted) {
        bts.erase(menu->getKey());
        printBts();
    }
}


void MainWindow::on_clearButton_clicked()
{
    bts.clear();
    printBts();
}


void MainWindow::on_searchButton_clicked()
{
    menu->activate(MenuSettings::FIND);

    if (menu->exec() == QDialog::Accepted) {

        auto it = bts.find(menu->getKey());

        menu->setKey(menu->getKey());
        menu->setValue(it == bts.end() ? "NOT FOUND" : (*it).second);

        menu->activate(MenuSettings::SHOW);
    }
}





void MainWindow::on_equalButton_clicked()
{
    bts[ui->keyEdit->text()] = ui->valueEdit->text();
    printBts();
}


void MainWindow::on_returnButton_clicked()
{
    ui->returnValueEdit->setText(bts[ui->returnKeyEdit->text()]);
    printBts();
}


void MainWindow::on_printButton_clicked()
{
    bts.print();
}







void MainWindow::print_iterator() {
    if (it == bts.end()) {
        ui->iteratorEdit->setText("bts.end()");
        ui->iteratorKey->setText("bts.end()");
        ui->iteratorEdit->setReadOnly(true);
    }
    else {
        ui->iteratorEdit->setText((*it).second);
        ui->iteratorKey->setText((*it).first);
        ui->iteratorEdit->setReadOnly(false);
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->comboBox->currentText() == "begin")
        it = bts.begin();
    else
        it = bts.end();

    print_iterator();
}


void MainWindow::on_plus_equal_Button_clicked()
{
    it = it + ui->it_plus_equal->value();
    print_iterator();
}


void MainWindow::on_minus_equal_Button_clicked()
{
    it = it - ui->it_minus_equal->value();
    print_iterator();
}


void MainWindow::on_iteratorEdit_Button_clicked()
{
    if (it != bts.end())
        (*it).second = ui->iteratorEdit->text();

    print_iterator();

    printBts();
}


void MainWindow::on_updateButton_clicked()
{
    print_iterator();
}

