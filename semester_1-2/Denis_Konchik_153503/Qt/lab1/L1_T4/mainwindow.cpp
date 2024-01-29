#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDialog>

QString fileCompanies = "companies.bin";
Company* arrCompanies = nullptr;
int amountCompanies = 0;

QString fileWorkers = "workers.bin";
Worker* arrWorkers = nullptr;
int amountWorkers = 0;

void copy(char*, QString);
bool compare(const char*, const char*);
bool strToBool(const QString);
QString boolToStr(const bool);
bool isSuitable(const Company&, const Worker&);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    line = new QLineEdit[3];
    spb = new QSpinBox[4];
    spbDel = new QSpinBox;
    cmb = new QComboBox;
    cmb->addItem("NO");
    cmb->addItem("YES");
    isFieldWorkersActive = false;

    ui->setupUi(this);
    ui->viewWorkers->selectRow(-1);
    setFixedSize(size());

    arrCompanies = fileParse(arrCompanies, fileCompanies, amountCompanies);
    arrWorkers = fileParse(arrWorkers, fileWorkers, amountWorkers);

    modelCompanies = new QStandardItemModel(this);
    modelWorkers = new QStandardItemModel(this);

    printCompanies();
    printWorkers();
}

void MainWindow::printCompanies() {

    delete modelCompanies;

    modelCompanies = new QStandardItemModel(amountCompanies, 8,this);
    modelCompanies->blockSignals(true);
    QString modelCompaniesColumnName[8] = {"Company name", "Speciality", "Post", "Salary", "Vocation", "Higher\neducation", "Age from", "Age to"};

    for (int column = 0; column < 8; column++)
        modelCompanies->setHeaderData(column, Qt::Horizontal, modelCompaniesColumnName[column]);
    ui->viewCompanies->setModel(modelCompanies);

    QModelIndex index;

    for (int i = 0; i < modelCompanies->rowCount(); i++) {
        for (int j = 0; j < modelCompanies->columnCount(); j++) {

            index = modelCompanies->index(i, j);

            if (j == 0)
                modelCompanies->setData(index, arrCompanies[i].name);
            else if (j == 1)
                modelCompanies->setData(index, arrCompanies[i].speciality);
            else if (j == 2)
                modelCompanies->setData(index, arrCompanies[i].post);
            else if (j == 3)
                modelCompanies->setData(index, arrCompanies[i].salary);
            else if (j == 4)
                modelCompanies->setData(index, arrCompanies[i].vacationDays);
            else if (j == 5)
                modelCompanies->setData(index, boolToStr(arrCompanies[i].isNeedHigherEducation));
            else if (j == 6)
                modelCompanies->setData(index, arrCompanies[i].minAge);
            else if (j == 7)
                modelCompanies->setData(index, arrCompanies[i].maxAge);

        }
    }

    modelCompanies->blockSignals(false);
    QObject::connect(modelCompanies, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slotChangedCompanies(QStandardItem*)));
}


void MainWindow::printWorkers() {

    delete modelWorkers;

    modelWorkers = new QStandardItemModel(amountWorkers, 6,this);
    modelWorkers->blockSignals(true);
    QString modelWorkersColumnName[6] = {"Name", "Age", "Speciality", "Higher\neducation", "Desired\npost", "Minimal\nsalary"};

    for (int column = 0; column < 6; column++)
        modelWorkers->setHeaderData(column, Qt::Horizontal, modelWorkersColumnName[column]);
    ui->viewWorkers->setModel(modelWorkers);

    QModelIndex index;

    for (int i = 0; i < modelWorkers->rowCount(); i++) {
        for (int j = 0; j < modelWorkers->columnCount(); j++) {

            index = modelWorkers->index(i, j);

            if (j == 0)
                modelWorkers->setData(index, arrWorkers[i].name);
            else if (j == 1)
                modelWorkers->setData(index, arrWorkers[i].age);
            else if (j == 2)
                modelWorkers->setData(index, arrWorkers[i].speciality);
            else if (j == 3)
                modelWorkers->setData(index, boolToStr(arrWorkers[i].hasHigherEducation));
            else if (j == 4)
                modelWorkers->setData(index, arrWorkers[i].post);
            else if (j == 5)
                modelWorkers->setData(index, arrWorkers[i].minSalary);
        }
    }

    modelWorkers->blockSignals(false);
    QObject::connect(modelWorkers, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slotChangedWorkers(QStandardItem*)));

}

void MainWindow::slotChangedCompanies(QStandardItem* item) {
    QModelIndex index;
    index = modelCompanies->index(item->row(), item->column());


    int i = item->row();
    int j = item->column();

    if (j == 0)
        copy(arrCompanies[i].name, modelCompanies->data(index).toString());
    else if (j == 1)
        copy(arrCompanies[i].speciality, modelCompanies->data(index).toString());
    else if (j == 2)
        copy(arrCompanies[i].post, modelCompanies->data(index).toString());
    else if (j == 3) {
        int f_salary = modelCompanies->data(index).toInt();
        if (f_salary < 0)
            modelCompanies->setData(index, arrCompanies[i].salary);
        else
            arrCompanies[i].salary = f_salary;
    }
    else if (j == 4) {
        int f_vacationDays = modelCompanies->data(index).toInt();
        if (f_vacationDays < 0)
            modelCompanies->setData(index, arrCompanies[i].vacationDays);
        else
            arrCompanies[i].vacationDays = f_vacationDays;
    }
    else if (j == 5) {
        QString f_isNeedHigherEducation = modelCompanies->data(index).toString();
        if (!(f_isNeedHigherEducation == "YES" ||
                f_isNeedHigherEducation == "NO"))
            modelCompanies->setData(index, boolToStr(arrCompanies[i].isNeedHigherEducation));
        else
            arrCompanies[i].isNeedHigherEducation = strToBool(f_isNeedHigherEducation);
    }
    else if (j == 6) {
        int f_minAge = modelCompanies->data(index).toInt();
        if (f_minAge < 0)
            modelCompanies->setData(index, arrCompanies[i].minAge);
        else
            arrCompanies[i].minAge = f_minAge;
    }
    else if (j == 7) {
        int f_maxAge = modelCompanies->data(index).toInt();
        if (f_maxAge < 0)
            modelCompanies->setData(index, arrCompanies[i].maxAge);
        else
            arrCompanies[i].minAge = f_maxAge;
    }

    fileRewrite(arrCompanies, fileCompanies, amountCompanies);
}

void MainWindow::slotChangedWorkers(QStandardItem* item) {
    QModelIndex index;
    index = modelWorkers->index(item->row(), item->column());

    int i = item->row();
    int j = item->column();

    if (j == 0)
        copy(arrWorkers[i].name, modelWorkers->data(index).toString());
    else if (j == 1) {
        int f_age = modelWorkers->data(index).toInt();
        if (f_age < 0)
            modelWorkers->setData(index, arrWorkers[i].age);
        else
            arrWorkers[i].age = f_age;
    }
    else if (j == 2)
        copy(arrWorkers[i].speciality, modelWorkers->data(index).toString());
    else if (j == 3) {
        QString f_hasHigherEducation = modelWorkers->data(index).toString();
        if (!(f_hasHigherEducation == "YES" ||
                f_hasHigherEducation == "NO"))
            modelWorkers->setData(index, boolToStr(arrWorkers[i].hasHigherEducation));
        else
            arrWorkers[i].hasHigherEducation = strToBool(f_hasHigherEducation);
    }
    else if (j == 4)
        copy(arrWorkers[i].post, modelWorkers->data(index).toString());
    else if (j == 5) {
        int f_minSalary = modelWorkers->data(index).toInt();
        if (f_minSalary < 0)
            modelWorkers->setData(index, arrWorkers[i].minSalary);
        else
            arrWorkers[i].minSalary = f_minSalary;
    }

    fileRewrite(arrWorkers, fileWorkers, amountWorkers);
}






void MainWindow::on_addCompanyButton_clicked() {

    setDefaultInputs();

    QDialog* Box = new QDialog;
    Box->setWindowTitle("Company");
    Box->setWindowFlags(Qt::Window | Qt::Tool);

    QGridLayout* lay = new QGridLayout;

    lay->addWidget(new QLabel("Company name: "), 0, 0);
    lay->addWidget(&line[0], 0, 1);

    lay->addWidget(new QLabel("Speciality: "), 1, 0);
    lay->addWidget(&line[1], 1, 1);

    lay->addWidget(new QLabel("Post: "), 2, 0);
    lay->addWidget(&line[2], 2, 1);

    lay->addWidget(new QLabel("Salary: "), 3, 0);
    spb[0].setRange(0, 999999999);
    lay->addWidget(&spb[0], 3, 1);

    lay->addWidget(new QLabel("Vocation: "), 4, 0);
    spb[1].setRange(0, 500);
    lay->addWidget(&spb[1], 4, 1);

    lay->addWidget(new QLabel("Heigher education: "), 5, 0);
    cmb->setCurrentIndex(0);
    lay->addWidget(cmb, 5, 1);

    lay->addWidget(new QLabel("Age from: "), 6, 0);
    spb[2].setRange(0, 200);
    lay->addWidget(&spb[2], 6, 1);

    lay->addWidget(new QLabel("Age to: "), 7, 0);
    spb[3].setRange(0, 200);
    lay->addWidget(&spb[3], 7, 1);

    QPushButton* Ok = new QPushButton("&Ok");
    QPushButton* Cancel = new QPushButton("&Cancel");
    lay->addWidget(Ok); lay->addWidget(Cancel);

    connect(Ok, SIGNAL(clicked()), this, SLOT(addCompanyToArr()));
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), Box, SLOT(reject()));

    Box->setLayout(lay);
    Box->show();
    Box->setFixedSize(Box->size());
    Box->activateWindow();
}

void MainWindow::on_addWorkerButton_clicked() {

    setDefaultInputs();

    QDialog* Box = new QDialog;
    Box->setWindowTitle("Worker");
    Box->setWindowFlags(Qt::Window | Qt::Tool);

    QGridLayout* lay = new QGridLayout;

    lay->addWidget(new QLabel("Worker name: "), 0, 0);
    lay->addWidget(&line[0], 0, 1);

    lay->addWidget(new QLabel("Age: "), 1, 0);
    spb[0].setRange(0, 200);
    lay->addWidget(&spb[0], 1, 1);

    lay->addWidget(new QLabel("Speciality: "), 2, 0);
    lay->addWidget(&line[1], 2, 1);

    lay->addWidget(new QLabel("Higher education: "), 3, 0);
    cmb->setCurrentIndex(0);
    lay->addWidget(cmb, 3, 1);

    lay->addWidget(new QLabel("Desired post: "), 4, 0);
    lay->addWidget(&line[2], 4, 1);

    lay->addWidget(new QLabel("Minimal salary: "), 5, 0);
    spb[1].setRange(0, 999999999);
    lay->addWidget(&spb[1], 5, 1);


    QPushButton* Ok = new QPushButton("&Ok");
    QPushButton* Cancel = new QPushButton("&Cancel");
    lay->addWidget(Ok); lay->addWidget(Cancel);

    connect(Ok, SIGNAL(clicked()), this, SLOT(addWorkerToArr()));
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), Box, SLOT(reject()));

    Box->setLayout(lay);
    Box->show();
    Box->setFixedSize(Box->size());
    Box->activateWindow();
}

void MainWindow::addCompanyToArr() {
    Company newCompany;

    copy(newCompany.name, line[0].text());
    copy(newCompany.speciality, line[1].text());
    copy(newCompany.post, line[2].text());
    newCompany.salary = spb[0].value();
    newCompany.vacationDays = spb[1].value();
    newCompany.isNeedHigherEducation = cmb->currentIndex();
    newCompany.minAge = spb[2].value();
    newCompany.maxAge = spb[3].value();

    setDefaultInputs();

    arrCompanies = (Company*)realloc(arrCompanies, ++amountCompanies * sizeof(Company));
    arrCompanies[amountCompanies - 1] = newCompany;

    fileRewrite(arrCompanies, fileCompanies, amountCompanies);
    printCompanies();
}

void MainWindow::addWorkerToArr() {
    Worker newWorker;

    copy(newWorker.name, line[0].text());
    newWorker.age = spb[0].value();
    copy(newWorker.speciality, line[1].text());
    newWorker.hasHigherEducation = cmb->currentIndex();
    copy(newWorker.post, line[2].text());
    newWorker.minSalary = spb[1].value();

    setDefaultInputs();

    arrWorkers = (Worker*)realloc(arrWorkers, ++amountWorkers * sizeof(Worker));
    arrWorkers[amountWorkers - 1] = newWorker;

    fileRewrite(arrWorkers, fileWorkers, amountWorkers);
    printWorkers();
}


void MainWindow::delCompanyFromArr() {
    int numDel = spbDel->value();

    for (int i = numDel - 1; i < amountCompanies - 1; i++)
        arrCompanies[i] = arrCompanies[i + 1];

    arrCompanies = (Company*)realloc(arrCompanies, --amountCompanies * sizeof(Company));
    fileRewrite(arrCompanies, fileCompanies, amountCompanies);
    printCompanies();
}

void MainWindow::delWorkerFromArr() {
    int numDel = spbDel->value();

    for (int i = numDel - 1; i < amountWorkers - 1; i++)
        arrWorkers[i] = arrWorkers[i + 1];

    arrWorkers = (Worker*)realloc(arrWorkers, --amountWorkers * sizeof(Worker));
    fileRewrite(arrWorkers, fileWorkers, amountWorkers);
    printWorkers();
}

void MainWindow::on_deleteCompanyButton_clicked() {

    if (amountCompanies == 0) return;

    QDialog* Box = new QDialog;
    Box->setWindowTitle("Delete company");
    Box->setWindowFlags(Qt::Window | Qt::Tool);

    QGridLayout* lay = new QGridLayout;
    lay->addWidget(new QLabel("Number: "), 0, 0);
    spbDel->setRange(1, modelCompanies->rowCount());
    spbDel->setValue(1);
    lay->addWidget(spbDel, 0, 1);

    QPushButton* Ok = new QPushButton("&Ок");
    QPushButton* Cancel = new QPushButton("&Cancel");
    lay->addWidget(Ok, 1, 0);
    lay->addWidget(Cancel, 1, 1);

    connect(Ok, SIGNAL(clicked()), this, SLOT(delCompanyFromArr()));
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), Box, SLOT(reject()));

    Box->setLayout(lay);
    Box->show();
    Box->setFixedSize(Box->size());
    Box->activateWindow();
}

void MainWindow::on_deleteWorkerButton_clicked() {

    if (amountWorkers == 0) return;

    QDialog* Box = new QDialog;
    Box->setWindowTitle("Delete worker");
    Box->setWindowFlags(Qt::Window | Qt::Tool);

    QGridLayout* lay = new QGridLayout;
    lay->addWidget(new QLabel("Number: "), 0, 0);
    spbDel->setRange(1, modelWorkers->rowCount());
    spbDel->setValue(1);
    lay->addWidget(spbDel, 0, 1);

    QPushButton* Ok = new QPushButton("&Ок");
    QPushButton* Cancel = new QPushButton("&Cancel");
    lay->addWidget(Ok, 1, 0);
    lay->addWidget(Cancel, 1, 1);

    connect(Ok, SIGNAL(clicked()), this, SLOT(delWorkerFromArr()));
    connect(Ok, SIGNAL(clicked()), Box, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), Box, SLOT(reject()));

    Box->setLayout(lay);
    Box->show();
    Box->setFixedSize(Box->size());
    Box->activateWindow();
}


void MainWindow::on_companiesFolderButton_clicked() {
    QString newStorage = QFileDialog::getOpenFileName(0, "Chose file with Companies", "", "companies.bin");
    if (newStorage == "")
        return;

    fileCompanies = newStorage;
    arrCompanies = fileParse(arrCompanies, fileCompanies, amountCompanies);
    printCompanies();
}


void MainWindow::on_workersFolderButton_clicked() {
    QString newStorage = QFileDialog::getOpenFileName(0, "Chose file with Workers", "", "workers.bin");
    if (newStorage == "")
        return;

    fileWorkers = newStorage;
    arrWorkers = fileParse(arrWorkers, fileWorkers, amountWorkers);
    printWorkers();
}



void MainWindow::on_vacanciesForWorkerButton_clicked() {

    emit on_resetColorButton_clicked();
    if (amountWorkers == 0 ||
            ui->viewWorkers->currentIndex().row() == -1 ||
            ui->viewWorkers->currentIndex().row() > amountWorkers - 1)
        return;

    QModelIndex index = ui->viewWorkers->currentIndex();
    int workerRow = index.row();

    for (int companyRow = 0; companyRow < modelCompanies->rowCount(); companyRow++) {
        if (isSuitable(arrCompanies[companyRow], arrWorkers[workerRow]))
            modelCompanies->item(companyRow, 0)->setBackground(QBrush(Qt::green));
    }
}



void MainWindow::on_vacanciesWithoutWorkersButton_clicked() {
    emit on_resetColorButton_clicked();
    if (amountCompanies == 0) return;

    for (int companyRow = 0; companyRow < modelCompanies->rowCount(); companyRow++) {

        int suitable = 0;
        for (int workerRow = 0; workerRow < modelWorkers->rowCount(); workerRow++) {
            if (isSuitable(arrCompanies[companyRow], arrWorkers[workerRow])) {
                suitable++;
                break;
            }
        }

        if (!suitable)
            modelCompanies->item(companyRow, 0)->setBackground(QBrush(Qt::red));
    }
}

void MainWindow::on_resetColorButton_clicked() {
    for (int companyRow = 0; companyRow < modelCompanies->rowCount(); companyRow++)
        modelCompanies->item(companyRow, 0)->setBackground(QBrush(Qt::white));
}



void MainWindow::setDefaultInputs() {
    delete[] line; line = new QLineEdit[3];
    delete[] spb; spb = new QSpinBox[4];
    delete spbDel; spbDel = new QSpinBox;
    delete cmb; cmb = new QComboBox;
    cmb->addItem("NO"); cmb->addItem("YES");

}

void MainWindow::on_helpButton_clicked() {
    QDialog* infoWindow = new QDialog(this);
    infoWindow->setWindowTitle("Info");
    infoWindow->setWindowFlags(Qt::Window | Qt::Tool);

    QVBoxLayout* lay = new QVBoxLayout;
    lay->addWidget(new QLabel("Работа с программой: \n"
                              "[Add Company] - добавить компанию \n"
                              "[Delete Company] - удалить компанию \n"
                              "[Chose Directory (C)] - выбрать путь \n"
                              "до файла с компаниями \n\n"
                              "[Add Worker] - добавить работника \n"
                              "[Delete Worker] - удалить работника \n"
                              "[Chose Directory (W)] - выбрать путь \n"
                              "до файла с работниками \n\n"
                              "[Vacancies Without Workers] - выделение \n"
                              "цветом вакансий без работников \n"
                              "[Vacancies For Worker] - вакансии для \n"
                              "работника, который выделен курсором \n"
                              "[Reset Fields Colors] - сбросить цвета полей \n\n"
                              "Все данные необходимо вводить корректно, наличие\n"
                              "или отстутсиве высшего образования — YES / NO, \n"
                              "Загружать в программму только файлы, созданные\n"
                              "этой же программой"
                              ));


    QPushButton* Ok = new QPushButton("&Ок");
    lay->addWidget(Ok);
    connect(Ok, SIGNAL(clicked()), infoWindow, SLOT(accept()));

    infoWindow->setLayout(lay);
    infoWindow->show();
    infoWindow->setFixedSize(infoWindow->size());
    infoWindow->activateWindow();
}


MainWindow::~MainWindow() {
    delete ui;
}



void copy(char* first, QString second) {
    int i = 0;
    for (; i < second.size(); i++)
        first[i] = second[i].toLatin1();
    first[i] = '\0';
}

bool compare(const char* first, const char* second) {
    if (first[0] == '\0' && second[0] == '\0')
        return false;

    int i = 0;
    while(first[i] != '\0' || second[i] != '\0') {
        if (first[i] != second[i])
            return false;
        i++;
    }
    return true;
}

bool strToBool(const QString str) {
    return str == "YES" ? 1 : 0;
}

QString boolToStr(const bool val) {
    return val ? "YES" : "NO";
}


bool isSuitable(const Company& company, const Worker& worker) {

    if (company.isNeedHigherEducation && !worker.hasHigherEducation)
        return false;


    return compare(company.speciality, worker.speciality) &&
            company.minAge <= worker.age && company.maxAge >= worker.age &&
            company.salary >= worker.minSalary &&
            compare(company.post, worker.post);
}



template<class T>
T* MainWindow::fileParse(T* arr, QString filename, int& N) {

    QFile file;
    file.setFileName(filename);

    if (file.open(QIODevice::ReadOnly)) {

        N = 0; free(arr); arr = nullptr;
        T Parse;


        char checkIdentify = 0;
        file.read((char*)&checkIdentify, 1);

        if (typeid(*arr).name()[1] == 'C' && checkIdentify != '@') {
            msgBadFile(fileCompanies);
        } else if (typeid(*arr).name()[1] == 'W' && checkIdentify != '#') {
            msgBadFile(fileWorkers);
        } else {
            file.seek(1);
            while (file.read((char*)&Parse, sizeof(T))) {
                arr = (T*)realloc(arr, ++N * sizeof(T));
                arr[N - 1] = Parse;
            }
        }

    } else {
        qDebug() << "BAD OPEN";
    }

    file.close();

    return arr;
}

template<class T>
void MainWindow::fileRewrite(T* arr, QString filename, int& N) {
    QFile file;
    file.setFileName(filename);

    if (file.open(QIODevice::Truncate | QIODevice::WriteOnly)) {

        T* obj = new T;
        file.write(&obj->identify, 1);

        for (int i = 0; i < N; i++)
            file.write((char*)&arr[i], sizeof(T));

        delete obj;
    } else {
        qDebug() << "BAD OPEN";
    }

    file.close();
}

void MainWindow::msgBadFile(QString badFile) {

    arrCompanies = nullptr; amountCompanies = 0;
    arrWorkers = nullptr; amountWorkers = 0;

    QDialog* msgBox = new QDialog;
    msgBox->setWindowTitle("Bad file");
    msgBox->setWindowFlags(Qt::Window | Qt::Tool);

    QVBoxLayout* lay = new QVBoxLayout(msgBox);
    lay->addWidget(new QLabel("Вы загрузили некорректный файл\n" + badFile));

    msgBox->show();
    msgBox->activateWindow();

    QTimer::singleShot(10, this, SLOT(slotHide()));
    QObject::connect(msgBox, SIGNAL(rejected()), this, SLOT(close()));

}
