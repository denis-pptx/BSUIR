// Лабораторная 2, задача 6. Выполнена: Кончик Д. С.

/*
Составить программу используя переключатель switch:
Z = ...
    = bc - a^2, если N = 2
    = bc, если N = 56
    = a^2 + c, если N = 7
    = a - bc, если N = 3
    = (a + b)^3, в остальных случаях

Переменные a, b, c и N ввести в клавиатуры:
a = -13.8; b = 8.9; c = 25
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Rus");
    double a, b, c, Y; 
    int N;

    // Ввод данных
    cout << "Введите вещественные числа (a, b, c), целое число (N): \n";
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "c = "; cin >> c;
    cout << "N = "; cin >> N;

    // Проверка условия задачи
    switch (N) {
    case 2:
        Y = b * c - a * a; break;
    case 56:
        Y = b * c; break;
    case 7:
        Y = a * a + c; break;
    case 3:
        Y = a - b * c; break;
    default:
        Y = pow(a + b, 3);
    }

    cout << "\nY = " << Y;
}

