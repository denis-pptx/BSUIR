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
    setWindowTitle("weak_ptr");
    setFixedSize(size());


    pointersShared[0] = make_shared(new int(0));
    for (int i = 1; i < 10; i++)
        pointersShared[i] = pointersShared[0];

    modelShared = new QStandardItemModel(10, 2, this);
    modelShared->setHeaderData(0, Qt::Horizontal, "Содержит \nуказатель \nm_ptr");
    modelShared->setHeaderData(1, Qt::Horizontal, "Число \nвладельцев \nshared_count");
    ui->tableViewShared->setModel(modelShared);

    for (int i = 0; i < 10; i++)
        isExistShared[i] = true;

    fill_cells_shared();

    pointersWeak[0] = pointersShared[0];
    for (int i = 1; i < 10; i++)
        pointersWeak[i] = pointersWeak[0];

    modelWeak = new QStandardItemModel(10, 3, this);
    modelWeak->setHeaderData(0, Qt::Horizontal, "Содержит \nуказатель \nm_ptr");
    modelWeak->setHeaderData(1, Qt::Horizontal, "Число \nвладельцев \nshared_count");
    modelWeak->setHeaderData(2, Qt::Horizontal, "Число \nнаблюдателей \nweak_count");
    ui->tableViewWeak->setModel(modelWeak);

    for (int i = 0; i < 10; i++)
        isExistWeak[i] = true;

    fill_cells_weak();
}

void MainWindow::fill_cells_shared() {
    // Заполнение ячеек SHARED

    // Заполнение столбца адресов содержимого
    for (int row = 0; row < modelShared->rowCount(); row++)
        if (isExistShared[row])
            modelShared->setData(modelShared->index(row, 0), adressToStr(pointersShared[row]));

    // Заполнение столбца числа владельцев
    for (int row = 0; row < modelShared->rowCount(); row++)
        if (isExistShared[row])
            modelShared->setData(modelShared->index(row, 1), *pointersShared[row].get_count());

    // Запрет изменения ячеек
    for (int row = 0; row < modelShared->rowCount(); row++)
        for (int column = 0; column < modelShared->columnCount(); column++)
              modelShared->item(row, column)->setEditable(false);
}

void MainWindow::fill_cells_weak() {
    // Заполнение ячеек WEAK

    // Заполнение столбца адресов содержимого
    for (int row = 0; row < modelWeak->rowCount(); row++)
        if (isExistWeak[row])
            modelWeak->setData(modelWeak->index(row, 0), adressToStr((int*)pointersWeak[row]));

    // Заполнение столбца числа владельцев
    for (int row = 0; row < modelWeak->rowCount(); row++)
        if (isExistWeak[row]) {
            if (*pointersWeak[row].get_use_count() < 0 ||
                    *pointersWeak[row].get_use_count() > 10)
                modelWeak->setData(modelWeak->index(row, 1), "0");
            else
                modelWeak->setData(modelWeak->index(row, 1), *pointersWeak[row].get_use_count());
        }

    // Заполнение столбца числа наблюдателей
    for (int row = 0; row < modelWeak->rowCount(); row++)
        if (isExistWeak[row])
            modelWeak->setData(modelWeak->index(row, 2), *pointersWeak[row].get_weak_count());

    // Запрет изменения ячеек
    for (int row = 0; row < modelWeak->rowCount(); row++)
        for (int column = 0; column < modelWeak->columnCount(); column++)
              modelWeak->item(row, column)->setEditable(false);
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
                              "[Присвоить weak] - присвоить weak'у weak \n"
                              "[weak->shared] - сделать из weak'a shared \n"
                              "и присвоить это shared'у \n"
                              "[Присвоить shared] - присвоить weak'у shared \n\n"
                              "[Изменить] - указатель shared будет \n"
                              "указывать на другую область памяти \n"
                              "[Присвоить] - присвоить один \n"
                              "указатель shared другому \n\n"
                              "[Закрыть] - вызов деструкторов, как это\n"
                              "происходит при завершения программы"
                              ));


    QPushButton* Ok = new QPushButton("&Ок");
    lay->addWidget(Ok);
    connect(Ok, SIGNAL(clicked()), infoWindow, SLOT(accept()));

    infoWindow->setLayout(lay);
    infoWindow->show();
    infoWindow->activateWindow();
}


void MainWindow::on_pushButton_edit_shared_clicked()
{
    // Кнопка "Присвоить"

    QDialog* Box = new QDialog;
    Box->setWindowTitle("Присвоить");
    Box->setWindowFlags(Qt::Window | Qt::Tool);

    QGridLayout* lay = new QGridLayout;

    lay->addWidget(new QLabel("Номеру: "), 0, 0);
    spb1 = new QSpinBox;
    spb1->setRange(1, modelShared->rowCount());
    spb1->setValue(1);
    lay->addWidget(spb1, 0, 1);

    lay->addWidget(new QLabel("Номер: "), 1, 0);
    spb2 = new QSpinBox;
    spb2->setRange(1, modelShared->rowCount());
    spb2->setValue(1);
    lay->addWidget(spb2, 1, 1);

    QPushButton* Ok = new QPushButton("&Ок");
    QPushButton* Cancel = new QPushButton("&Отмена");
    lay->addWidget(Ok, 2, 0);
    lay->addWidget(Cancel, 2, 1);

    connect(Ok, SIGNAL(clicked()), this, SLOT(appropriation_shared()));
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), Box, SLOT(reject()));

    Box->setLayout(lay);
    Box->show();
    Box->setFixedSize(Box->size());
    Box->activateWindow();
}

void MainWindow::appropriation_shared() {
    // Присваивание

    pointersShared[spb1->value() - 1] = pointersShared[spb2->value() - 1];
    fill_cells_weak();
    fill_cells_shared();
}


void MainWindow::on_pushButton_toElsePtr_shared_clicked()
{
    // Кнопка "Изменить"

    QDialog* Box = new QDialog;
    Box->setWindowTitle("Изменить");
    Box->setWindowFlags(Qt::Window | Qt::Tool);

    QGridLayout* lay = new QGridLayout;

    lay->addWidget(new QLabel("Номер: "), 0, 0);
    spb1 = new QSpinBox;
    spb1->setRange(1, modelShared->rowCount());
    spb1->setValue(1);
    lay->addWidget(spb1, 0, 1);

    QPushButton* Ok = new QPushButton("&Ок");
    QPushButton* Cancel = new QPushButton("&Отмена");
    lay->addWidget(Ok, 1, 0);
    lay->addWidget(Cancel, 1, 1);

    connect(Ok, SIGNAL(clicked()), this, SLOT(toElsePtr_shared()));
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), Box, SLOT(reject()));

    Box->setLayout(lay);
    Box->show();
    Box->setFixedSize(Box->size());
    Box->activateWindow();
}

void MainWindow::toElsePtr_shared() {
    // Изменение указателя на что-то другое

    pointersShared[spb1->value() - 1] = make_shared(new int(0));
    fill_cells_weak();
    fill_cells_shared();
}


void MainWindow::on_pushButton_close_clicked()
{
    ui->pushButton_assign_shared->blockSignals(true);
    ui->pushButton_assign_weak->blockSignals(true);
    ui->pushButton_close->blockSignals(true);
    ui->pushButton_edit_shared->blockSignals(true);
    ui->pushButton_toElsePtr_shared->blockSignals(true);
    ui->pushButton_weakToShared->blockSignals(true);

    for (int i = 0; i < 10; i++) {
        QTimer::singleShot(i * 300, this, [=](){

            pointersShared[i].~shared_ptr();

            isExistShared[i] = false;
            modelShared->setData(modelShared->index(i, 0), "");
            modelShared->setData(modelShared->index(i, 1), "");
            fill_cells_shared();
            fill_cells_weak();
        });
    }

    for (int i = 0; i < 10; i++) {
        QTimer::singleShot((i+ 10) * 300, this, [=](){

            pointersWeak[i].~weak_ptr();


            isExistWeak[i] = false;
            fill_cells_weak();

            modelWeak->setData(modelWeak->index(i, 0), "");
            modelWeak->setData(modelWeak->index(i, 1), "");
            modelWeak->setData(modelWeak->index(i, 2), "");

        });
    }


    //QTimer::singleShot(5000, this, SLOT(poka()));
    //QTimer::singleShot(5000, this, SLOT(hide()));
}

void MainWindow::poka() {
    QMessageBox::warning(this, "Warning","Пока, я вызвал \nоставшиеся деструкторы");
}

void MainWindow::on_pushButton_assign_weak_clicked()
{
    // Кнопка "Присвоить weak_ptr"

    QDialog* Box = new QDialog;
    Box->setWindowTitle("Присвоить weak");
    Box->setWindowFlags(Qt::Window | Qt::Tool);

    QGridLayout* lay = new QGridLayout;

    lay->addWidget(new QLabel("Указателю weak: "), 0, 0);
    spb1 = new QSpinBox;
    spb1->setRange(1, modelShared->rowCount());
    spb1->setValue(1);
    lay->addWidget(spb1, 0, 1);

    lay->addWidget(new QLabel("Указатель weak: "), 1, 0);
    spb2 = new QSpinBox;
    spb2->setRange(1, modelShared->rowCount());
    spb2->setValue(1);
    lay->addWidget(spb2, 1, 1);

    QPushButton* Ok = new QPushButton("&Ок");
    QPushButton* Cancel = new QPushButton("&Отмена");
    lay->addWidget(Ok, 2, 0);
    lay->addWidget(Cancel, 2, 1);

    connect(Ok, SIGNAL(clicked()), this, SLOT(assign_weak()));
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), Box, SLOT(reject()));

    Box->setLayout(lay);
    Box->show();
    Box->setFixedSize(Box->size());
    Box->activateWindow();
}

void MainWindow::assign_weak() {
    // Присвоение weak'у weak

    pointersWeak[spb1->value() - 1] = pointersWeak[spb2->value() - 1];
    fill_cells_weak();
    fill_cells_shared();
}


void MainWindow::on_pushButton_assign_shared_clicked()
{
    // Кнопка "Присвоить shared_ptr"

    QDialog* Box = new QDialog;
    Box->setWindowTitle("Присвоить shared");
    Box->setWindowFlags(Qt::Window | Qt::Tool);

    QGridLayout* lay = new QGridLayout;

    lay->addWidget(new QLabel("Указателю weak: "), 0, 0);
    spb1 = new QSpinBox;
    spb1->setRange(1, modelShared->rowCount());
    spb1->setValue(1);
    lay->addWidget(spb1, 0, 1);

    lay->addWidget(new QLabel("Указатель shared: "), 1, 0);
    spb2 = new QSpinBox;
    spb2->setRange(1, modelShared->rowCount());
    spb2->setValue(1);
    lay->addWidget(spb2, 1, 1);

    QPushButton* Ok = new QPushButton("&Ок");
    QPushButton* Cancel = new QPushButton("&Отмена");
    lay->addWidget(Ok, 2, 0);
    lay->addWidget(Cancel, 2, 1);

    connect(Ok, SIGNAL(clicked()), this, SLOT(assign_shared()));
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), Box, SLOT(reject()));

    Box->setLayout(lay);
    Box->show();
    Box->setFixedSize(Box->size());
    Box->activateWindow();
}

void MainWindow::assign_shared() {
    // Присвоение weak'у shared

    pointersWeak[spb1->value() - 1] = pointersShared[spb2->value() - 1];
    fill_cells_weak();
    fill_cells_shared();
}


void MainWindow::on_pushButton_weakToShared_clicked()
{
    // Кнопка "weak->shared"

    QDialog* Box = new QDialog;
    Box->setWindowTitle("weak->shared");
    Box->setWindowFlags(Qt::Window | Qt::Tool);

    QGridLayout* lay = new QGridLayout;

    lay->addWidget(new QLabel("Из указателя weak: "), 0, 0);
    spb1 = new QSpinBox;
    spb1->setRange(1, modelShared->rowCount());
    spb1->setValue(1);
    lay->addWidget(spb1, 0, 1);

    lay->addWidget(new QLabel("Сделать shared и присвоить"), 1, 0);

    lay->addWidget(new QLabel("Указателю shared: "), 2, 0);
    spb2 = new QSpinBox;
    spb2->setRange(1, modelShared->rowCount());
    spb2->setValue(1);
    lay->addWidget(spb2, 2, 1);

    QPushButton* Ok = new QPushButton("&Ок");
    QPushButton* Cancel = new QPushButton("&Отмена");
    lay->addWidget(Ok, 3, 0);
    lay->addWidget(Cancel, 3, 1);

    connect(Ok, SIGNAL(clicked()), this, SLOT(weak_to_shared()));
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), Box, SLOT(reject()));

    Box->setLayout(lay);
    Box->show();
    Box->setFixedSize(Box->size());
    Box->activateWindow();
}

void MainWindow::weak_to_shared() {
    pointersShared[spb2->value() - 1] = pointersWeak[spb1->value() - 1].lock();
    fill_cells_weak();
    fill_cells_shared();
}

