// Лабораторная 2, задача 5. Выполнена: Кончик Д. С.

/*
Составить программу используя условный оператор if:
Z = ...
    = a + b / c, если c >= d и a < d
    = a - b / c, если c < d и a >= d
    = 0, в остальных случаях

Переменные a, b, c и d ввести в клавиатуры: 
a = 3.8; b = -25; c = 5
*/

#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Rus");
    double a, b, c, d, Z;
    
    // Ввод данных
    cout << "Введите вещественные числа: a, b, c, d ";
    cout << "\na = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "c = "; cin >> c;
    cout << "d = "; cin >> d;

    // Проверка знаменятеля дроби на 0
    if (c != 0) { 
        // Проверка условий задачи
        if (c >= d && a < d) 
            Z = a + b / c;
        else if (c < d && a >= d) 
            Z = a - b / c;
        else 
            Z = 0;

        cout << "\nZ = " << Z;
    }
    else {
        cout << "\nError";
    }


    return 0;
}


