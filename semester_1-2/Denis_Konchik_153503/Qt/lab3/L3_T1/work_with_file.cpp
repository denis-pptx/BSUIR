#include "mainwindow.h"
#include "ui_mainwindow.h"

bool MainWindow::fileParse() {


    QFile file;
    file.setFileName(filename);

    node_list::list<Product> temp_list;
    Product tmp;

    if (file.open(QIODevice::ReadOnly)) {

        while (file.read((char*)&tmp, sizeof(Product))) {

            if (tmp.isValidParse()) {
                temp_list.push_back(tmp);
            } else {
                file.close();
                return false;
            }

        }

    }
    else
    {
        qDebug() << "BAD OPEN";
    }

    warehouse = temp_list;
    file.close();
    return true;
}

void MainWindow::fileRewrite() {

    QFile file;
    file.setFileName(filename);

    if (file.open(QIODevice::Truncate | QIODevice::WriteOnly))
        for (node_list::list<Product>::iterator it = warehouse.begin(); it != nullptr; ++it)
            file.write((char*)&(*it), sizeof(Product));
    else
        qDebug() << "BAD OPEN";


    file.close();
}

void MainWindow::on_fileButton_clicked()
{
    QString newFile = QFileDialog::getOpenFileName(0, "Выберите файл", "", "*.bin");
    if (newFile == "")
        return;

    QString oldFile = filename;
    filename = newFile;


    if (fileParse()) {
        printProducts();
        setSpinboxesRange();
    } else {
        QMessageBox::warning(this, "Error", "Ошибка считывания файла \n" + filename);
        filename = oldFile;
    }

}
