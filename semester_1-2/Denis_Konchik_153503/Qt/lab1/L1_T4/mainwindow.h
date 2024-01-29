#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QFileDialog>
#include <QDialog>
#include "company.h"
#include "worker.h"
#include <cstdio>
#include <typeinfo>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void printCompanies();
    void printWorkers();

private slots:
    void slotChangedCompanies(QStandardItem*);
    void slotChangedWorkers(QStandardItem*);

    void on_addCompanyButton_clicked();
    void on_addWorkerButton_clicked();

    void addCompanyToArr();
    void addWorkerToArr();

    void delCompanyFromArr();
    void delWorkerFromArr();

    void on_deleteCompanyButton_clicked();
    void on_deleteWorkerButton_clicked();

    void on_companiesFolderButton_clicked();
    void on_workersFolderButton_clicked();


    void on_vacanciesForWorkerButton_clicked();
    void on_vacanciesWithoutWorkersButton_clicked();

    void on_resetColorButton_clicked();

    void on_helpButton_clicked();

    void activateFieldWorkers() { isFieldWorkersActive = true; }
    void slotHide() { hide(); }

private:
    Ui::MainWindow *ui;
    QStandardItemModel* modelCompanies;
    QStandardItemModel* modelWorkers;

    void setDefaultInputs();
    QLineEdit* line;
    QSpinBox* spb;
    QSpinBox* spbDel;
    QComboBox* cmb;

    bool isFieldWorkersActive;

    template<class T>
    T* fileParse(T* arr, QString filename, int& N);

    template<class T>
    void fileRewrite(T* arr, QString filename, int& N);

    void msgBadFile(QString badFile);
};
#endif // MAINWINDOW_H
