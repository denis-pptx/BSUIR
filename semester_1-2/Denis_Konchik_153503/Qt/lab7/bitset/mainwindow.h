#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bitset.h"

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
    void on_equalButton_clicked();

    void on_allButton_clicked();

    void on_anyButton_clicked();

    void on_countButton_clicked();

    void on_flipButton_clicked();

    void on_noneButton_clicked();

    void on_resetButton_clicked();

    void on_setButton_clicked();

    void on_testButton_clicked();

    void on_sizeButton_clicked();

private:
    Ui::MainWindow *ui;

    QString boolToStr(bool b);

    void print();

    bitset<32> set;
};
#endif // MAINWINDOW_H
