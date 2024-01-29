#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("L6_T2");
    setFixedSize(size());

    table = new HashTableMod(10);

    model = new QStandardItemModel;

    print();

    srand(time(NULL));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addButton_clicked()
{
    table->push(ui->addSpinBox->value());
    print();
}


void MainWindow::on_deleteButton_clicked()
{
    table->pop(ui->deleteSpinBox->value());
    print();
}

void MainWindow::print() {
    delete model;

    int arr_size = table->get_arr_size();
    stack<int>* arr = table->get_arr();

    stack<int>* tmp = new stack<int>[arr_size];
    for (int i = 0; i < arr_size; i++)
        tmp[i] = arr[i];

    model = new QStandardItemModel(0, arr_size, this);

    for (int i = 0; i < arr_size; i++)
        model->setHeaderData(i, Qt::Horizontal, QString::number(i));

    ui->tableView->setModel(model);


    for (int i = 0; i < arr_size; i++) {
        int row = 0;

        while (!tmp[i].empty()) {
            if (row > model->rowCount() - 1)
                model->insertRow(row);

            QModelIndex index = model->index(row++, i);

            model->setData(index, QString::number(tmp[i].top()));
            model->item(index.row(), index.column())->setEditable(false);
            tmp[i].pop();
        }
    }

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->amountLabel->setText(QString::number(table->get_size()));
    delete[] tmp;
}





void MainWindow::on_findButton_clicked()
{
    if (table->contains(ui->findSpinBox->value()))
        ui->findLabel->setText("true");
    else
        ui->findLabel->setText("false");
}


void MainWindow::on_fillButton_clicked()
{
    int N = ui->fillSpinBox->value();

    table->clear();

    while(table->get_size() != N)
        table->push(rand() % N * 4 - N * 2 +
                    rand() % N - rand() % N / 2);

    print();
}


void MainWindow::on_maxButton_clicked()
{
    if (table->get_size() == 0)
        ui->maxLine->setText("EMPTY");
    else
        ui->maxLine->setText(QString::number(table->get_max()));
}


void MainWindow::on_clearButton_clicked()
{
    table->clear();
    print();
}

