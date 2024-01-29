#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "deque.h"


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
    void on_push_back_Button_clicked();

    void on_push_front_Button_clicked();

    void on_pop_back_Button_clicked();

    void on_pop_front_Button_clicked();

    void on_clear_Button_clicked();

    void on_random_Button_clicked();

    void on_frontButton_clicked();

    void on_backButton_clicked();

    void on_pushButton_clicked();

    void on_plus_equal_Button_clicked();

    void on_minus_equal_Button_clicked();

    void on_iteratorEdit_Button_clicked();

    void on_equalButton_clicked();

    void on_updateButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    deque<QString> d;

    deque<QString>::iterator it;

    void print_deque();

    void print_iterator();
};
#endif // MAINWINDOW_H
