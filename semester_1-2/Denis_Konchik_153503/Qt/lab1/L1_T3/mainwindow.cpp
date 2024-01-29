#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow()
    : ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowTitle("Даты");

    parseFile();
    model = new QStandardItemModel(this);
    QObject::connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(updateFile(QStandardItem*)));

    printAllDates();

    show();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::printAllDates() {

    delete model;

    model = new QStandardItemModel(N, 3, this);
    model->blockSignals(true);
    model->setHeaderData(0, Qt::Horizontal, "Дата");
    model->setHeaderData(1, Qt::Horizontal, "Следующий");
    model->setHeaderData(2, Qt::Horizontal, "Разница");
    ui->tableView->setModel(model);


    QModelIndex index;

    for (int row = 0; row < model->rowCount(); row++) {
        for (int column = 0; column < model->columnCount(); column++) {
            index = model->index(row, column);
            if (column == 0)
                model->setData(index, dateArray[row].toString());
            else if (column == 1)
                model->setData(index, dateArray[row].nextDate().toString());
            else if (column == 2 && row < model->rowCount() - 1)
                model->setData(index, dateArray[row].duration(dateArray[row + 1]));
            else if (column == 2 && row == model->rowCount() - 1)
                model->setData(index, "—");
        }
    }

    for (int row = 0; row < model->rowCount(); row++) {
        model->item(row, 1)->setEditable(false);
        model->item(row, 2)->setEditable(false);
    }

    QObject::connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(updateFile(QStandardItem*)));
    model->blockSignals(false);
}

void MainWindow::updateFile(QStandardItem* item) {

    QModelIndex index;
    index = model->index(item->row(), item->column());

    QString str = model->data(index).toString();

    Date tmp;
    if (!tmp.isDateCorrect(str)) {
        msgFileBadDate(str, item->row() + 1);
        return;
    }

    insertInFile(item->row() + 1, str);
    dateArray[item->row()] = toDate(str);

    printAllDates();
}


void MainWindow::on_infoButton_clicked() {
    QModelIndex index = ui->tableView->currentIndex();

    if (index.column() == 0 || index.column() == 1) {
        QDialog* infoBox = new QDialog;
        infoBox->setWindowTitle("Info");
        infoBox->setWindowFlags(Qt::Window | Qt::Tool);


        QGridLayout* lay = new QGridLayout;

        lay->addWidget(new QLabel("Текущий день: "), 0, 0);
        lay->addWidget(new QLabel(model->data(index).toString()), 0, 1);
        lay->addWidget(new QLabel("Следующий день: "), 1, 0);
        lay->addWidget(new QLabel((toDate(model->data(index).toString()).nextDate()).toString()), 1, 1);
        lay->addWidget(new QLabel("Предыдущий день: "), 2, 0);
        lay->addWidget(new QLabel((toDate(model->data(index).toString()).previousDate()).toString()), 2, 1);
        lay->addWidget(new QLabel("Дней в году: "), 3, 0);

        if ((toDate(model->data(index).toString())).isLeap())
            lay->addWidget(new QLabel("366"), 3, 1);
        else
            lay->addWidget(new QLabel("365"), 3, 1);

        lay->addWidget(new QLabel("Номер недели в году: "), 4, 0);
        lay->addWidget(new QLabel(QString::number((toDate(model->data(index).toString())).weakNumber())), 4, 1);

        infoBox->setLayout(lay);
        infoBox->show();
        infoBox->activateWindow();
    }
}

void MainWindow::setDateOfBirth() {
    birthDayDate = Date(dateEdit->date().day(), dateEdit->date().month(), dateEdit->date().year());
}

void MainWindow::on_birthButton_clicked() {
    time_t rawtime;
    tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    QDate current(timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);

    QDialog* Box = new QDialog;
    Box->setWindowTitle("ДР");
    Box->setWindowFlags(Qt::Window | Qt::Tool);

    QVBoxLayout* lay = new QVBoxLayout;
    lay->addWidget(new QLabel("Дата рождения:"));

    dateEdit = new QDateEdit;
    dateEdit->setDateRange(QDate(1, 1, 1), current);
    dateEdit->setDate(QDate(2004, 7, 1));
    lay->addWidget(dateEdit);

    QPushButton* Ok = new QPushButton("&Ок");
    lay->addWidget(Ok);

    connect(Ok, SIGNAL(clicked()), this, SLOT(setDateOfBirth()));
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));

    Box->setLayout(lay);
    Box->show();
    Box->activateWindow();
}


void MainWindow::on_daysToBirthButton_clicked() {
    QDialog* Box = new QDialog;
    Box->setWindowTitle("ДР");
    Box->setWindowFlags(Qt::Window | Qt::Tool);


    QVBoxLayout* lay = new QVBoxLayout;
    lay->addWidget(new QLabel("До Дня рождения: "));

    lay->addWidget(new QLabel(QString::number(daysTillYourBithday(birthDayDate)) + " день / дня / дней"));

    lay->addWidget(new QLabel("Дата рождения: "));
    lay->addWidget(new QLabel(birthDayDate.toString()));

    QPushButton* Ok = new QPushButton("&Ок");
    lay->addWidget(Ok);
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));

    Box->setLayout(lay);
    Box->show();
    Box->activateWindow();

}


void MainWindow::addDate() {
    dateArray = (Date*)realloc(dateArray, ++N * sizeof(Date));
    dateArray[N - 1] = Date(dateEdit->date().day(), dateEdit->date().month(), dateEdit->date().year());
    insertInFile(N, dateArray[N-1].toString(), true);
    printAllDates();
}

void MainWindow::on_addDayButton_clicked() {
    QDialog* Box = new QDialog;
    Box->setWindowTitle("Add");
    Box->setWindowFlags(Qt::Window | Qt::Tool);

    QVBoxLayout* lay = new QVBoxLayout;
    lay->addWidget(new QLabel("Новая дата:"));

    dateEdit = new QDateEdit;
    dateEdit->setDateRange(QDate(1, 1, 1), QDate(9999, 12, 31));
    dateEdit->setDate(QDate(rand() % 300 + 1900, rand() % 12 + 1, rand() % 25 + 1));
    lay->addWidget(dateEdit);

    QPushButton* Ok = new QPushButton("&Ок");
    lay->addWidget(Ok);

    connect(Ok, SIGNAL(clicked()), this, SLOT(addDate()));
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));

    Box->setLayout(lay);
    Box->show();
    Box->activateWindow();
}


void MainWindow::on_choseFile_clicked() {

    QString newStorage = QFileDialog::getOpenFileName(0, "Выберите файл", "", "*.txt");
    if (newStorage == "")
        return;

    storage = newStorage;

    N = 0;
    free(dateArray);
    dateArray = nullptr;
    parseFile();
    printAllDates();
}


void MainWindow::on_helpButton_clicked() {
    QDialog* infoWindow = new QDialog(this);
    infoWindow->setWindowTitle("Info");
    infoWindow->setWindowFlags(Qt::Window | Qt::Tool);

    QVBoxLayout* lay = new QVBoxLayout;
    lay->addWidget(new QLabel("Работа с программой: \n"
                              "[Разница] - между датой в данной строке \n"
                              "и датой, находящейся в следующей строке \n"
                              "[Установить ДР] - установить День рождения\n"
                              "[Информация о дне] - информация о дне,\n"
                              "выбранном в таблице курсором \n"
                              "[Добавить день] - добавить дату \n"
                              "[Выбрать файл] - выбрать файл с датами\n\n"
                              "Все даты необходимо вводить в корректном\n"
                              "формате — ДД.ММ.ГГГГ \n\n"
                              "В файле даты должны быть как ДД.ММ.ГГГГ \n"
                              "и располагаться в столбик одна под одной"
                              ));


    QPushButton* Ok = new QPushButton("&Ок");
    lay->addWidget(Ok);
    connect(Ok, SIGNAL(clicked()), infoWindow, SLOT(accept()));

    infoWindow->setLayout(lay);
    infoWindow->show();
    infoWindow->activateWindow();
}




bool MainWindow::isDateInFormat(QString date) {
    std::regex rx("((0[1-9]|[12][0-9]|3[01])[- /.]"
                 "(0[1-9]|1[012])[- /.]"
                 "([0-9]{3}[1-9]|[0-9]{2}[1-9][0-9]{1}|[0-9]{1}[1-9][0-9]{2}|[1-9][0-9]{3}))");

    if (date.length() < 10 || date[2] != '.' || date[5] != '.')
        return false;

    return std::regex_match(date.toStdString().c_str(), rx);
}

void MainWindow::parseFile() {

    QFile file;
    file.setFileName(storage);

    if (file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        while (!stream.atEnd()) {
            QString line;
            stream >> line;


            Date tmp;
            if (line == "") {
                break;
            } else if (!tmp.isDateCorrect(line)) {
                msgFileBadDate(line, N + 1);
                break;
            }


            dateArray = (Date*)realloc(dateArray, ++N * sizeof(Date));
            dateArray[N - 1] = toDate(line);
        }
    } else {
        qDebug() << "BAD OPEN";
    }

    file.close();
}

void MainWindow::insertInFile(int n, QString date, bool addElement) {
    QFile file;
    file.setFileName(storage);


    if (file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        stream.seek(12 * (n - 1));
        stream << date;
        if (addElement)
            stream << "\n";
    } else {
        qDebug() << "BAD OPEN";
    }

    file.close();
}

void MainWindow::msgFileBadDate(QString badDate, int strNum) {
    dateArray = nullptr;
    N = 0;

    QDialog* msgBox = new QDialog;
    msgBox->setWindowTitle("Bad file");
    msgBox->setWindowFlags(Qt::Window | Qt::Tool);

    QVBoxLayout* lay = new QVBoxLayout(msgBox);
    lay->addWidget(new QLabel("Некорректная дата: " + badDate +
                              "\nСтрока: " + QString::number(strNum)));


    QPushButton* Ok = new QPushButton("&Ок");
    lay->addWidget(Ok);

    msgBox->show();
    msgBox->activateWindow();

    QTimer::singleShot(10, this, SLOT(slotHide()));
    QObject::connect(msgBox, SIGNAL(rejected()), this, SLOT(close()));
    QObject::connect(Ok, SIGNAL(clicked()), msgBox, SLOT(accept()));

}
