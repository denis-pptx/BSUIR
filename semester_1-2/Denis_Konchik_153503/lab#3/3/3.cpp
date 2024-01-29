// Лабораторная 3, задача 3. Выполнена: Кончик Д. С.

/*
(использовать for)
Составить программу вычисления значений функции y = sin(x) - cos(x) на отрезке [A, B]
в точках x_i = A + i * H, где H = (B - A) / M, M = 20, A = 0, B = π / 2
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    double x, B = acos(-1) / 2, y = 0;
    double H = B / 20;

    // Вычисление значений функции
    cout << fixed << setprecision(6);
    x = 0;
    for (int i = 1; x <= B; i++) {
   
        y = sin(x) - cos(x); // Значение функции
        cout << "x" << i << " = " << x << ", y" << i << " = " << y << "\n";

        x = i * H;
    }

    return 0;
}

