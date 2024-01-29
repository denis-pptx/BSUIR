#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileName = "text.txt";
    setFixedSize(size());
    setWindowTitle("Скобки");

    fileRead();
    printTextEdit();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_choseFileButton_clicked()
{
    QString newFile = QFileDialog::getOpenFileName(0, "Выберите файл", "", "*.*");
    if (newFile == "")
        return;

    fileName = newFile;

    fileRead();
    printTextEdit();
}

void MainWindow::on_saveTextButton_clicked()
{
    textList = ui->textEdit->toPlainText().split('\n');
    fileRewrite();
}


void MainWindow::fileRead() {

    QFile file;
    file.setFileName(fileName);

    if (file.open(QIODevice::ReadOnly)) {
        textList.clear();
        QTextStream stream(&file);

        QString line;
        while(!stream.atEnd()) {
            line = stream.readLine();
            textList.push_back(line);
        }
    }
    else
    {
        qDebug() << "BAD OPEN";
    }
    file.close();
}

void MainWindow::fileRewrite() {
    QFile file;
    file.setFileName(fileName);

    if (file.open(QIODevice::Truncate | QIODevice::WriteOnly)) {

        QTextStream stream(&file);
        for (QString str : textList)
            stream << str << "\n";
    }
    else
    {
        qDebug() << "BAD OPEN";
    }

    file.close();
}

void MainWindow::printTextEdit() {
    QString text = "";
    for (QString str : textList)
        text += str + "\n";

    ui->textEdit->setText(text);

}


bool MainWindow::isStrCorrect(QString &str, int& row) {


    for (int column = 0; column < str.size(); column++) {
        if (str[column] == '[') { a.push(bracket{'[', row, column}); }
        if (str[column] == '{') { a.push(bracket{'{', row, column}); }
        if (str[column] == '(') { a.push(bracket{'(', row, column}); }

        if (str[column] == ']') {
            if (a.empty() || a.top().c != '[') {
                a.push(bracket{']', row, column});
                return false;
            }
            else
                a.pop();
        }

        if (str[column] == '}') {
            if (a.empty() || a.top().c != '{'){
                a.push(bracket{'}', row, column});
                return false;
            }
            else
                a.pop();
        }

        if (str[column] == ')') {
            if (a.empty() || a.top().c != '(') {
                a.push(bracket{')', row, column});
                return false;
            }
            else
                a.pop();
        }
    }

    return true;
}

bool MainWindow::isListCorrect() {

    a.clear();
    textList = ui->textEdit->toPlainText().split('\n');

    for (int row = 0; row < textList.size(); row++)
        if (!isStrCorrect(textList[row], row))
            return false;

    return a.empty();
}

void MainWindow::on_checkButton_clicked()
{
    qDebug() << isListCorrect();

    if (!isListCorrect())
        QMessageBox::critical(this, " ",
                             "Скобка: " + QString(a.top().c) +
                             "\nСтрока: " + QString::number(a.top().row + 1) +
                             "\nСтолбец: " + QString::number(a.top().column + 1));
    else
        QMessageBox::information(this, " ", "Success");


}



//QString msg;
//if (a.top().c == '(' || a.top().c == '{' || a.top().c == '[')
//    msg = "Не найдена соответствующая \nзакрывающая скобка";
//else
//    msg = "Не найдена соответствующая \nоткрывающая скобка";



