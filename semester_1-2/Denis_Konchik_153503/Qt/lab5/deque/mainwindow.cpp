#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "deque.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    print_deque();

    setWindowTitle("deque");
    setFixedSize(size());

    ui->plus_equal_Button->setEnabled(false);
    ui->minus_equal_Button->setEnabled(false);
    ui->iteratorEdit_Button->setEnabled(false);
    ui->iteratorEdit->setEnabled(false);
    ui->it_minus_equal->setEnabled(false);
    ui->it_plus_equal->setEnabled(false);

    ui->equalButton->setEnabled(false);
    ui->randomLine->setEnabled(false);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::print_deque() {
    ui->listWidget->clear();

    for (int i = 0; i < d.size(); i++)
        ui->listWidget->addItem("[" + QString::number(i) + "]: " + d[i]);

    ui->label_size->setText(QString::number(d.size()));
    ui->label_empty->setText(d.empty() ? "true" : "false");
    ui->spinBox->setRange(0, d.size() - 1);

    if (d.empty()) {
        ui->random_Button->setEnabled(false);
        ui->spinBox->setEnabled(false);
        ui->frontButton->setEnabled(false);
        ui->backButton->setEnabled(false);
        ui->equalButton->setEnabled(false);
        ui->randomLine->setEnabled(false);
        ui->updateButton->setEnabled(false);
        ui->randomLine->setText("");
    } else {
        ui->random_Button->setEnabled(true);
        ui->spinBox->setEnabled(true);
        ui->frontButton->setEnabled(true);
        ui->backButton->setEnabled(true);
        ui->equalButton->setEnabled(true);
        ui->randomLine->setEnabled(true);

    }



  //  ui->randomLine->setText("");
}


void MainWindow::on_push_back_Button_clicked()
{
    d.push_back(ui->lineEdit->text());

    print_deque();

}


void MainWindow::on_push_front_Button_clicked()
{
    d.push_front(ui->lineEdit->text());

    print_deque();

}


void MainWindow::on_pop_back_Button_clicked()
{
    d.pop_back();

    print_deque();
}


void MainWindow::on_pop_front_Button_clicked()
{
    d.pop_front();

    print_deque();
}


void MainWindow::on_clear_Button_clicked()
{
    d.clear();

    print_deque();
}


void MainWindow::on_random_Button_clicked()
{
    ui->randomLine->setText(d[ui->spinBox->value()]);
}


void MainWindow::on_frontButton_clicked()
{
    ui->randomLine->setText(d.front());
}


void MainWindow::on_backButton_clicked()
{
    ui->randomLine->setText(d.back());
}

void MainWindow::print_iterator() {

    ui->plus_equal_Button->setEnabled(true);
    ui->minus_equal_Button->setEnabled(true);
    ui->iteratorEdit_Button->setEnabled(true);
    ui->iteratorEdit->setEnabled(true);
    ui->it_minus_equal->setEnabled(true);
    ui->it_plus_equal->setEnabled(true);
    ui->updateButton->setEnabled(true);


    ui->iteratorEdit->setText(*it);
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->comboBox->currentText() == "begin")
        it = d.begin();
    else
        it = d.end();

    print_iterator();
}


void MainWindow::on_plus_equal_Button_clicked()
{
    it += ui->it_plus_equal->value();
    print_iterator();
}


void MainWindow::on_minus_equal_Button_clicked()
{
    it -= ui->it_minus_equal->value();
    print_iterator();
}


void MainWindow::on_iteratorEdit_Button_clicked()
{
    *it = ui->iteratorEdit->text();

    print_iterator();

    print_deque();
}


void MainWindow::on_equalButton_clicked()
{
    d[ui->spinBox->value()] = ui->randomLine->text();


    print_deque();
}


void MainWindow::on_updateButton_clicked()
{
    print_iterator();
}


void MainWindow::on_pushButton_2_clicked()
{
    for (int i = 0; i < 100; i++)
        on_push_back_Button_clicked();
}

