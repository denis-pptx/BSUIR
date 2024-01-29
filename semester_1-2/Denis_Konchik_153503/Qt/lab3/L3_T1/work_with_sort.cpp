#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_sortButton_clicked()
{
    closeWindows();
    if (!warehouse.size()) {
        QMessageBox::warning(this, "Warning", "Список пуст");;
        return;
    }

    sortMenu->activate();

    if(sortMenu->exec() == QDialog::Accepted) {
        Columns column = (Columns)sortMenu->getField();

        if (!sortMenu->getOrder()) {

            switch(column) {
            case Name:
                warehouse.sort([](const Product& left, const Product& right){
                    return left.getName().toLower() <= right.getName().toLower(); });
                break;

            case Amount:
                warehouse.sort([](const Product& left, const Product& right){
                    return left.getAmount() <= right.getAmount(); });
                break;

            case Price:
                warehouse.sort([](const Product& left, const Product& right){
                    return left.getPrice() <= right.getPrice(); });
                break;

            case Date:
                warehouse.sort([](const Product& left, const Product& right){
                    return left.getDate() <= right.getDate(); });
                break;

            default:
                qDebug() << "Sort error " + QString::number(column);

            }

        } else {

            switch(column) {
            case Name:
                warehouse.sort([](const Product& left, const Product& right){
                    return left.getName().toLower() >= right.getName().toLower(); });
                break;

            case Amount:
                warehouse.sort([](const Product& left, const Product& right){
                    return left.getAmount() >= right.getAmount(); });
                break;

            case Price:
                warehouse.sort([](const Product& left, const Product& right){
                    return left.getPrice() >= right.getPrice(); });
                break;

            case Date:
                warehouse.sort([](const Product& left, const Product& right){
                    return left.getDate() >= right.getDate(); });
                break;

            default:
                qDebug() << "Sort error " + QString::number(column);
            }
        }

        printProducts();
        fileRewrite();
    }
}


