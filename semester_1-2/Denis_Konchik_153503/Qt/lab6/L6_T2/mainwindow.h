#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "hash.h"
#include "stack.h"

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
    void on_addButton_clicked();

    void on_deleteButton_clicked();


    void on_findButton_clicked();

    void on_fillButton_clicked();

    void on_maxButton_clicked();

    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;

    HashTableMod* table;

    QStandardItemModel* model;

    void print();
};
#endif // MAINWINDOW_H
