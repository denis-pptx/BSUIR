// Лабораторная 5, задача Дополнительно(#2.2). Выполнена: Кончик Д. С.

/*
Аналитическим методом было установлено, что решение задачи
эквивалентно выражению:

    x = k^n % m, m = 10^t  (*)
    x = (k % m)^n % m

Источник: https://site.ada.edu.az/~medv/acm/Docs%20e-olimp/Volume%2016/1514.htm
*/


#include <iostream>
#include "..\Input\input.h"
#define ll unsigned long long
using namespace std;

// m = 10^t
// x = (k % m)^n % m.

ll Foo(ll k, ll n, ll m)
{
    // Если степень нечетная, то разбиваем a^(n+1) = a * a^n, n - четное

    if (n == 0)
        return 1;
    else if (n % 2 == 1)
        return (k * Foo((k * k) % m, n / 2, m)) % m;
    else
        return Foo((k * k) % m, n / 2, m);

}


int main()
{
    setlocale(LC_ALL, "Rus");

    // Ввод данных
    cout << "Введите тройки чисел (k, n, t):\n";

    ll k, n, t;

    ll* ArrayX = 0; // Массив со всеми суммами
    int N = 0; // Число элементов в массиве ArrayX


    k = input_int_pairs_ll(); n = input_int_pairs_ll(); t = input_int_pairs_ll();
    while (k > 0 && n > 0 && t > 0) {
        ll m = 1;
        for (int i = 0; i < t; i++) {
            m *= 10;
        }
        ll x = Foo(k % m, n, m);

        // Увеличиваем массив и добавляем в него элемент
        ArrayX = (ll*)realloc(ArrayX, ++N * sizeof(ll));
        ArrayX[N - 1] = x;

        k = input_int_pairs_ll(); n = input_int_pairs_ll(); t = input_int_pairs_ll();
    }

    // Вывод
    cout << "\n";
    for (int i = 0; i < N; i++) {
        cout << "Case #" << i + 1 << ": " << ArrayX[i] << "\n";
    }

    free(ArrayX);

    return 0;
}

