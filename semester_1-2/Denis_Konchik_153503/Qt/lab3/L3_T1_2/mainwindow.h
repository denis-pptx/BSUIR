#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QTableView>

#include "sortmenu.h"
#include "stupid_list.h"
#include "enrollee.h"
#include "enrolleemenu.h"

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
    void on_fileButton_clicked();

    void setSpinboxesRange();

    void on_addEnrolleeButton_clicked();


    void on_editEnrolleeButton_clicked();

    void on_deleteEnrolleeButton_clicked();

    void setSpinBoxNumber(const QModelIndex& index);

    void on_aboutEnrolleePushButton_clicked();

    void on_fromCityPushButton_clicked();

    void on_fromScorePushButton_clicked();

    void on_deleteApplicantsButton_clicked();

    void on_sortButton_clicked();

    void on_enrolleeView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    stupid_list::list<Enrollee> statement;
    int vacantPlace;

    QString filename;
    bool fileParse();
    void fileRewrite();

    QStandardItemModel* enrolleeModel;

    EnrolleeMenuAdd* enrolleeMenuAdd;
    EnrolleeMenuEdit* enrolleeMenuEdit;
    // EnrolleeMenuView* enrolleeMenuView;
    SortMenu* sortMenu;

    QTableView* viewWindow;

    void printEnrollee();
    void printEnrolleeFromCity(QString city);
    void printEnrolleeFromScore(int score);
    void printEnrolleeBySurname(QString product);

    void closeWindows();

    enum Columns { Surname, Name, Patronymic, City, Score };
};
#endif // MAINWINDOW_H
