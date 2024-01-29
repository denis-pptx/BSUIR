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
#include <QPrinter>
#include <QTextDocument>
#include <QApplication>

#include "Task\TaskTypes\Task.h"
#include "Test.h"
#include "Task\TaskChoose.h"


// Сколько символов максимум влезет в список заданий теста
#define MAX_LIST_VIEW_LABEL_LEN 20

// Максимум и минимум заданий в тесте
#define MAX_TASK_NUM 100
#define MIN_TASK_NUM 0

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
    // TaskOperations
    void addTask();
    void removeTask();
    void checkTasksLimit();

    // TestOperations
    void createTest();
    void openTest();
    void saveTest();
    void saveAsTest();
    void removeTest();
    void exportPDF();

    // testSlots
    void connectTestSignals(Test*);
    void slot_testRemoved();
    void slot_testCreated();
    void slot_testOpened();

    // tasksListView
    void taskListViewPrint();                                                           // Распечатать список заданий теста
    void taskListView_clicked(const QModelIndex&);                                      // Клик по списку заданий теста
    void taskListView_rowsMoved(const QModelIndex&, int, int, const QModelIndex&, int); // Задание передвинуто
    void on_taskPasted(int numberOfPasted, int currentRow);
    void on_taskCopied(int numberOfCopied);

    // mainwindow
    int checkUnsavedChanges();                      // Проверка на наличие несохраненных изменений
    virtual void closeEvent(QCloseEvent*) override; // При закрытии окна

    // time
    void timeCheckBox_clicked(bool checked);
    void timeSpinBox_valueChanged(int arg1);



private:
    Ui::MainWindow *ui;
    Test* test;             // Текущий тест
    TaskChoose* taskChoose; // Окно выбора типа задания
};



#endif // MAINWINDOW_H
