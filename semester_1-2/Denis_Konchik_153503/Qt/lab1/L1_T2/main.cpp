#include "mainwidget.h"
#include <QApplication>
#include <ctime>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    return a.exec();
}
