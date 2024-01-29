#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = nullptr;
    view = nullptr;
    window = nullptr;
    lay = nullptr;

    // Настройка редактора кода
    ui->textEdit->hide();
    codeEdit = new CodeEditor(this);
    codeEdit->setGeometry(ui->textEdit->geometry());
    connect(codeEdit, SIGNAL(textChanged()), this, SLOT(textEditorTextChanged()));

    // Имя программы
    windowTitle = "Парсер";

    setFixedSize(size());

    // Путь к файлу
    fileName = "D:\\Doc\\Studies\\FAaP\\Denis_Konchik_153503\\Qt\\lab4\\build-L4_T2-Desktop_Qt_6_2_3_MinGW_64_bit-Debug\\code.txt";

    // Базовые типы данных
    baseTypesOrig = {"bool", "char", "signed char", "unsigned char", "wchar_t", "char16_t", "char32_t", "short",
            "short int", "signed short int", "signed short", "unsigned short", "unsigned short int",
            "int", "signed int", "unsigned int", "signed", "unsigned", "long", "long int", "signed long int",
            "signed long", "unsigned long", "unsigned long int", "long long", "long long int",
            "signed long long int", "signed long long", "unsigned long long", "unsigned long long int",
            "float", "double", "long double", "void", "auto"};

    // Модификаторы
    modifers = {"const", "volatile", "register", "mutable", "static", "extern"};

    // Арифметические операторы
    arithmetical = {"+", "-", "*", "/", "%"};

    // Символы
    symbols = {"~", "^", "|", "&", "(", ")", "{", "}", "[", "]", ",", ".", ";", ":", "=", "?", "\"", "!", "<", ">", "#"};


    FileRead();

    PrintText();

    SplitCode();

    setWindowTitle(windowTitle);


}

MainWindow::~MainWindow()
{
    delete ui;
}




// Распечатать содержимое
void MainWindow::PrintText() {



    string text = "";
    for (string str : code)
        text += str + "\n";

    codeEdit->blockSignals(true);

    codeEdit->setPlainText(QString(text.c_str()));

    codeEdit->blockSignals(false);
}


// Команды с клавитуры
void MainWindow::keyPressEvent(QKeyEvent *event) {

    if (event->modifiers() == Qt::ControlModifier &&
            event->key() == Qt::Key_S) {
        on_saveTextButton_clicked();
    }
    else if (event->modifiers() == Qt::ControlModifier &&
             event->key() == Qt::Key_R) {

        FileRead();
        PrintText();
        SplitCode();

    }
}

// Закрыть окошки
void MainWindow::resetWindows() {

    delete model;
    delete view;
    delete window;

    model = nullptr;
    view = nullptr;
    window = nullptr;

}
// Изменение текста
void MainWindow::on_textEdit_textChanged()
{
    setWindowTitle(windowTitle + "*");
}

void MainWindow::textEditorTextChanged() {
    setWindowTitle(windowTitle + "*");
}








