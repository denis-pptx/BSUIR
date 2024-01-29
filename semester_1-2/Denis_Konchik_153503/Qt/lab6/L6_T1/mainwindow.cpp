#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), menu(new Menu()), model(new QStandardItemModel)
{
    ui->setupUi(this);
    setWindowTitle("L6_T1");
    setFixedSize(size());


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addButton_clicked()
{
    menu->activate(MenuSettings::ADD);

    if(menu->exec() == QDialog::Accepted) {

        Item item(menu->getKey(), menu->getText());

        //if (!items.contains(item)) {
            items.push_back(item);
            printItems();
       // }
    }
}

void MainWindow::printItems()
{

    model->clear();
    model->setColumnCount(2);
    model->setRowCount(items.size());

    model->setHeaderData(0, Qt::Horizontal, "Ключ");
    model->setHeaderData(1, Qt::Horizontal, "Текст");

    ui->tableView->setModel(model);

    for (int row = 0; row < items.size(); row++) {

        QModelIndex index = model->index(row, 0);
        model->setData(index, items[row].key);
        model->item(index.row(), index.column())->setEditable(false);

        index = model->index(row, 1);
        model->setData(index, items[row].str);
        model->item(index.row(), index.column())->setEditable(false);
    }
}


void MainWindow::on_tableToTreeButton_clicked() {

    tree.clear();

    for (int i = 0; i < items.size(); i++)
        tree.push(items[i]);
}


void MainWindow::on_directBypassButton_clicked()
{
    tree.directBypass();
    tree.bypass();
}


void MainWindow::on_symmetricalBypassButton_clicked()
{
    tree.symmetricalBypass();
    tree.bypass();
}


void MainWindow::on_backBypassButton_clicked()
{
    tree.backBypass();
    tree.bypass();
}

void MainWindow::on_widthBypassButton_clicked()
{
    tree.widthBypass();
    tree.bypass();
}

void MainWindow::on_printTreeButton_clicked()
{
    tree.show();
}


void MainWindow::on_addItemButton_clicked()
{

    menu->activate(MenuSettings::ADD);

    if(menu->exec() == QDialog::Accepted)
        tree.push(Item(menu->getKey(), menu->getText()));
}


void MainWindow::on_deleteItemButton_clicked()
{
    menu->activate(MenuSettings::DELETE);

    if (menu->exec() == QDialog::Accepted)
        tree.pop(Item(menu->getKey(), ""));
}




void MainWindow::on_findItemButton_clicked()
{
    menu->activate(MenuSettings::FIND);

    if (menu->exec() == QDialog::Accepted) {

        Node<Item>* node = tree.search(Item(menu->getKey(), ""));

        menu->setKey(menu->getKey());

        if (node)
            menu->setText(node->item.str);
        else
            menu->setText("NOT FOUND");

        menu->activate(MenuSettings::SHOW);
    }

}


void MainWindow::on_clearButton_clicked()
{
    tree.clear();
}


void MainWindow::on_variantButton_clicked()
{
    bool found = true;
    Item itm = tree.middle(found);

    if (found) {
        menu->setKey(itm.key);
        menu->setText(itm.str);
    } else {
        menu->setKey(0);
        menu->setText("EMPTY");
    }

    menu->activate(MenuSettings::SHOW);
}




