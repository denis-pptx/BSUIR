// Лабораторная 1, задача 4. Выполнена: Кончик Д. С.

/*
Определить время падения камня на поверхность земли с высоты h.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double h;
    cout << "h = "; cin >> h; // Ввод данных

    double t = sqrt(2 * h / 9.81); // Вычисление времени падения
    cout << "t = " << t; 
    return 0;
}