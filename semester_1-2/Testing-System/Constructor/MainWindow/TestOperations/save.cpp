#include "MainWindow/mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::saveTest() {
    test->save();
}

void MainWindow::saveAsTest() {

    QString fileUrl = QFileDialog::getSaveFileName(this, tr("Save test"), test->getUrl().fileName(), tr("Test (*.tst)"));

    if (fileUrl != "") {
        ui->fileNameLine->setFileUrl(fileUrl);
        test->saveAs(fileUrl);
    }
}
