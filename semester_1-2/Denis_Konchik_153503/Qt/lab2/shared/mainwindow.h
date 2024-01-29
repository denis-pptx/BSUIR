#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "shared_ptr.h"
using namespace p;

#include <sstream>
#include <string>

#include <QMessageBox>
#include <QTimer>
#include <QThread>
#include <QLabel>
#include <QLayout>
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
    void on_pushButton_edit_clicked();
    void on_pushButton_toElsePtr_clicked();
    void on_pushButton_close_clicked();

    void appropriation();
    void toElsePtr();

    void poka();

    void on_resetButton_clicked();
    void reset();

    void on_swapButton_clicked();
    void swap();

private:
    Ui::MainWindow *ui;
    QStandardItemModel* model;

    shared_ptr<int> pointers[10];

    QSpinBox* spb1;
    QSpinBox* spb2;

    void fill_cells();

    bool isExist[10];
};
#endif // MAINWINDOW_H
