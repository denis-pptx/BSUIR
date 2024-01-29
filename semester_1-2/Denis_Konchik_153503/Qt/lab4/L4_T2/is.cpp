#include "ui_mainwindow.h"
#include "mainwindow.h"

// Является ли слово типом
bool MainWindow::isType(const string& word) {

    for (const auto& type : baseTypes)
        if (word == type)
            return true;

    if (isUserStruct(word))
        return true;

    if (isUserClass(word))
        return true;

    return false;
}

// Является ли слово пользовательской структурой
bool MainWindow::isUserStruct(const string& word) {
    for (auto type : userStructs)
        if (word == type)
            return true;

    return false;
}

// Является ли слово пользовательским классом
bool MainWindow::isUserClass(const string& word) {

    for (auto type : userClasses)
        if (word == type)
            return true;

    return false;
}


// Является ли слово символом
bool MainWindow::isSymb(const string &smb) {

    for (const auto& i : symbols)
        if (smb == i)
            return true;

    if (isArithm(smb))
        return true;

    return false;
}

// Является ли слово арифметическим оператором
bool MainWindow::isArithm(const string &word) {

    for (const auto& i : arithmetical)
        if (word == i)
            return true;

    return false;
}

// Является ли слово именем функции
bool MainWindow::isFuncName(const string& word) {

    for(const auto& i : funcProt)
        if (i.first.funcName == word)
            return true;

    return false;
}

// Является ли слово модификатором
bool MainWindow::isModifer(const string& word) {

    for (const auto& i : modifers)
        if (i == word)
            return true;

    return false;
}
