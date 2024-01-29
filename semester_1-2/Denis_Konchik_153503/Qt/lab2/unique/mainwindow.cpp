#include "mainwindow.h"
#include "ui_mainwindow.h"

template<class T>
QString adressToStr(unique_ptr<T>& ptr) {
    std::stringstream ss;
    ss << &ptr;
    return QString::fromStdString(ss.str());
}

template<class T>
QString adressToStr(T* ptr) {
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
    setWindowTitle("unique_ptr");
    setFixedSize(size());

    model = new QStandardItemModel(10, 2, this);
    model->setHeaderData(0, Qt::Horizontal, "Адрес умного \nуказателя");
    model->setHeaderData(1, Qt::Horizontal, "Содержит \nуказатель \nm_ptr");
    ui->tableView->setModel(model);

    pointers[0] = make_unique<int>(new int(0));
    current_owner = 1;

    fill_cells();

    spb1 = new QSpinBox;
    spb2 = new QSpinBox;
}

void MainWindow::fill_cells() {
    // Заполнить ячейки

    // Заполнение столбца адресов указателей
    for (int row = 0; row < model->rowCount(); row++)
        model->setData(model->index(row, 0), adressToStr(pointers[row]));

    // Заполнение столбца содержимого указателей
    for (int row = 0; row < model->rowCount(); row++)
        model->setData(model->index(row, 1), adressToStr(pointers[row].get_ptr()));

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
                              "[Адрес умного указателя] - адрес умного указателя, \n"
                              "который содержит указатель (т.е объекта класса) \n"
                              "[Содержит указатель] - адрес указателя, который\n"
                              "содержится в умном указателе \n\n"
                              "[Присвоить] - присовить один указатель другому \n"
                              "[Изменить] - присвоить данному указателю новый \n"
                              "сырой указатель \n"
                              "[Сбросить] - обнулить указатель (reset) \n"
                              "[Swap] - обменять содержимое указателей \n\n"
                              "Левый столбец - адрес умного указателя \n"
                              "Правый столбец - то, что он содержит"
                              ));


    QPushButton* Ok = new QPushButton("&Ок");
    lay->addWidget(Ok);
    connect(Ok, SIGNAL(clicked()), infoWindow, SLOT(accept()));

    infoWindow->setLayout(lay);
    infoWindow->show();
    infoWindow->activateWindow();
}


void MainWindow::on_assignButton_clicked()
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

    connect(Ok, SIGNAL(clicked()), this, SLOT(assignment()));
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), Box, SLOT(reject()));

    Box->setLayout(lay);
    Box->show();
    Box->setFixedSize(Box->size());
    Box->activateWindow();
}

void MainWindow::assignment() {
    // Присваивание

    pointers[spb1->value() - 1] = pointers[spb2->value() - 1];
    fill_cells();
}

void MainWindow::on_editButton_clicked()
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

    connect(Ok, SIGNAL(clicked()), this, SLOT(edit()));
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), Box, SLOT(reject()));

    Box->setLayout(lay);
    Box->show();
    Box->setFixedSize(Box->size());
    Box->activateWindow();
}

void MainWindow::edit() {
    // Изменение указателя на что-то другое

    pointers[spb1->value() - 1] = make_unique(new int(0));
    fill_cells();
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

