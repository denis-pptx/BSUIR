#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <ctime>
#include <QMainWindow>
#include <QString>
#include <QPixmap>
//#include <iostream>
//using std::vector;
#include "../vector/vector.h"
#include "../string/string.h"
//using std::string;
// https://clck.ru/gA3eu

using namespace my_string;
using namespace my_vector;

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
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    string count(int N);

    bool bit(string str, int k);


    string pow(string str, int k);
};
#endif // MAINWINDOW_H
