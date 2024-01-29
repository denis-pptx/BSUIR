#include "mainwindow.h"
#include "ui_mainwindow.h"

bool MainWindow::fileParse() {


    QFile file;
    file.setFileName(filename);

    stupid_list::list<Enrollee> temp_list;
    Enrollee tmp;

    if (file.open(QIODevice::ReadOnly)) {

        while (file.read((char*)&tmp, sizeof(Enrollee))) {

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

    statement = temp_list;
    file.close();
    return true;
}

void MainWindow::fileRewrite() {

    QFile file;
    file.setFileName(filename);

    if (file.open(QIODevice::Truncate | QIODevice::WriteOnly))
        for (stupid_list::list<Enrollee>::iterator it = statement.begin(); it != -1; ++it)
            file.write((char*)&(*it), sizeof(Enrollee));
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
        printEnrollee();
        setSpinboxesRange();
    } else {
        QMessageBox::warning(this, "Error", "Ошибка считывания файла \n" + filename);
        filename = oldFile;
    }
}
