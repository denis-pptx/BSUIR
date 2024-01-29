#include "MainWindow/mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::createTest() {

    if (checkUnsavedChanges() == QMessageBox::Cancel)
        return;

    QString fileUrl = QFileDialog::getSaveFileName(this, tr("Create test"), "untitled.tst", tr("Test (*.tst)"));

    if (fileUrl == "")
        return;

    delete test;
    test = new Test(fileUrl);

    connectTestSignals(test);
    test->create();

}
