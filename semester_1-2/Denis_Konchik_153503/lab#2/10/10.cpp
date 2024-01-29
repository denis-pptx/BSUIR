// Лабораторная 2, задача 10. Выполнена: Кончик Д. С.

/*
Из величин, определяемых выражениями a = sin(x), b = cos(x), c = ln|x| при заданном х,
определить и вывести на экран дисплея минимальное значение.
Библиотеку <cmath> использовать запрещено.
*/

#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Rus");
    double PI = 3.1415926535;

    // Ввод данных
    cout << "a = sin(x), b = cos(x), c = ln|x| \nВведите 'x' (действительное число): ";
    double x; cin >> x;

    // Приведение угла в интервал [-PI; +PI]
    double x_period = x;
    while (x_period > PI || x_period < -PI)
        x_period += x_period > PI ? -2 * PI : 2 * PI;

    // Вычисление a = sin(x) через ряд Тейлора
    double a_sin_x = 0, power = x_period, fact = 1;
    int k = 1;

    for (int i = 1; i <= 30; i += 2) {

        fact = 1;
        for (int j = 1; j <= i; j++) {
            fact *= j;
        }

        a_sin_x += k * power / fact;
        power *= x_period * x_period;
        k = -k;
    }

    // Вычисление b = cos(x) через ряд Тейлора
    double b_cos_x = 0;
    power = x_period * x_period;
    fact = 1;
    k = -1;

    for (int i = 2; i <= 30; i += 2) {

        fact = 1;
        for (int j = 1; j <= i; j++) {
            fact *= j;
        }

        b_cos_x += k * power / fact;
        power *= x_period * x_period;
        k = -k;
    } b_cos_x += 1;

    // Расчет c = ln|x| (x != 0), вывод решения задачи
    double min = a_sin_x;
    if (x != 0) {

        // Вычисление c = ln|x| через ряд Тейлора
        x = x > 0 ? x : -x;
        double t = (x - 1) / (x + 1);
        power = t;
        double c_ln_x = 0;

        for (int i = 1; i <= 100; i += 2) {
            c_ln_x += power / i;
            power *= t * t;
        } c_ln_x *= 2;

        // Вывод значений функций
        cout << "\na = sin(x) = " << a_sin_x
            << "\nb = cos(x) = " << b_cos_x << " "
            << "\nc = ln|x| = " << c_ln_x << " ";

        // Вычисление минимального значения
        min = b_cos_x < min ? b_cos_x : min;
        min = c_ln_x < min ? c_ln_x : min;

    } else {

        // Вывод значений функций
        cout << "\na = sin(x) = " << a_sin_x
            << "\nb = cos(x) = " << b_cos_x;

        // Вычисление минимального значения
        min = a_sin_x < b_cos_x ? a_sin_x : b_cos_x;
    }
    cout << "\n\nMin: " << min << "\n";

    return 0;
}


