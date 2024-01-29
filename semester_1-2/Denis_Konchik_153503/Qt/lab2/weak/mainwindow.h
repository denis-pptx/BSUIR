#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "shared_ptr.h"
#include "weak_ptr.h"
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
    void on_pushButton_edit_shared_clicked();
    void on_pushButton_toElsePtr_shared_clicked();
    void on_pushButton_close_clicked();

    void appropriation_shared();
    void toElsePtr_shared();

    void poka();

    void on_pushButton_assign_weak_clicked();
    void assign_weak();

    void on_pushButton_assign_shared_clicked();
    void assign_shared();

    void on_pushButton_weakToShared_clicked();
    void weak_to_shared();


private:
    Ui::MainWindow *ui;

    QStandardItemModel* modelShared;
    QStandardItemModel* modelWeak;

    shared_ptr<int> pointersShared[10];
    weak_ptr<int> pointersWeak[10];

    QSpinBox* spb1;
    QSpinBox* spb2;

    void fill_cells_shared();
    void fill_cells_weak();

    bool isExistShared[10];
    bool isExistWeak[10];
};
#endif // MAINWINDOW_H
