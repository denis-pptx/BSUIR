#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowTitle("Склад");



    productModel = new QStandardItemModel;
    productMenuAdd = new ProductMenuAdd;
    productMenuEdit = new ProductMenuEdit;
    // productMenuView = new ProductMenuView;
    sortMenu = new SortMenu;
    viewWindow = new QTableView;

    ui->aboutProductLineEdit->setMaxLength(100);
    ui->aboutProductLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^[^а-яА-ЯёЁ]+$")));


    filename = "D:\\Doc\\Учеба\\ОАиП\\Denis_Konchik_153503\\Qt\\lab3\\build-L3_T1-Desktop_Qt_6_2_3_MinGW_64_bit-Debug\\warehouse.bin";

    if (fileParse()) {
        printProducts();
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

void MainWindow::on_deleteProductButton_clicked()
{
    closeWindows();
    if (!warehouse.size()) {
        QMessageBox::warning(this, "Warning", "Список пуст");;
        return;
    }

    warehouse.erase(ui->deleteSpinBox->value() - 1);

    printProducts();
    setSpinboxesRange();
    fileRewrite();
}



void MainWindow::on_settingsProductButton_clicked()
{
    closeWindows();
    if (!warehouse.size()) {
        QMessageBox::warning(this, "Warning", "Список пуст");;
        return;
    }

    printProductWithSettings();
}


void MainWindow::on_expectedProductButton_clicked()
{
    closeWindows();
    if (!warehouse.size()) {
        QMessageBox::warning(this, "Warning", "Список пуст");;
        return;
    }

    printExpectedProduct();
}

void MainWindow::on_aboutProductButton_clicked()
{
    closeWindows();
    if (!warehouse.size()) {
        QMessageBox::warning(this, "Warning", "Список пуст");;
        return;
    }

    QString product = ui->aboutProductLineEdit->text();
    printProductByName(product);

//    closeWindows();
//    if (!warehouse.size()) {
//        QMessageBox::warning(this, "Warning", "Список пуст");;
//        return;
//    }

//    for(node_list::list<Product>::iterator it = warehouse.begin(); it != nullptr; ++it) {
//        if ((*it).getName() == product) {
//            productMenuView->activate(it);
//            return;
//        }
//    }
//    QMessageBox::warning(this, "Warning", "Товар не найден");;
}


















