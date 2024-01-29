#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("queue");
    setFixedSize(size());
    update();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update() {

    if (!q.size()) {
        QString empty = "NONE";
        ui->frontLine->setText(empty);
        ui->backLine->setText(empty);
    } else {
        ui->frontLine->setText(q.front());
        ui->backLine->setText(q.back());
    }

    ui->sizeLine->setText(QString::number(q.size()));
}
void MainWindow::on_pushButton_clicked()
{
    q.push(ui->lineEdit->text());
    update();

}


void MainWindow::on_popButton_clicked()
{
    if (q.size()) {
        q.pop();
        update();
    }
}


void MainWindow::on_clearButton_clicked()
{
    if (q.size()) {
        q.clear();
        update();
    }
}

