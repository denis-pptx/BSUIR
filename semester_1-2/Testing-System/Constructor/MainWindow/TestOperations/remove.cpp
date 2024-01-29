#include "MainWindow/mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::removeTest() {

    int ret = QMessageBox::warning(this, windowTitle(),
                                   QString("Do you want to delete test \"") + test->getUrl().fileName() + QString("\"?"),
                                   QMessageBox::Yes | QMessageBox::No
                                   );

    if (ret == QMessageBox::Yes) {
        test->remove(); 
        delete test;
        test = nullptr;
    }
}
