﻿// Лабораторная 2, задача 2. Выполнена: Кончик Д. С.

/*
Меньшее из двух значений переменных целого типа Х и Y заменить нулём, 
а в случае их равенства - заменить нулями оба; 
наибольшее из трёх различных значений переменных вещественного типа А, В и С уменьшите на K.
K вводится с клавиатуры.
*/

#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL,"Rus");

    // Первая задача. Ввод данных (#1)
    int X, Y;
    cout << "Введите два целых числа: X, Y\n";
    cout << "X = "; cin >> X;
    cout << "Y = "; cin >> Y;

    // Условиe первой задачи
    if (X == Y) {
        X = 0; 
        Y = 0;
    } else if (X < Y) {
        X = 0;
    } else {
        Y = 0;
    }

    cout << "X = " << X << ", Y = " << Y << "\n";


 
    // Вторая задача. Ввод данных (#2)
    double A, B, C, K;
    cout << "\nВведите три различных вещественных числа: ";
    cout << "\nA = "; cin >> A;
    cout << "B = "; cin >> B;
    cout << "C = "; cin >> C;
    cout << "K = "; cin >> K;

    // Условие второй задачи
    if (A > B && A > C) 
        A -= K;
    else if (B > A && B > C) 
        B -= K;
    else 
        C -= K;

    cout << "A = " << A << ", B = " << B << ", C = " << C;


    return 0;
}

