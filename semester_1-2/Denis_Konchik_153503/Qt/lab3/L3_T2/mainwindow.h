#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include "stack.h"
using namespace my_stack;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_choseFileButton_clicked();


    void on_saveTextButton_clicked();

    void on_checkButton_clicked();

private:
    Ui::MainWindow *ui;
    QString fileName;

    void fileRead();
    void fileRewrite();

    QStringList textList;
    void printTextEdit();

    bool isStrCorrect(QString& str, int& row);
    bool isListCorrect();



    struct bracket {
        char c;
        int row;
        int column;
    };

    stack<bracket> a;


};
#endif // MAINWINDOW_H
