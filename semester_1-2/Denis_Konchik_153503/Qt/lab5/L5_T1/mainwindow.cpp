#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowTitle("Флаги");

    empty = QPixmap(":/empty.jpg");

    countries = {"Belarus", "China", "Germany", "Italy", "Poland", "Russia",
                 "Spain", "Turkey", "UK", "Ukraine", "USA", "USSR", "Jamaica"};

    for (const auto& word : countries)
        ui->countries->addItem(word);


    setEmpty();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentPicture() {
    ui->image->setPixmap(flags.curr().first.scaled(ui->image->width(), ui->image->height()/*, Qt::KeepAspectRatio*/));
    ui->countryName->setText(flags.curr().second);
}

void MainWindow::pushNext(const QString& name) {

    QString pictureName = ":/" + name + ".jpg";

    flags.push_next(qMakePair(pictureName, name));
}

void MainWindow::pushPrev(const QString& name) {

    QString pictureName = ":/" + name + ".jpg";

    flags.push_prev(qMakePair(pictureName, name));
}

void MainWindow::setEmpty() {

    ui->image->setPixmap(empty.scaled(ui->image->width(), ui->image->height()));
    ui->amount->setText(QString::number(flags.size()));
    ui->countryName->setText("none");
}

void MainWindow::on_push_next_Button_clicked()
{
    int index = ui->countries->currentIndex();

    if (index == -1)
        return;


    pushNext(countries[index]);
    ui->amount->setText(QString::number(flags.size()));

    if (flags.size() == 1)
        setCurrentPicture();
}


void MainWindow::on_push_prev_Button_clicked()
{
    int index = ui->countries->currentIndex();

    if (index == -1)
        return;

    pushPrev(countries[index]);
    ui->amount->setText(QString::number(flags.size()));

    if (flags.size() == 1)
        setCurrentPicture();
}





void MainWindow::on_go_next_Button_clicked()
{
    if (flags.empty())
        return;

    flags.go_next();
    setCurrentPicture();
}


void MainWindow::on_go_prev_Button_clicked()
{
    if (flags.empty())
        return;

    flags.go_prev();
    setCurrentPicture();
}


void MainWindow::on_pop_Button_clicked()
{


    flags.pop();

    if (flags.empty()) {
        setEmpty();
        return;
    }

    setCurrentPicture();
    ui->amount->setText(QString::number(flags.size()));
}


void MainWindow::on_pushButton_clicked()
{
    flags.clear();
    setEmpty();

}

