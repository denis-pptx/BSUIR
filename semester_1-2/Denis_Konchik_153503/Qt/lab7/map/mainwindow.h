#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "map.h"
#include "menu.h"
#include <iostream>

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
    void on_insertButton_clicked();

    void on_eraseButton_clicked();

    void on_clearButton_clicked();

    void on_searchButton_clicked();


    void on_equalButton_clicked();

    void on_returnButton_clicked();

    void on_printButton_clicked();

    void on_pushButton_clicked();

    void on_plus_equal_Button_clicked();

    void on_minus_equal_Button_clicked();

    void on_iteratorEdit_Button_clicked();

    void on_updateButton_clicked();

private:
    void printBts();

    void print_iterator();

    Ui::MainWindow *ui;

    QStandardItemModel* model;

    my_map::map<QString, QString> bts;
    my_map::map<QString, QString>::iterator it;

    Menu* menu;
};
#endif // MAINWINDOW_H
