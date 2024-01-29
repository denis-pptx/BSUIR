// Лабораторная 2, задача 8. Выполнена: Кончик Д. С.

/*
Вычислить значение y в зависимости от выбранной функции f(x), аргумент определяется из поставленного условия. 
Возможные значения функции f(x): 2x, x^3, x/3 (выбор осуществляется используя оператор switch).
Предусмотреть вывод сообщений, показывающих, при каком условии и с какой функцией производились вычисления y.

#14: y = b * cos[a * f(x)] + sin(x / 5) + a * e^x
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Rus");

    double N_double;
    int N = 0;
    double x, z, a, b, f_x, y;

    cout << "y = b * cos[a * f(x)] + sin(x / 5) + a * e^x \n";

    // Выбор номера функции 'f(x)'
    cout << "\nВозможные значения f(x): \n"
        << "1. 2 * x \n2. x^3 \n3. x / 3 \n"
        << "Выберите номер f(x) (1 - 3): ";
    cin >> N_double;

    // Ограничение некорректного ввода 'N'
    if (N_double - trunc(N_double) == 0)
        N = N_double;


    if (N == 1 || N == 2 || N == 3) {
        // Ввод 'z', 'a', 'b'
        cout << "\nВведите вещественное число z:"
            << "\nx = sqrt(z), z > 0"
            << "\nx = 3z + 1, z <= 0 \n";
        cout << "z = "; cin >> z;

        cout << "\nВведите a, b - вещестенные числа: \n";
        cout << "a = "; cin >> a;
        cout << "b = "; cin >> b;

        // Вычисление x
        if (z > 0) {
            cout << "\nx = sqrt(z)";
            x = sqrt(z);
        } else {
            cout << "\nx = 3 * z + 1";
            x = 3 * z + 1;
        }

        // Вычисление f(x)
        switch (N) {
        case 1:
            f_x = 2 * x;
            cout << "\nf(x) = 2 * x";
            break;
        case 2:
            f_x = pow(x, 3); 
            cout << "\nf(x) = x^3"; 
            break;
        case 3:
            f_x = x / 3;
            cout << "\nf(x) = x / 3";
            break;
        }

        // Вычисление и вывод 'y'
        y = b * cos(trunc(a * f_x)) + sin(x / 5) + a * exp(x);
        cout << "\ny = b * cos[a * f(x)] + sin(x / 5) + a * e^x \n";
        cout << "\ny = " << y;

    } else {
        cout << "Некорректный номер f(x)";
    }
    return 0;
}


