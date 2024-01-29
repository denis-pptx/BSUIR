#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowTitle("Польская запись");

    expressionMenuAdd = new ExpressionMenuAdd;

    print();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::print() {
    model = new QStandardItemModel(15, 8, this);
    ui->view->setModel(model);

    QString columnName[] = {"Выражение", "ОПЗ", "a", "b", "c", "d", "e", "Результат" };
    for (int column = 0; column < 8; column++)
        model->setHeaderData(column, Qt::Horizontal, columnName[column]);

    QString expression[15] = { "a/(b-c)*(d+e)",
                             "(a+b)*(c-d)/e",
                             "a-(b+c*d)/e",
                             "a/b-((c+d)*e)",
                             "a*(b-c+d)/e",
                             "(a+b)*(c-d)/e",
                             "a*(b-c)/(d+e)",
                             "a/(b*(c+d))-e",
                             "(a+(b/c-d))*e",
                             "a*(b+c)/(d-e)",
                             "a-(b/c*(d+e))",
                             "(a-b)/(c+d)*e",
                             "a/(b+c-d*e)",
                             "a*(b-c)/(d+e)",
                             "(a+b*c)/(d-e)"};

    double numbers[15][5] = { {8.6, 2.4, 5.1, 0.3, 7.9},
                              {7.4, 3.6, 2.8, 9.5, 0.9},
                              {3.1, 5.4, 0.2, 9.6, 7.8},
                              {1.2, 0.7, 9.3, 6.5, 8.4},
                              {9.7, 8.2, 3.6, 4.1, 0.5},
                              {0.8, 4.1, 7.9, 6.2, 3.5},
                              {1.6, 4.9, 5.7, 0.8, 2.3},
                              {8.5, 0.3, 2.4, 7.9, 1.6},
                              {5.6, 7.4, 8.9, 3.1, 0.2},
                              {0.4, 2.3, 6.7, 5.8, 9.1},
                              {5.6, 3.2, 0.9, 1.7, 4.8},
                              {0.3, 6.7, 8.4, 9.5, 1.2},
                              {7.6, 4.8, 3.5, 9.1, 0.2},
                              {0.5, 6.1, 8.9, 2.4, 7.3},
                              {9.1, 0.6, 2.4, 3.7, 8.5} };


    for (int row = 0; row < 15; row++) {
        PolishEntry entry(numbers[row], expression[row]);
        for (int column = 0; column < 8; column++) {

            QModelIndex index = model->index(row, column);
            model->setData(index, entry.getColumnByIndex(column));
            model->item(row, column)->setEditable(false);
        }
    }
}


void MainWindow::on_addButton_clicked()
{
    expressionMenuAdd->activate();

    if(expressionMenuAdd->exec() == QDialog::Accepted) {

        try {
            PolishEntry entry(expressionMenuAdd->getNumbers(), expressionMenuAdd->getInfix());
            model->insertRow(model->rowCount());
            for (int column = 0; column < 8; column++) {

                QModelIndex index = model->index(model->rowCount() - 1, column);
                model->setData(index, entry.getColumnByIndex(column));
                model->item(model->rowCount() - 1, column)->setEditable(false);
            }
        }
        catch(...) {
            double* numbers = new double[5];
            numbers = expressionMenuAdd->getNumbers();
            QMessageBox::critical(this, "Warning", "Некорректное выражение и/или данные"
                                                   "\nВыражение: " + expressionMenuAdd->getInfix() +
                                                   "\na = " + QString::number(numbers[0]) +
                                                   "\nb = " + QString::number(numbers[1]) +
                                                   "\nc = " + QString::number(numbers[2]) +
                                                   "\nd = " + QString::number(numbers[3]) +
                                                   "\ne = " + QString::number(numbers[4]));

            return;
        }

    }


}

