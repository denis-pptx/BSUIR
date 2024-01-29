#include "mainwindow.h"
#include "ui_mainwindow.h"

// Считывание файла
void MainWindow::FileRead() {

    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly)) {

        code.clear();
        QTextStream stream(&file);

        string line;
        while(!stream.atEnd()) {
            line = stream.readLine().toStdString().c_str();
            code.push_back(line);
        }

    }
    else
    {
        qDebug() << "BAD OPEN";
    }
    file.close();
}

// Перезапись файла
void MainWindow::FileRewrite() {

    QFile file(fileName);

    if (file.open(QIODevice::Truncate | QIODevice::WriteOnly)) {

        QTextStream stream(&file);
        for (string str : code)
            stream << str.c_str() << "\n";
    }
    else
    {
        qDebug() << "BAD OPEN";
    }

    file.close();
}

// Выбрать файл
void MainWindow::on_choseFileButton_clicked()
{
    QString newFile = QFileDialog::getOpenFileName(0, "Выберите файл", "", "*.*");
    if (newFile == "")
        return;



    fileName = newFile;


    FileRead();

    PrintText();

    SplitCode();



}

// Сохранить файл
void MainWindow::on_saveTextButton_clicked()
{

    QVector<QString> tmp_code = codeEdit->toPlainText().split('\n').toVector();
    code.clear();

    for (const auto& item : tmp_code)
        code.push_back(item.toStdString().c_str());

    SplitCode();

    FileRewrite();

    setWindowTitle(windowTitle);
}
