#include "mainwindow.h"
#include "ui_mainwindow.h"


QString adressToStr(int* ptr) {
    std::stringstream ss;
    ss << ptr;
    QString result = QString::fromStdString(ss.str());
    return result == "0" ? "0x0" : result;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("shared_ptr");
    setFixedSize(size());

    pointers[0] = make_shared(new int(0));
    for (int i = 1; i < 10; i++)
        pointers[i] = pointers[0];

    model = new QStandardItemModel(10, 2, this);
    model->setHeaderData(0, Qt::Horizontal, "Содержит \nуказатель \nm_ptr");
    model->setHeaderData(1, Qt::Horizontal, "Число \nвладельцев \nuse_count");
    ui->tableView->setModel(model);

    for (int i = 0; i < 10; i++)
        isExist[i] = true;

    fill_cells();
}

void MainWindow::fill_cells() {
    // Заполнить ячеек

    // Заполнение столбца адресов содержимого
    for (int row = 0; row < model->rowCount(); row++)
        if (isExist[row])
            model->setData(model->index(row, 0), adressToStr(pointers[row]));

    // Заполнение столбца числа владельцев
    for (int row = 0; row < model->rowCount(); row++)
        if (isExist[row])
            model->setData(model->index(row, 1), *pointers[row].get_count());

    // Запрет изменения ячеек
    for (int row = 0; row < model->rowCount(); row++)
        for (int column = 0; column < model->columnCount(); column++)
              model->item(row, column)->setEditable(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_help_clicked()
{
    // Кнопка "Помощь"

    QDialog* infoWindow = new QDialog(this);
    infoWindow->setWindowTitle("Info");
    infoWindow->setWindowFlags(Qt::Window | Qt::Tool);

    QVBoxLayout* lay = new QVBoxLayout;
    lay->addWidget(new QLabel(
                              "[Присвоить] - присвоить один \n"
                              "указатель другому \n"
                              "[Изменить] - указатель будет \n"
                              "указывать на другую область памяти \n"
                              "[Закрыть] - вызов деструкторов, \n"
                              "как это происходит при \n"
                              "завершения программы."
                              ));


    QPushButton* Ok = new QPushButton("&Ок");
    lay->addWidget(Ok);
    connect(Ok, SIGNAL(clicked()), infoWindow, SLOT(accept()));

    infoWindow->setLayout(lay);
    infoWindow->show();
    infoWindow->activateWindow();
}


void MainWindow::on_pushButton_edit_clicked()
{
    // Кнопка "Присвоить"

    QDialog* Box = new QDialog;
    Box->setWindowTitle("Присвоить");
    Box->setWindowFlags(Qt::Window | Qt::Tool);

    QGridLayout* lay = new QGridLayout;

    lay->addWidget(new QLabel("Номеру: "), 0, 0);
    spb1 = new QSpinBox;
    spb1->setRange(1, model->rowCount());
    spb1->setValue(1);
    lay->addWidget(spb1, 0, 1);

    lay->addWidget(new QLabel("Номер: "), 1, 0);
    spb2 = new QSpinBox;
    spb2->setRange(1, model->rowCount());
    spb2->setValue(1);
    lay->addWidget(spb2, 1, 1);

    QPushButton* Ok = new QPushButton("&Ок");
    QPushButton* Cancel = new QPushButton("&Отмена");
    lay->addWidget(Ok, 2, 0);
    lay->addWidget(Cancel, 2, 1);

    connect(Ok, SIGNAL(clicked()), this, SLOT(appropriation()));
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), Box, SLOT(reject()));

    Box->setLayout(lay);
    Box->show();
    Box->setFixedSize(Box->size());
    Box->activateWindow();
}

void MainWindow::appropriation() {
    // Присваивание

    pointers[spb1->value() - 1] = pointers[spb2->value() - 1];
    fill_cells();
}


void MainWindow::on_pushButton_toElsePtr_clicked()
{
    // Кнопка "Изменить"

    QDialog* Box = new QDialog;
    Box->setWindowTitle("Изменить");
    Box->setWindowFlags(Qt::Window | Qt::Tool);

    QGridLayout* lay = new QGridLayout;

    lay->addWidget(new QLabel("Номер: "), 0, 0);
    spb1 = new QSpinBox;
    spb1->setRange(1, model->rowCount());
    spb1->setValue(1);
    lay->addWidget(spb1, 0, 1);

    QPushButton* Ok = new QPushButton("&Ок");
    QPushButton* Cancel = new QPushButton("&Отмена");
    lay->addWidget(Ok, 1, 0);
    lay->addWidget(Cancel, 1, 1);

    connect(Ok, SIGNAL(clicked()), this, SLOT(toElsePtr()));
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), Box, SLOT(reject()));

    Box->setLayout(lay);
    Box->show();
    Box->setFixedSize(Box->size());
    Box->activateWindow();
}

void MainWindow::toElsePtr() {
    // Изменение указателя на что-то другое

    pointers[spb1->value() - 1] = make_shared(new int(0));
    fill_cells();
}


void MainWindow::on_pushButton_close_clicked()
{

    ui->pushButton_close->blockSignals(true);
    ui->pushButton_edit->blockSignals(true);
    ui->pushButton_toElsePtr->blockSignals(true);
    ui->resetButton->blockSignals(true);
    ui->swapButton->blockSignals(true);

    for (int i = 0; i < 10; i++) {
        QTimer::singleShot(i * 300, this, [=](){

            pointers[i].~shared_ptr();

            isExist[i] = false;
            model->setData(model->index(i, 0), "");
            model->setData(model->index(i, 1), "");
            fill_cells();
        });
    }



    //QTimer::singleShot(5000, this, SLOT(poka()));
    //QTimer::singleShot(5000, this, SLOT(hide()));
}

void MainWindow::poka() {
    int n = 0;
    for (int i = 0; i < 10; i++)
        if (isExist[i])
            n++;
    QMessageBox::warning(this, "Warning","Пока, я вызвал (" + QString::number(n) + " шт) \nоставшиеся деструкторы");

}

void MainWindow::on_resetButton_clicked()
{
    // Кнопка "Сбросить"

    QDialog* Box = new QDialog;
    Box->setWindowTitle("Сбросить");
    Box->setWindowFlags(Qt::Window | Qt::Tool);

    QGridLayout* lay = new QGridLayout;

    lay->addWidget(new QLabel("Номер: "), 0, 0);
    spb1 = new QSpinBox;
    spb1->setRange(1, model->rowCount());
    spb1->setValue(1);
    lay->addWidget(spb1, 0, 1);

    QPushButton* Ok = new QPushButton("&Ок");
    QPushButton* Cancel = new QPushButton("&Отмена");
    lay->addWidget(Ok, 1, 0);
    lay->addWidget(Cancel, 1, 1);

    connect(Ok, SIGNAL(clicked()), this, SLOT(reset()));
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), Box, SLOT(reject()));

    Box->setLayout(lay);
    Box->show();
    Box->setFixedSize(Box->size());
    Box->activateWindow();
}

void MainWindow::reset() {
    // Сброс указателя
    pointers[spb1->value() - 1].reset();
    fill_cells();
}


void MainWindow::on_swapButton_clicked()
{
    // Кнопка "Swap"

    QDialog* Box = new QDialog;
    Box->setWindowTitle("Swap");
    Box->setWindowFlags(Qt::Window | Qt::Tool);

    QGridLayout* lay = new QGridLayout;

    lay->addWidget(new QLabel("Номер: "), 0, 0);
    spb1 = new QSpinBox;
    spb1->setRange(1, model->rowCount());
    spb1->setValue(1);
    lay->addWidget(spb1, 0, 1);

    lay->addWidget(new QLabel("С номером: "), 1, 0);
    spb2 = new QSpinBox;
    spb2->setRange(1, model->rowCount());
    spb2->setValue(1);
    lay->addWidget(spb2, 1, 1);

    QPushButton* Ok = new QPushButton("&Ок");
    QPushButton* Cancel = new QPushButton("&Отмена");
    lay->addWidget(Ok, 2, 0);
    lay->addWidget(Cancel, 2, 1);

    connect(Ok, SIGNAL(clicked()), this, SLOT(swap()));
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), Box, SLOT(reject()));

    Box->setLayout(lay);
    Box->show();
    Box->setFixedSize(Box->size());
    Box->activateWindow();
}

void MainWindow::swap() {
    // Обмен
    pointers[spb1->value() - 1].swap(pointers[spb2->value() - 1]);
    fill_cells();
}

