// Лабораторная 6, задача 1. Выполнена: Кончик Д. С.

/*
Рассматривать строки как одномерный массив символов.
При выполнении задания предусмотреть возможность ввода текста с клавиатуры. При работе с текстом
использовать строки длиной не более 80-ти символов. Исходный текст и полученный результат вывести на экран.

[Вариант 14]
Дана строка, состоящая из слов, разделенных пробелами. Вывести на экран порядковый номер слова
минимальной длины и количество символов в этом слове.
*/

#include <iostream>
#include "stdlib.h"
using namespace std;

void min(char*, int&, int&);

int main()
{
    // Ввод данных
    cout << "Input string. Words are separated with spaces.\n";
    char str[80]; cin.getline(str, 80);

    int MinNum = 0, MinLen = 0;

    min(str, MinNum, MinLen);

    cout << "Minimum word number: " << MinNum <<
        "\nLength: " << MinLen << "\n";

    return 0;
}

void min(char* str, int& MinNum, int& MinLen) {

    if (strlen(str) == 0) {
        MinNum = 0;
        MinLen = 0;
        return;
    }

    // Убираем пробелы в конце строки
    int len = strlen(str);
    while (str[len - 1] == ' ')
        str[--len] = '\0';

    // Длина первого слова
    int i = 0;
    while (str[i] != ' ' && str[i] != '\0')
        i++;

    MinNum = 1; // Номер слова минимальной длины
    MinLen = i; // Длина слова минимальной длины
    int backup = 0, Number = 1, length = 0;


    backup = ++i; // На каком символе остановились
    while (i <= strlen(str)) {

        // Двигаемся до пробела
        while (str[i] != ' ' && str[i] != '\0')
            i++;


        Number++; // Номер текущего слова
        length = i - backup; // Длина текущего слова

        if (length < MinLen) {
            MinLen = length;
            MinNum = Number;
        }

        backup = ++i;
    }
}