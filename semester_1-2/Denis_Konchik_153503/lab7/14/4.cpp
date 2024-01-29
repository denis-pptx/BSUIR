﻿// Лабораторная 7, задача 4. Выполнена: Кончик Д. С.

/*
Осуществить сложение и вычитание чисел в заданной системе счисления. 
В другую систему счисления не переводить. 
В системах счисления больших десятичной  использовать буквы по аналогии с шестнадцатеричной системой. 
Разработать функции для выполнения операции сложения и функции для выполнения операции вычитания.
Предусмотреть ввод положительных и отрицательных чисел.

[Вариант 13]
В девятнадцатеричной.
*/



#include <iostream>
#include <cmath>
using namespace std;


void Reverse(char* str);
void Input(char* str, const int& size);
int LetterToInt(char x);
int IntToLetter(int x);
int len(char* str);
void Same_Amount(char* num1, char* num2);
void Additional_Zero(char* num, int z);
void DelZero(char* num);
void SameView(char* num1, char* num2);
void DelSign(char* num, char sign);
void AddMinus(char* num);
void FuncSum(char* sum, char* num1, char* num2);
void FuncDifference(char* sum, char* num1, char* num2, bool& n1_bigger_n2);
void copy(char* temp, char* str);
void OperationFunc(char* sum, char* num1, char* num2);
void SameAfterPoint(char* num1, char* num2);
void DeletePoint(char* str, int pos);
void InsertPoint(char* str, int pos);

char* SUM(char* number1, char* number2, const int MAX) {
    char* sum = new char[MAX];


    char* temp1 = new char[MAX]; copy(temp1, number1);
    char* temp2 = new char[MAX]; copy(temp2, number2);

    // Удаляем плюсы у чисел
    DelSign(temp1, '+'); DelSign(temp2, '+');


    // Складываем
    OperationFunc(sum, temp1, temp2);
    DelZero(sum); // Удаление лишних нулей с начала

    return sum;
}

char* DIFF(char* number1, char* number2, const int MAX) {
    char* difference = new char[MAX];

    char* temp1 = new char[MAX]; copy(temp1, number1);
    char* temp2 = new char[MAX]; copy(temp2, number2);

    // Удаляем плюсы у чисел
    DelSign(temp1, '+'); DelSign(temp2, '+');


    // Разность - у второго числа поменять знак
    if (number2[0] != '-')
        AddMinus(temp2);
    else
        DelSign(temp2, '-');

    // Складываем первое число со вторым (знак изменен)
    OperationFunc(difference, temp1, temp2);
    DelZero(difference); // Удаление лишних нулей с начала

    return difference;
}


int main()
{
    // Объявление
    const int MAX = 100;
    char number1[MAX], number2[MAX];
    char* difference = new char[MAX];
    char* sum = new char[MAX];

    // Ввод
    cout << "Enter two numbers in 19 system: \n";
    cout << "First: "; Input(number1, MAX);
    cout << "Second: "; Input(number2, MAX);

    // Одинаково знаков после точки
    SameAfterPoint(number1, number2);
    int PointEnd = 0;
    int l = len(number1);
    for (int i = 0; i < l; i++) {
        if (number1[l - i - 1] == '.') {
            PointEnd = i;
            break;
        }
    }

    // Убрать точку
    DeletePoint(number1, len(number1) - PointEnd - 1);
    DeletePoint(number2, len(number2) - PointEnd - 1);

    sum = SUM(number1, number2, MAX);
    difference = DIFF(number1, number2, MAX);

    if (sum[0] == '.') {
        sum[0] = '0';
        sum[1] = '\0';
    }

    if (difference[0] == '.') {
        difference[0] = '0';
        difference[1] = '\0';
    }

    // Вставить точку
    InsertPoint(sum, len(sum) - PointEnd);
    InsertPoint(difference, len(difference) - PointEnd);

    cout << "\nSum: " << sum;
    cout << "\nDifference: " << difference << "\n";

    return 0;
}


void SameAfterPoint(char* num1, char* num2) {
    int P1 = 0;
    for (int i = 0; i < len(num1); i++) {
        if (num1[i] == '.') {
            P1 = i;
            break;
        }
    }

    int P2 = 0;
    for (int i = 0; i < len(num2); i++) {
        if (num2[i] == '.') {
            P2 = i;
            break;
        }
    }

    int add = 0; // На сколько удлинить
    if (P1 && !P2) {
        add = len(num1) - P1 - 1;
        int i = 0, l = len(num2);
        num2[l] = '.';
        for (i = l + 1; i < l + add + 1; i++)
            num2[i] = '0';
        num2[i] = '\0';
    }
    else if (!P1 && P2) {
        add = len(num2) - P2 - 1;
        int i = 0, l = len(num1);
        num1[l] = '.';
        for (i = l + 1; i < l + add + 1; i++)
            num1[i] = '0';
        num1[i] = '\0';
    }
    else if (P1 && P2) {
        P1 = len(num1) - P1;
        P2 = len(num2) - P2;

        char* change = P1 < P2 ? num1 : num2;
        add = fabs(P2 - P1);

        int l = len(change);
        int i = 0;
        for (i = l; i < l + add; i++)
            change[i] = '0';
        change[i] = '\0';
    }
}

void DeletePoint(char* str, int pos) {
    int i = 0;
    for (i = pos; i < len(str) - 1; i++)
        str[i] = str[i + 1];
    str[i] = '\0';
}

void InsertPoint(char* str, int pos) {
    int l = len(str), i = 0;
    for (i = l; i > pos; i--)
        str[i] = str[i - 1];
    str[pos] = '.';
    str[l + 1] = '\0';
}

void Input(char* str, const int& size) {
    cin >> str;

    if (len(str) > size) {
        cout << "INCORRECT INPUT";
        exit(0);
    }

    for (int i = 0; i < len(str); i++) {
        if (!(48 <= str[i] && str[i] <= 57
            || 65 <= str[i] && str[i] <= 73
            || 97 <= str[i] && str[i] <= 105
            || i == 0 && str[i] == '-'
            || i == 0 && str[i] == '+' || str[i] == '.')) {
            cout << "INCORRECT INPUT";
            exit(0);
        }
    }
}

void Reverse(char* str) {
    // Реверс строки

    for (int i = 0; i < len(str) / 2; i++) {
        char temp = str[i];
        str[i] = str[len(str) - 1 - i];
        str[len(str) - 1 - i] = temp;
    }
}

int LetterToInt(char x) {
    if (48 <= x && x <= 57)
        return x - '0';
    else if (65 <= x && x <= 73)
        return x - 55;
    else if (97 <= x && x <= 105)
        return x - 87;
}

int IntToLetter(int x) {
    if (0 <= x && x <= 9)
        return x + '0';
    else if (10 <= x && x <= 18)
        return x + 55;
    else {
        exit(0);
    }
}

int len(char* str) {
    // Длина строки

    int count = 0;
    while (str[count] != '\0')
        count++;

    return count;
}

void Same_Amount(char* num1, char* num2) {
    int NumRes = -1; // Номер числа, которое нужно изменить
    int MaxLen = 0;     // Размер, до которого нужно изменить

    char* change = 0;

    if (len(num1) > len(num2)) {
        change = num2;
        MaxLen = len(num1);
    }
    else if (len(num1) < len(num2)) {
        change = num1;
        MaxLen = len(num2);
    }


    if (MaxLen) {
        Reverse(change);

        for (int i = len(change); i < MaxLen; i++) {
            change[i] = '0';
        }
        change[MaxLen] = '\0';
        Reverse(change);
    }
}


void Additional_Zero(char* num, int z = 0) {
    Reverse(num);

    int NewLen = len(num) + z;

    for (int j = len(num); j < NewLen; j++)
        num[j] = '0';

    num[NewLen] = '\0';

    Reverse(num);
}


void DelZero(char* num) {
    if (num[0] == '0') {
        int Zero = 0; // число нулей с конца
        while (num[Zero] && num[Zero] == '0')
            Zero++;

        Reverse(num);
        num[len(num) - Zero] = '\0';
        Reverse(num);

        if (len(num) == 0) {
            num[0] = '0';
            num[1] = '\0';
        }

    }
    else if (num[0] == '-') {

        int Zero = 1; // число нулей с конца
        while (num[Zero] && num[Zero] == '0')
            Zero++;

        int OldLen = len(num);

        Reverse(num);

        num[OldLen - Zero + 1] = '\0';
        num[OldLen - Zero] = '-';

        Reverse(num);
    }

    if (num[0] == '.') {
        Reverse(num);
        int l = len(num);
        num[l] = '0';
        num[l + 1] = '\0';
        Reverse(num);
    }
}





void SameView(char* num1, char* num2) {
    // Одинаковое количество ячеек
    Same_Amount(num1, num2);

    // Дополнительные ячейки
    Additional_Zero(num1, 5);
    Additional_Zero(num2, 5);
}

void DelSign(char* num, char sign = '-') {
    Reverse(num);
    int l = len(num);
    if (num[l - 1] == sign)
        num[l - 1] = '\0';
    Reverse(num);
}

void AddMinus(char* num) {
    int l = len(num);
    if (!(l == 1 && num[0] == '0')) {

        Reverse(num);
        num[l] = '-';
        num[l + 1] = '\0';
        Reverse(num);

    }
}

void FuncSum(char* sum, char* num1, char* num2) {
    // Переворачиваем
    Reverse(num1); Reverse(num2);

    // Складываем
    int P = 0; // Перенос разряда
    int i = 0;
    for (i = 0; i < len(num1); i++) {
        // Сумма двух ячеек
        int CellSum = LetterToInt(num1[i]) + LetterToInt(num2[i]) + P;

        if (CellSum < 19) {
            sum[i] = IntToLetter(CellSum);
            P = 0;
        }
        else {
            sum[i] = IntToLetter(CellSum - 19);
            P = 1;
        }
    }
    sum[i] = '\0';
    Reverse(sum);
}

void FuncDifference(char* sum, char* num1, char* num2, bool& n1_bigger_n2) {
    // num1 > num2

    // Переворачиваем
    Reverse(num1); Reverse(num2);

    // Отнимаем
    int P = 0; // Забор разряда
    int i = 0;
    for (i = 0; i < len(num1); i++) {
        // Разность двух ячеек
        int CellDiff = LetterToInt(num1[i]) - LetterToInt(num2[i]);

        if (i == len(num1) - 1 && CellDiff < 0)
            n1_bigger_n2 = false;

        if (CellDiff >= 0) {
            sum[i] = IntToLetter(CellDiff);
        }
        else {
            sum[i] = IntToLetter(19 + LetterToInt(num1[i]) - LetterToInt(num2[i]));


            // Забираем единицу из ячейки, из которой можно забрать
            int j = i + 1;

            if (num1[j] != '\0') {
                while (num1[j] == '0')
                    num1[j++] = 'I';

                if (num1[j] == '\0')
                    n1_bigger_n2 = false;
                else
                    num1[j] = IntToLetter(LetterToInt(num1[j]) - 1); // забираем единицу у следующей ячейки
            }
            else {
                n1_bigger_n2 = false;
            }

        }
    }
    sum[i] = '\0';
    Reverse(sum);
}

void copy(char* temp, char* str) {
    int i = 0;
    for (i = 0; i < len(str); i++)
        temp[i] = str[i];
    temp[i] = '\0';
}

void OperationFunc(char* sum, char* num1, char* num2) {
    if ((num1[0] == '-' || num2[0] == '-') && !(num1[0] == '-' && num2[0] == '-')) {
        // Только одно из чисел содержит минус

        // Пусть num1 > num2

        bool n1_bigger_n2 = true;

        // Сохраняем исходные числа
        char temp1[100]; copy(temp1, num1);
        char temp2[100]; copy(temp2, num2);

        DelSign(num1); DelSign(num2);// Удаляем минусы у чисел
        Same_Amount(num1, num2); // Одинаковое количество ячеек
        FuncDifference(sum, num1, num2, n1_bigger_n2); // Отнимаем от большего меньшее

        if (temp1[0] == '-') {
            DelZero(sum);
            AddMinus(sum);
        }

        // иначе
        if (n1_bigger_n2 == false) {

            // Возвращаем исходные числа
            copy(num1, temp1); copy(num2, temp2);

            DelSign(num1); DelSign(num2); // Удаляем минусы у чисел
            Same_Amount(num1, num2); // Одинаковое количество ячеек

            FuncDifference(sum, num2, num1, n1_bigger_n2); // Отнимаем от большего меньшее

            if (temp2[0] == '-') {
                DelZero(sum);
                AddMinus(sum);
            }
        }
    }
    else if (!(num1[0] == '-' && num2[0] == '-')) {
        // Минусов нет

        SameView(num1, num2); // К одинаковому виду
        FuncSum(sum, num1, num2); // Складываем
    }
    else if (num1[0] == '-' && num2[0] == '-') {

        // Минус у обоих

        DelSign(num1); DelSign(num2); // Убираем минусы
        SameView(num1, num2); // К одинаковому виду
        FuncSum(sum, num1, num2); // Складываем
        AddMinus(sum); // Возвращаем минус
    }
}

