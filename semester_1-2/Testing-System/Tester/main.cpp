#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Rus");
    QApplication a(argc, argv);

//    QFile styleSheetFile("../StyleSheet/AMOLED.qss");
//    styleSheetFile.open(QFile::ReadOnly);
//    QString styleSheet = QLatin1String(styleSheetFile.readAll());
//    a.setStyleSheet(styleSheet);

    MainWindow w;
    w.show();
    return a.exec();
}
