// Лабораторная 1, задача 2. Выполнена: Кончик Д. С.

/*
Разработка программы для реализации линейного вычислительного процесса.

Составить программу на языке С++ для расчета соотношения. Исходные данные ввести с клавиатуры.
Вариант 4. 
    T = cos(x) + A^2 / (K - C * D) - B,
    A = x - y, B = sqrt(z)
*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x, y, z, K, C, D;

    // Ввод данных
    cout << "x = "; cin >> x;
    cout << "y = "; cin >> y;
    cout << "z = "; cin >> z;
    cout << "K = "; cin >> K;
    cout << "C = "; cin >> C;
    cout << "D = "; cin >> D;

    if (K - C * D != 0) // Проверка знаменателя дроби на 0
        cout << "\nT = " << cos(x) + pow(x - y, 2) / (K - C * D) - sqrt(z); // Вычисление выражения
    else
        cout << "error";

    return 0;
}

