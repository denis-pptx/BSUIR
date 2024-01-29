// Лабораторная 3, задача 1. Выполнена: Кончик Д. С.

/*
(использовать while)
Вычислить N = Σ(a_i - b_i)^2 (i ∈ N, 1 <= i <= 30), где a и b определены по формуле:

    a_i = i, если i нечетное
          i/2, если i четное

    b_i = i^2, если i нечетное
          i^3, если i четное
*/

#include <iostream>
using namespace std;

int main()
{
    int N = 0, i = 1, a, b;

    while (i <= 30) {

        // Вычисление текущих 'a' и 'b'
        if (i % 2 == 0) {
            a = i / 2;
            b = i * i * i;
        } else {
            a = i;
            b = i * i;
        }

        // Сумма
        N += (a - b) * (a - b);

        i++;
    }

    cout << "N = "; cout << N;

    return 0;
}

