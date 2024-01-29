#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include "ring.h"


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


    void on_push_prev_Button_clicked();

    void on_push_next_Button_clicked();

    void on_go_next_Button_clicked();

    void on_go_prev_Button_clicked();

    void on_pop_Button_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    ring<QPair<QPixmap, QString> > flags;

    QVector<QString> countries;

    QPixmap empty;

    void pushNext(const QString& name);
    void pushPrev(const QString& name);

    void setCurrentPicture();
    void setEmpty();
};
#endif // MAINWINDOW_H
