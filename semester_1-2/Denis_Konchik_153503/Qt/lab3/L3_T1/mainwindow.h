#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>

#include "product.h"
#include "node_list.h"
#include "productmenu.h"
#include "sortmenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_addProductButton_clicked();
    void on_editProductButton_clicked();
    void on_deleteProductButton_clicked();


    void setSpinboxesRange();
    void setSpinBoxNumber(const QModelIndex& index);



    void on_settingsProductButton_clicked();

    void on_expectedProductButton_clicked();

    void on_sortButton_clicked();

    void on_storedFromSpinBox_valueChanged(int arg1);

    void on_priceFromSpinBox_valueChanged(double arg1);

    void on_amountFromSpinBox_valueChanged(int arg1);

    void on_fileButton_clicked();

    void on_aboutProductButton_clicked();

    void on_productView_doubleClicked(const QModelIndex &index);

private:

    void printProducts();
    void printProductWithSettings();
    void printExpectedProduct();
    void printProductByName(QString product);
    bool isSuitableProduct(node_list::list<Product>::iterator& it);

    bool fileParse();
    void fileRewrite();

    void closeWindows();

    Ui::MainWindow *ui;

    ProductMenuAdd* productMenuAdd;
    ProductMenuEdit* productMenuEdit;
    // ProductMenuView* productMenuView;

    SortMenu* sortMenu;

    QString filename;

    enum Columns { Name, Amount, Price, Date };

    QStandardItemModel* productModel;
    QTableView* viewWindow;

    node_list::list<Product> warehouse;
};
#endif // MAINWINDOW_H
