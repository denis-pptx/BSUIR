#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowTitle("Ведомость");



    enrolleeModel = new QStandardItemModel;

    enrolleeMenuAdd = new EnrolleeMenuAdd;
    enrolleeMenuEdit = new EnrolleeMenuEdit;
    // enrolleeMenuView = new EnrolleeMenuView;

    sortMenu = new SortMenu;

    viewWindow = new QTableView;

    ui->aboutEnrolleeLineEdit->setMaxLength(100);
    ui->aboutEnrolleeLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^[^а-яА-ЯёЁ]+$")));


    filename = "D:\\Doc\\Учеба\\ОАиП\\Denis_Konchik_153503\\Qt\\lab3\\build-L3_T1_2-Desktop_Qt_6_2_3_MinGW_64_bit-Debug\\statement.bin";

    if (fileParse()) {
        printEnrollee();
        setSpinboxesRange();
    } else {
        QMessageBox::warning(this, "Error", "Ошибка считывания файла \n" + filename);
        exit(0);
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_deleteEnrolleeButton_clicked()
{
    closeWindows();
    if (!statement.size()) {
        QMessageBox::warning(this, "Warning", "Список пуст");;
        return;
    }

    statement.erase(ui->deleteSpinBox->value() - 1);

    printEnrollee();
    setSpinboxesRange();
    fileRewrite();
}


void MainWindow::on_fromCityPushButton_clicked()
{
    closeWindows();
    if (!statement.size()) {
        QMessageBox::warning(this, "Warning", "Список пуст");;
        return;
    }
    printEnrolleeFromCity(ui->fromCityLineEdit->text());
}


void MainWindow::on_fromScorePushButton_clicked()
{
    closeWindows();
    if (!statement.size()) {
        QMessageBox::warning(this, "Warning", "Список пуст");;
        return;
    }
    printEnrolleeFromScore(ui->fromScoreSpinBox->value());
}


void MainWindow::on_deleteApplicantsButton_clicked()
{
    closeWindows();
    if (!statement.size()) {
        QMessageBox::warning(this, "Warning", "Список пуст");
        return;
    }

    int min = ui->minScoreScoreSpinBox->value();

    stupid_list::list<Enrollee> new_list;

    for (stupid_list::list<Enrollee>::iterator it = statement.begin(); it != -1; ++it)
        if ((*it).getScore() >= min)
            new_list.push_back(
                        Enrollee((*it).getSurname(), (*it).getName(), (*it).getPatronymic(),
                                 (*it).getCity(), (*it).getScore()));

    int deleted = statement.size() - new_list.size();

    statement.clear();
    statement = new_list;

    printEnrollee();
    setSpinboxesRange();
    fileRewrite();

    QMessageBox::information(this, "Info", "Удалено: " + QString::number(deleted));
}

void MainWindow::on_aboutEnrolleePushButton_clicked()
{
    QString surname = ui->aboutEnrolleeLineEdit->text();

    if (!statement.size()) {
        QMessageBox::warning(this, "Warning", "Список пуст");;
        return;
    }

    QString product = ui->aboutEnrolleeLineEdit->text();
    printEnrolleeBySurname(product);

//    closeWindows();
//    if (!statement.size()) {
//        QMessageBox::warning(this, "Warning", "Список пуст");
//        return;
//    }

//    for(stupid_list::list<Enrollee>::iterator it = statement.begin(); it != -1; ++it) {
//        if ((*it).getSurname() == surname) {
//            enrolleeMenuView->activate(it);
//            return;
//        }
//    }
//    QMessageBox::warning(this, "Warning", "Абитуриент не найден");
}







