#include "MainWindow/mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::openTest() {

    QString fileUrl = QFileDialog::getOpenFileName(0, tr("Open test"), "", tr("*.tst"));

    if (fileUrl == "")
        return;

    if (checkUnsavedChanges() == QMessageBox::Cancel)
        return;

    delete test;
    test = new Test(fileUrl);

    connectTestSignals(test);
    test->open();
}
