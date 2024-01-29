#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::printEnrollee()
{
    delete enrolleeModel;

    enrolleeModel = new QStandardItemModel(statement.size(), 5,this);
    QString enrolleeModelColumnName[] = {"Фамилия", "Имя", "Отчество", "Город", "Баллы" };

    for (int column = 0; column < 5; column++)
        enrolleeModel->setHeaderData(column, Qt::Horizontal, enrolleeModelColumnName[column]);

    connect(ui->enrolleeView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(setSpinBoxNumber(const QModelIndex&)));
    ui->enrolleeView->setModel(enrolleeModel);

    int row = 0;
    for (stupid_list::list<Enrollee>::iterator it = statement.begin(); it != -1; ++it, ++row) {

        for (int column = 0; column < enrolleeModel->columnCount(); column++) {

            QModelIndex index = enrolleeModel->index(row, column);
            enrolleeModel->setData(index, (*it).getColumnByIndex(column));
            enrolleeModel->item(row, column)->setEditable(false);
        }
    }

}


void MainWindow::printEnrolleeFromCity(QString city)
{
    QStandardItemModel* modelWindow = new QStandardItemModel(0, 5,this);
    QString enrolleeModelColumnName[] = {"Фамилия", "Имя", "Отчество", "Город", "Баллы" };

    for (int column = 0; column < 5; column++)
        modelWindow->setHeaderData(column, Qt::Horizontal, enrolleeModelColumnName[column]);

    viewWindow = new QTableView;
    viewWindow->setModel(modelWindow);

    int row = 0;
    for (stupid_list::list<Enrollee>::iterator it = statement.begin(); it != -1; ++it) {

        if ((*it).getCity() == city) {

            modelWindow->insertRow(row);

            for (int column = 0; column < modelWindow->columnCount(); column++) {

                QModelIndex index = modelWindow->index(row, column);
                modelWindow->setData(index, (*it).getColumnByIndex(column));
                modelWindow->item(row, column)->setEditable(false);
            }

            row++;
        }
    }

    if (modelWindow->rowCount() == 0) {
        QMessageBox::warning(this, "Warning", "Абитуриенты не найдены");;
    } else {
        viewWindow->setWindowTitle("Абитуриенты по городу");
        viewWindow->setFixedSize(ui->enrolleeView->size());
        viewWindow->show();
    }


}


void MainWindow::printEnrolleeFromScore(int score)
{
    QStandardItemModel* modelWindow = new QStandardItemModel(0, 5,this);
    QString enrolleeModelColumnName[] = {"Фамилия", "Имя", "Отчество", "Город", "Баллы" };

    for (int column = 0; column < 5; column++)
        modelWindow->setHeaderData(column, Qt::Horizontal, enrolleeModelColumnName[column]);

    viewWindow = new QTableView;
    viewWindow->setModel(modelWindow);

    int row = 0;
    for (stupid_list::list<Enrollee>::iterator it = statement.begin(); it != -1; ++it) {

        if ((*it).getScore() >= score) {

            modelWindow->insertRow(row);

            for (int column = 0; column < modelWindow->columnCount(); column++) {

                QModelIndex index = modelWindow->index(row, column);
                modelWindow->setData(index, (*it).getColumnByIndex(column));
                modelWindow->item(row, column)->setEditable(false);
            }

            row++;
        }
    }

    if (modelWindow->rowCount() == 0) {
        QMessageBox::warning(this, "Warning", "Абитуриенты не найдены");;
    } else {
        viewWindow->setWindowTitle("Абитуриенты по баллу");
        viewWindow->setFixedSize(ui->enrolleeView->size());
        viewWindow->show();
    }

}

void MainWindow::printEnrolleeBySurname(QString product) {

    QStandardItemModel* modelWindow = new QStandardItemModel(0, 5,this);
    QString enrolleeModelColumnName[] = {"Фамилия", "Имя", "Отчество", "Город", "Баллы" };

    for (int column = 0; column < 5; column++)
        modelWindow->setHeaderData(column, Qt::Horizontal, enrolleeModelColumnName[column]);

    viewWindow = new QTableView;
    viewWindow->setModel(modelWindow);

    int row = 0;
    for (stupid_list::list<Enrollee>::iterator it = statement.begin(); it != -1; ++it) {

        if ((*it).getSurname() == product) {

            modelWindow->insertRow(row);

            for (int column = 0; column < modelWindow->columnCount(); column++) {

                QModelIndex index = modelWindow->index(row, column);
                modelWindow->setData(index, (*it).getColumnByIndex(column));
                modelWindow->item(row, column)->setEditable(false);
            }

            row++;
        }
    }

    if (modelWindow->rowCount() == 0) {
        QMessageBox::warning(this, "Warning", "Абитуриенты не найдены");;
    } else {
        viewWindow->setWindowTitle("Абитуриенты по фамилии");
        viewWindow->setFixedSize(ui->enrolleeView->size());
        viewWindow->show();
    }

}


