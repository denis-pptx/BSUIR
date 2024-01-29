#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("bitset");
    print();
}


MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::boolToStr(bool b) {
    return b ? "true" : "false";
}

void MainWindow::print() {
    ui->lineBinView->setText(set.to_string());
    ui->lineDecView->setText(QString::number(set.to_ulong()));
}

void MainWindow::on_equalButton_clicked()
{
    set[ui->bitNumberEdit->value()] = ui->bitEdit->value();
    print();
}


void MainWindow::on_allButton_clicked()
{
    ui->allView->setText(boolToStr(set.all()));
}


void MainWindow::on_anyButton_clicked()
{
    ui->anyView->setText(boolToStr(set.any()));
}


void MainWindow::on_countButton_clicked()
{
    ui->countView->setText(QString::number(set.count()));
}


void MainWindow::on_flipButton_clicked()
{
    if (ui->flipCheckBox->isChecked())
        set.flip();
    else
        set.flip(ui->flipEdit->value());

    print();
}


void MainWindow::on_noneButton_clicked()
{
    ui->noneView->setText(boolToStr(set.none()));
}


void MainWindow::on_resetButton_clicked()
{
    if (ui->resetCheckBox->isChecked())
        set.reset();
    else
        set.reset(ui->resetEdit->value());

    print();
}


void MainWindow::on_setButton_clicked()
{
    if (ui->setCheckBox->isChecked())
        set.set();
    else
        set.set(ui->setEdit->value());

    print();
}




void MainWindow::on_testButton_clicked()
{
    ui->testView->setText(boolToStr(set.test(ui->testEdit->value())));
}


void MainWindow::on_sizeButton_clicked()
{
    ui->sizeView->setText(QString::number(set.size()));
}

