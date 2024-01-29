#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_sortButton_clicked()
{
    closeWindows();
    if (!statement.size()) {
        QMessageBox::warning(this, "Warning", "Список пуст");;
        return;
    }

    sortMenu->activate();

    if(sortMenu->exec() == QDialog::Accepted) {
        Columns column = (Columns)sortMenu->getField();

        if (!sortMenu->getOrder()) {

            switch(column) {
            case Surname:
                statement.sort([](const Enrollee& left, const Enrollee& right){
                    return left.getSurname().toLower() < right.getSurname().toLower(); });
                break;

            case Name:
                statement.sort([](const Enrollee& left, const Enrollee& right){
                    return left.getName().toLower() < right.getName().toLower(); });
                break;

            case Patronymic:
                statement.sort([](const Enrollee& left, const Enrollee& right){
                    return left.getPatronymic().toLower() < right.getPatronymic().toLower(); });
                break;

            case City:
                statement.sort([](const Enrollee& left, const Enrollee& right){
                    return left.getCity().toLower() < right.getCity().toLower(); });
                break;

            case Score:
                statement.sort([](const Enrollee& left, const Enrollee& right){
                    return left.getScore() < right.getScore(); });
                break;

            default:
                qDebug() << "Sort error " + QString::number(column);

            }

        } else {

            switch(column) {
            case Surname:
                statement.sort([](const Enrollee& left, const Enrollee& right){
                    return left.getSurname().toLower() > right.getSurname().toLower(); });
                break;

            case Name:
                statement.sort([](const Enrollee& left, const Enrollee& right){
                    return left.getName().toLower() > right.getName().toLower(); });
                break;

            case Patronymic:
                statement.sort([](const Enrollee& left, const Enrollee& right){
                    return left.getPatronymic().toLower() > right.getPatronymic().toLower(); });
                break;

            case City:
                statement.sort([](const Enrollee& left, const Enrollee& right){
                    return left.getCity().toLower() > right.getCity().toLower(); });
                break;

            case Score:
                statement.sort([](const Enrollee& left, const Enrollee& right){
                    return left.getScore() > right.getScore(); });
                break;

            default:
                qDebug() << "Sort error " + QString::number(column);

            }
        }

        printEnrollee();
        fileRewrite();
    }
}


