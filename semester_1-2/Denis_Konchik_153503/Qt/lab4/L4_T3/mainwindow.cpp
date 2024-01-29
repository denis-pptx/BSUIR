#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Двудесятичные числа");
    setFixedSize(size());

    QPixmap pix(":/new/prefix1/tom.jpg");
    int w = ui->image->width();
    int h = ui->image->height();

    ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    unsigned int start_time =  clock(); // начальное время

    string number = count(ui->spinBox->value());

    unsigned int end_time = clock(); // конечное время

    ui->textBrowser->setText(number.c_str());

    qDebug() << end_time - start_time;

    unsigned int search_time = end_time - start_time; // искомое время

    QMessageBox::information(nullptr, "Info", QString::number(search_time));
}


// К-ый бит числа в его двоичном представлении
bool MainWindow::bit(string str, int k) {

    int bit = 0;
    int len = (int)str.size();

    for (int i = 0; i < k; i++) {

        bit = (str.back() - 48) % 2;
        str.back() -= bit;

        for (int j = (int)len - 1; j >= 0; --j) {

            if (j != len - 1 && (str[j] - 48) % 2)
                str[j + 1] += 5;

            str[j] = (str[j] - 48) / 2 + 48;
        }
    }

    return (bool)bit;
}

// Добавить к строке 10^k
string MainWindow::pow(string str, int k) {

  //  qDebug() << str.c_str();
    if (k == 0)
        return "1";

    string result = "1";


    for (int i = 0; i < k - (int)str.size(); i++)
        result += "0";

    for (int i = 0; i < (int)str.size(); i++)
        result += str[i];



    return result;
}


string MainWindow::count(int N) {

    vector<string> A(1000, "0"); // k-я цифра в двоичном представлении 0
    vector<string> B(1000, "0"); // двудесятичные числа

    int i_A = 1;
    int i_B = 0;
    int k = 1;
    int bindemical = 1; // Всего чисел посчитано


    while (bindemical <= N) {

        int i_tmp = 0;
        i_B = 0;

        for (int i = 0; i < i_A; i++)
            if (bit(A[i], k) == 0)
                A[i_tmp++] = A[i];

        i_A = i_tmp;

        for (int i = 0; i < i_A; i++)
            B[i] = pow(A[i], k - 1);

        i_B = i_A;

        for (int i = 0; i < i_B; i++)
            A[i_A++] = B[i];

        bindemical += i_B;
        k++;
    }


    return B[N + i_B - bindemical];
}

