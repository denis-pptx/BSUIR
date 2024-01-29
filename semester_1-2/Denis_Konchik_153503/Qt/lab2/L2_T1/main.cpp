#include "mainwindow.h"
#include "unique_ptr.h"
#include "shared_ptr.h"
#include "weak_ptr.h"
#include <iostream>
#include <QApplication>
using std::cout;
using namespace p;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();

    unique_ptr<MainWindow> ptr1 = new MainWindow;
    ptr1.get_ptr()->show();
    unique_ptr<MainWindow> ptr2 = ptr1;


    return a.exec();
}
