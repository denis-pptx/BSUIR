#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "unique_ptr.h"
using namespace p;

#include <sstream>
#include <string>

#include <QVBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QDialog>
#include <QSpinBox>
#include <QStandardItemModel>

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


    void on_pushButton_help_clicked();

    void on_assignButton_clicked();
    void assignment();

    void on_editButton_clicked();
    void edit();

    void on_resetButton_clicked();
    void reset();

    void on_swapButton_clicked();
    void swap();
private:
    Ui::MainWindow *ui;
    QStandardItemModel* model;
    QSpinBox* spb1;
    QSpinBox* spb2;

    unique_ptr<int> pointers[10];

    void fill_cells();
    int current_owner;
};
#endif // MAINWINDOW_H
