﻿// Лабораторная 1, задача 5. Выполнена: Кончик Д. С.

/*
Определить расстояние, пройденное физическим телом за время t, если тело движется с
постоянным ускорением а и имеет в начальный момент времени скорость V0.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int t, a, V0;

    // Ввод данных
    cout << "t = "; cin >> t;
    cout << "a = "; cin >> a;
    cout << "V0 = "; cin >> V0;

    int S = V0 * t + a * pow(t, 2) / 2; // Расчет пройденного расстояния
    cout << "\nS = " << S;

    return 0;
}