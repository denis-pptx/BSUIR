#include "mainwindow.h"
#include <QApplication>

QString storage = "dates.txt";
Date* dateArray = nullptr;
int N = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow;
    return a.exec();
}
