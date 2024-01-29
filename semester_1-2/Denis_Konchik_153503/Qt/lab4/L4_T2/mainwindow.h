#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <stack>
#include <set>
#include <QStandardItemModel>
#include <QTableView>
#include <QModelIndex>
#include <QHeaderView>
#include <QDialog>
#include <QLayout>
#include <QLabel>

#include "codeeditor.h"
#include "structs.h"

#include "../string/string.h"
#include "../vector/vector.h"

#include "my_pair.h"
//#include "my_string.h"
//#include "my_vector.h"


using namespace my_string;
using namespace my_vector;
using namespace my_pair;

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
    void textEditorTextChanged();

    void on_choseFileButton_clicked();

    void on_saveTextButton_clicked();



    void on_funcProt_Button_clicked();

    void on_classStructArray_Button_clicked();

    void on_textEdit_textChanged();

    void on_localVariable_Button_clicked();

    void on_branching_Button_clicked();

    void on_variables_Button_clicked();

    void on_variablesEdit_Button_clicked();

    void on_mistakes_Button_clicked();

    void on_helpButton_clicked();

private:
    Ui::MainWindow *ui;

    // Текстовый редактор
    CodeEditor* codeEdit;

    // Добавить к типам типы с модификаторами
    void createTypesMod();

    // Объединить несколько слов в одно
    // long long, const unsigned и тд
    void uniteWords();

    // Закрыть все окошки
    void resetWindows();

    // Считать файл
    void FileRead();

    // Перезаписать файл
    void FileRewrite();

    // Распечатать код
    void PrintText();

    // Разделить код на слова
    void SplitCode();

    // Убрать строки с комментариями
    void SkipComments();

    // Найти пользовательские типы данных
    void SearchUserTypes();

    // Поиск функций и их прототипов
    void SearchFunc();

    // Поиск переменных и их начальных значений
    void SearchVariables();

    // Поиск изменений переменных
    void SearchVarEdit();

    // Поиск ошибок
    void SearchMistakes();

    // Получить число классов
    size_t CountClasses();

    // Получить число структур
    size_t CountStructs();

    // Получить число массивов
    size_t CountArrays();

    // Локальные переменные
    void CountLocalVariable();

    // Ветвления
    void CountBranches();

    // Пропустить кавычки
    void SkipQuotation(size_t& i);

    // Является ли слово типом
    bool isType(const string& word);

    // Является ли слово пользовательской структурой
    bool isUserStruct(const string& word);

    // Является ли слово пользовательским классом
    bool isUserClass(const string& word);

    // Является ли слово символом
    bool isSymb(const string& word);

    // Является ли слово арифметическим оператором
    bool isArithm(const string& word);

    // Имя ли это функции
    bool isFuncName(const string& word);

    // Модификатор ли это
    bool isModifer(const string& word);

    // Имя файла
    QString fileName;

    // Исходный код
    vector<string> code;

    // Разделенный на слова код
    vector<pair<string, Coords> > splitedCode;


    // Базовые типы данных
    vector<string> baseTypes;

    vector<string> baseTypesOrig;

    // Модификаторы
    vector<string> modifers;

    // Арифметические операторы
    vector<string> arithmetical;

    // Символы
    vector<string> symbols;

    // Пользовательские структуры
    vector<string> userStructs;

    // Пользовательские классы
    vector<string> userClasses;

    // Прототипы функций
    vector<pair<Prototype, Coords> > funcProt;

    // Перегруженные функции
    // имя функции — вектор перегрузок
    vector<pair<string, vector<string> > > overloaded;

    // Координаты перегруженных функций
    vector<vector<Coords> > coords;

    // Локальные переменные и их координаты
    vector<Coords> coordsVar;

    // Координаты изменений всех переменных
    vector<Coords> coordsVarEdit;

    // Ветвления "глубина — координата"
    vector<pair<size_t, Coords> > branching;

    // Переменные "тип - строка с объявлением"
    vector<pair<string, string> > variables;


    // Переменные "тип - все строки с объявлением этого типа"
    vector<pair<string, vector<string> > > typesDeclare;

    // Ошибки "ошибка - строка"
    vector<pair<string, size_t> > mistakes;

    // Название программы
    QString windowTitle;


    // Для вывода
    QStandardItemModel* model;
    QTableView* view;
    QDialog* window;
    QGridLayout* lay;

    size_t wm = 1920;
    size_t hm = 1080;

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};


#endif // MAINWINDOW_H
