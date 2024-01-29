#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "date.h"
#include <QMainWindow>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QTableWidget>
#include <QDialog>
#include <QLabel>
#include <QDateEdit>
#include <QFileDialog>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern QString storage;
extern Date* dateArray;
extern int N;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    void printAllDates();

private slots:
    void on_infoButton_clicked();
    void on_birthButton_clicked();
    void on_daysToBirthButton_clicked();
    void on_addDayButton_clicked();

    void on_choseFile_clicked();
    void on_helpButton_clicked();

    void setDateOfBirth();
    void updateFile(QStandardItem*);
    void addDate();

    void slotHide() { hide(); }
private:
    Date birthDayDate;
    QDateEdit* dateEdit;
    Ui::MainWindow *ui;
    QStandardItemModel* model;


    void parseFile();
    void insertInFile(int, QString, bool = false);
    bool isDateInFormat(QString date);
    void msgFileBadDate(QString badDate, int strNum);

};

;

#endif // MAINWINDOW_H
