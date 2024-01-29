#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_addEnrolleeButton_clicked()
{
    closeWindows();
    enrolleeMenuAdd->activate();

    if(enrolleeMenuAdd->exec() == QDialog::Accepted) {

        statement.push_back(
                    Enrollee(enrolleeMenuAdd->getSurname(), enrolleeMenuAdd->getName(),
                            enrolleeMenuAdd->getPatronymic(), enrolleeMenuAdd->getCity(), enrolleeMenuAdd->getScore()));

        printEnrollee();
        setSpinboxesRange();
        fileRewrite();
    }
}

void MainWindow::on_editEnrolleeButton_clicked()
{
    int editNumber = ui->editSpinBox->value();

    closeWindows();
    if (!statement.size()) {
        QMessageBox::warning(this, "Warning", "Список пуст");
        return;
    }

    stupid_list::list<Enrollee>::iterator it = statement.begin();
    for (int i = 0; i < editNumber - 1; i++)
        ++it;

    enrolleeMenuEdit->activate(it);

    if(enrolleeMenuEdit->exec() == QDialog::Accepted) {

        (*it).setSurname(enrolleeMenuEdit->getSurname());
        (*it).setName(enrolleeMenuEdit->getName());
        (*it).setPatronymic(enrolleeMenuEdit->getPatronymic());
        (*it).setCity(enrolleeMenuEdit->getCity());
        (*it).setScore(enrolleeMenuEdit->getScore());

        printEnrollee();
        fileRewrite();
    }
}

void MainWindow::on_enrolleeView_doubleClicked(const QModelIndex &index)
{
    ui->editSpinBox->setValue(index.row() + 1);
    on_editEnrolleeButton_clicked();
}


