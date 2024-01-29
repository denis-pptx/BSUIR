#include "MainWindow/mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::exportPDF()
{
    QUrl fileUrl = QFileDialog::getSaveFileName(this, tr("Export to PDF"), test->getFileName(), tr("*.pdf"));

    if (fileUrl.toString() == "")
        return;

    test->savePDF(fileUrl);
}
