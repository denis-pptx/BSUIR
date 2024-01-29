#include "mainwindow.h"
#include "ui_mainwindow.h"


// Переменные каждого типа (1)
void MainWindow::on_variables_Button_clicked()
{
    SearchVariables();

    resetWindows();

    model = new QStandardItemModel(0, 2,this);
    QString enrolleeModelColumnName[] = {"Тип", "Строка с объявлением"};

    for (int column = 0; column < 2; column++)
        model->setHeaderData(column, Qt::Horizontal, enrolleeModelColumnName[column]);

    view = new QTableView;
    view->setModel(model);
    view->setWindowTitle("Переменные каждого типа");

    for (const auto& type : typesDeclare) {
        model->insertRow(model->rowCount());

        QModelIndex index = model->index(model->rowCount() - 1, 0);
        string number = string(QString::number(type.second.size()).toStdString().c_str());
        model->setData(index, (type.first + " — [" + number + "]").c_str());

        for (const auto& strVar : type.second) {
            model->insertRow(model->rowCount());
            index = model->index(model->rowCount() - 2, 1);
            model->setData(index, strVar.c_str());
        }
    }

    view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    size_t w = 500;
    size_t h = 400;
    view->setGeometry((wm - w) / 3, (hm - h) / 3, w, h);

    view->show();
}


// Сколько классов, массивов, структур инициализировано (2)
void MainWindow::on_classStructArray_Button_clicked()
{
    size_t classAmount = CountClasses();
    size_t structAmount = CountStructs();
    size_t arrayAmount = CountArrays();

    resetWindows();

    window = new QDialog;
    window->setWindowFlags(Qt::Window | Qt::Tool);
    window->setWindowTitle("Info");

    lay = new QGridLayout;

    lay->addWidget(new QLabel("Классов: "), 0, 0);
    lay->addWidget(new QLabel(QString::number(classAmount)), 0, 1);

    lay->addWidget(new QLabel("Структур: "), 1, 0);
    lay->addWidget(new QLabel(QString::number(structAmount)), 1, 1);

    lay->addWidget(new QLabel("Массивов: "), 2, 0);
    lay->addWidget(new QLabel(QString::number(arrayAmount)), 2, 1);

    window->setLayout(lay);
    window->show();
    window->activateWindow();
}

// Перегрузки функций (3, 6)
void MainWindow::on_funcProt_Button_clicked()
{

    SearchFunc();

    resetWindows();

    model = new QStandardItemModel(0, 4,this);
    QString enrolleeModelColumnName[] = {"Имя функции", "Перегрузки", "Строка", "Столбец"};

    for (int column = 0; column < 4; column++)
        model->setHeaderData(column, Qt::Horizontal, enrolleeModelColumnName[column]);

    view = new QTableView;
    view->setModel(model);
    view->setWindowTitle("Перегрузки функций");


    for (size_t i = 0; i < overloaded.size(); i++) {
        model->insertRow(model->rowCount());

        QModelIndex index = model->index(model->rowCount() - 1, 0);
        string number = string(QString::number(overloaded[i].second.size()).toStdString().c_str());
        model->setData(index, (overloaded[i].first + " — [" + number + "]").c_str());

        for (size_t j = 0; j < overloaded[i].second.size(); j++) {
            model->insertRow(model->rowCount());

            index = model->index(model->rowCount() - 2, 1);
            model->setData(index, overloaded[i].second[j].c_str());

            index = model->index(model->rowCount() - 2, 2);
            model->setData(index, coords[i][j].row + 1);

            index = model->index(model->rowCount() - 2, 3);
            model->setData(index, coords[i][j].column + 1);

        }
    }

    view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    size_t w = 500;
    size_t h = 400;
    view->setGeometry((wm - w) / 3, (hm - h) / 3, w, h);
    view->show();

}


// Координаты изменения каждой переменной (4)
void MainWindow::on_variablesEdit_Button_clicked()
{
    SearchVarEdit();

    resetWindows();

    model = new QStandardItemModel(0, 2,this);
    QString enrolleeModelColumnName[] = {"Строка", "Столбец"};

    for (int column = 0; column < 2; column++)
        model->setHeaderData(column, Qt::Horizontal, enrolleeModelColumnName[column]);

    view = new QTableView;
    view->setModel(model);
    view->setWindowTitle("Изменения переменных");

    for (const auto& i : coordsVarEdit) {
        model->insertRow(model->rowCount());

        QModelIndex index = model->index(model->rowCount() - 1, 0);
        model->setData(index, i.row + 1);

        index = model->index(model->rowCount() - 1, 1);
        model->setData(index, i.column + 1);
    }

    view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    size_t w = 180;
    size_t h = 300;
    view->setGeometry((wm - w) / 3, (hm - h) / 3, w, h);

    view->show();
}

// Локальные переменные и их координаты (5)
void MainWindow::on_localVariable_Button_clicked()
{

    CountLocalVariable();

    resetWindows();

    model = new QStandardItemModel(0, 2,this);
    QString enrolleeModelColumnName[] = {"Строка", "Столбец"};

    for (int column = 0; column < 2; column++)
        model->setHeaderData(column, Qt::Horizontal, enrolleeModelColumnName[column]);

    view = new QTableView;
    view->setModel(model);
    view->setWindowTitle("Локальные переменные");

    for (const auto& i : coordsVar) {
        model->insertRow(model->rowCount());

        QModelIndex index = model->index(model->rowCount() - 1, 0);
        model->setData(index, i.row + 1);

        index = model->index(model->rowCount() - 1, 1);
        model->setData(index, i.column + 1);
    }

    view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    size_t w = 180;
    size_t h = 300;
    view->setGeometry((wm - w) / 3, (hm - h) / 3, w, h);

    view->show();

}

// Ветвления (7)
void MainWindow::on_branching_Button_clicked()
{

    CountBranches();

    resetWindows();

    model = new QStandardItemModel(0, 3,this);
    QString enrolleeModelColumnName[] = {"Уровень", "Строка", "Столбец"};

    for (int column = 0; column < 3; column++)
        model->setHeaderData(column, Qt::Horizontal, enrolleeModelColumnName[column]);

    view = new QTableView;
    view->setModel(model);
    view->setWindowTitle("Ветвления");

    for (const auto& i : branching) {
        model->insertRow(model->rowCount());

        QModelIndex index = model->index(model->rowCount() - 1, 0);
        model->setData(index, i.first);

        index = model->index(model->rowCount() - 1, 1);
        model->setData(index, i.second.row + 1);

        index = model->index(model->rowCount() - 1, 2);
        model->setData(index, i.second.column + 1);
    }

    view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    size_t w = 210;
    size_t h = 300;
    view->setGeometry((wm - w) / 3, (hm - h) / 3, w, h);

    view->show();
}




// Ошибки (8)
void MainWindow::on_mistakes_Button_clicked()
{

    SearchMistakes();

    resetWindows();

    model = new QStandardItemModel(0, 2,this);
    QString enrolleeModelColumnName[] = {"Ошибка", "Строка"};

    for (int column = 0; column < 2; column++)
        model->setHeaderData(column, Qt::Horizontal, enrolleeModelColumnName[column]);

    view = new QTableView;
    view->setModel(model);
    view->setWindowTitle("Ошибки");

    for (const auto& i : mistakes) {
        model->insertRow(model->rowCount());

        QModelIndex index = model->index(model->rowCount() - 1, 0);
        model->setData(index, i.first.c_str());

        index = model->index(model->rowCount() - 1, 1);
        model->setData(index, i.second + 1);
    }

    view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    size_t w = 180;
    size_t h = 300;
    view->setGeometry((wm - w) / 3, (hm - h) / 3, w, h);

    view->show();
}


void MainWindow::on_helpButton_clicked()
{
    resetWindows();

    window = new QDialog;
    window->setWindowTitle("Info");
    window->setWindowFlags(Qt::Window | Qt::Tool);

    lay = new QGridLayout;
    lay->addWidget(new QLabel("Работа с кодом: \n"
                              "[Выбрать файл] - очевидно \n"
                              "[Сохранить] - сохранить текущие изменения \n"
                              "в файл и применить их к парсингу \n"
                              "Ctrl + S — сохранить\n"
                              "Ctrl + R — перезагрузить выбранный файл \n\n"
                              "[1 - 8] - функции в соответствии с заданием \n"
                              "[8] - виды ошибок: \n"
                              "if () { ... }, if { ... } \n"
                              "while() { ... }, while { ... } \n"
                              "while (true), while (false) \n"
                              "#if ... #endif"
                              ));

    window->setLayout(lay);
    window->show();
    window->setFixedSize(window->size());
    window->activateWindow();
}


