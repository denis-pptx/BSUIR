// Лабораторная 2, задача 16. Выполнена: Кончик Д. С.

/*
Введены два числа. Выведите их НОД и НОК.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Rus");
    int A, B, NOD = 1, NOK = 0;
    double A_double, B_double;
    

    // Ввод данных
    cout << "Введите два натуральных числа:";
    cout << "\nA = "; cin >> A_double;
    cout << "B = "; cin >> B_double;

    // Проверка корректности ввода (программа будет работать только с натуральными числами)
    if (A_double >= 1 && B_double >= 1 && 
        A_double - trunc(A_double) == 0 && 
        B_double - trunc(B_double) == 0) {

        A = A_double;
        B = B_double;

        // Вычисление НОД (деление обоих чисел на переменную без остатка)
        int min = A < B ? A : B;
        for (int i = 1; i <= min; i++) {
            if (A % i == 0 && B % i == 0)
                NOD = i;
        }

        // Вычисление НОК (НОК * НОД = a * b)
        NOK = A * B / NOD;

        cout << "\nНОД = " << NOD
            << "\nНОК = " << NOK;

    } else {
        cout << "Некорректный ввод";
    }
    return 0;
}


