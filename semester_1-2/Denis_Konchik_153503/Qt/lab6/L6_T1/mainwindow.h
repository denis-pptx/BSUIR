#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QModelIndex>

#include "avl.h"
#include "menu.h"
#include "item.h"

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

    void on_tableToTreeButton_clicked();

    void on_directBypassButton_clicked();

    void on_symmetricalBypassButton_clicked();

    void on_backBypassButton_clicked();

    void on_printTreeButton_clicked();

    void on_addItemButton_clicked();

    void on_deleteItemButton_clicked();



    void on_findItemButton_clicked();

    void on_clearButton_clicked();

    void on_variantButton_clicked();

    void on_widthBypassButton_clicked();

private:
    Ui::MainWindow *ui;

    Menu* menu;

    QStandardItemModel* model;

    QVector<Item> items;

    TreeMod<Item> tree;

    void printItems();



};
#endif // MAINWINDOW_H
