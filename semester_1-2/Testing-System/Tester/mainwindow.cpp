#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , test(nullptr)
    , passingWindow(nullptr)
    , testOpened(false)
{
    ui->setupUi(this);

    setWindowTitle("Tester");
    resize(240, 120);

    ui->startTestButton->setEnabled(false);
    ui->name_lineEdit->setEnabled(false);
    ui->surname_lineEdit->setEnabled(false);
    ui->time_lineEdit->setEnabled(false);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openTestButton_clicked()
{
    QString fileUrl = QFileDialog::getOpenFileName(0, tr("Open test"), "", tr("*.tst"));

    if (fileUrl == "")
        return;

    testOpened = true;

    ui->name_lineEdit->setEnabled(true);
    ui->surname_lineEdit->setEnabled(true);
    ui->time_lineEdit->setEnabled(true);

    on_name_lineEdit_textEdited("");
    on_surname_lineEdit_textEdited("");

    delete test;
    test = new Test(fileUrl);
    test->open();

    if(test->getPassingTime().first)
        ui->time_lineEdit->setText(QString::number(test->getPassingTime().second) + " мин");
    else
        ui->time_lineEdit->setText("∞");
}


void MainWindow::on_startTestButton_clicked()
{
    passingWindow = new PassingTestWindow(
                 test, QPair<QString,QString>(ui->surname_lineEdit->text(), ui->name_lineEdit->text()));

    connect(passingWindow, &PassingTestWindow::goToMainWindow, this, &MainWindow::show);

    testOpened = false;
    ui->startTestButton->setEnabled(false);

    close();
    passingWindow->show();
}

void MainWindow::on_name_lineEdit_textEdited(const QString &)
{
    if (!testOpened)
        return;

    if (ui->name_lineEdit->text() == "")
        ui->startTestButton->setEnabled(false);
    else if (ui->name_lineEdit->text() != "" &&
             ui->surname_lineEdit->text() != "")
        ui->startTestButton->setEnabled(true);
}


void MainWindow::on_surname_lineEdit_textEdited(const QString&)
{
    if (!testOpened)
        return;

    if (ui->surname_lineEdit->text() == "")
        ui->startTestButton->setEnabled(false);
    else if (ui->surname_lineEdit->text() != "" &&
             ui->name_lineEdit->text() != "")
        ui->startTestButton->setEnabled(true);
}

