// Лабораторная 5, задача Дополнительно(#3). Выполнена: Кончик Д. С.

/*
Пусть f(n) - наибольший нечетный делитель натурального числа n. 
По заданному натуральному n необходимо вычислить значение суммы f(1) + f(2) + ... + f(n).

- Входные данные
Каждая строка содержит одно натуральное число n (n ≤ 10^9).
Последняя строка нуль и не обрабатывается.


- Выходные данные
Для каждого значения n в отдельной строке вывести значение суммы f(1) + f(2) + ... + f(n).

- Входные данные #1
7
1
777
0

- Выходные данные #1
21
1
201537

*/

#include <iostream>
#include <stdlib.h>
#include "..\Input\input.h"
using namespace std;

int Foo(int n) {
    int divider = 1;
    for (int i = n; i > 0; i--) {
        if (n % i == 0 && i % 2 == 1) {
            divider = i;
            break;
        }
    }

    return divider;
}

int main()
{
    setlocale(LC_ALL, "Rus");

    // Ввод данных
    cout << "Введите числа n:\n";

    int n, S = 0;
    int* ArrayX = 0; // Массив со всеми суммами
    int N = 0; // Число элементов в массиве ArrayX

    n = input_natural_z();
    while (n > 0) {
        S = 0;
        for (int i = 1; i <= n; i++) {
            S += Foo(i);
        }


        // Увеличиваем массив и добавляем в него элемент
        ArrayX = (int*)realloc(ArrayX, ++N * sizeof(int));
        ArrayX[N - 1] = S;

        n = input_natural_z();
    }

    // Вывод
    cout << "\n";
    for (int i = 0; i < N; i++) {
        cout << ArrayX[i] << "\n";
    }

    free(ArrayX);

    return 0;
}