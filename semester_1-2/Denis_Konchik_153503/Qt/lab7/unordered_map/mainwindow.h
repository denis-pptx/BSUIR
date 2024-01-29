#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QComboBox>

#include "hash.h"
#include "menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class HashFunctor {
public:
    int operator()(const QString& str) {
        int sum = 0;
        for (const auto& i : str)
            sum += i.unicode();
        return sum;
    }
};

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

private:
    void printHashTable();

    Ui::MainWindow *ui;

    QStandardItemModel* model;

    my_hash::unordered_map<QString, QString, HashFunctor>* hash_table;

    Menu* menu;
};
#endif // MAINWINDOW_H
