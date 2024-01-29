#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QGridLayout>
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#include <QCloseEvent>
#include <QMessageBox>
#include <QAbstractItemModel>

#include "Task\TaskTypes\Task.h"
#include "Test.h"
#include "TestPassingWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// ГЛАВНОЕ ОКНО
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openTestButton_clicked();
    void on_startTestButton_clicked();
    void on_name_lineEdit_textEdited(const QString &arg1);
    void on_surname_lineEdit_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Test* test;                       // Текущий тест
    PassingTestWindow* passingWindow; // Окно прохождения теста
    bool testOpened;                  // Открыт ли тест
};



#endif // MAINWINDOW_H
