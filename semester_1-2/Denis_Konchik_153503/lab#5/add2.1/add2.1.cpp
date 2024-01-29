// Лабораторная 5, задача Дополнительно(#2.1). Выполнена: Кончик Д. С.

/*
Вычисления для больших чисел занимают ОГРОМНОЕ количество времени.
Быстрое решение смотреть в add2.2.cpp

Рекурсивная функция задана следующим образом:
f(0, 0) = 1
f(n, r) = sum[f(n - 1, r - i)] (from i = 0 to i = k - 1) when [(n > 0) and (0 ≤ r < n(k - 1) + 1)]
f(n, r) = 0 otherwise

Вычислить значение x = sum[f(n, i)] (from i = 0 to i = n(k - 1)) mod m, где m = 10^t

- Входные данные
Каждая строка содержит три целых числа: k (0 < k < 10^19), n (0 < n < 10^19) и t (0 < t < 10).
Последняя строка содержит три нуля и не обрабатывается.

- Выходные данные
Для каждого теста в отдельной строке вывести номер теста и значение x. Формат вывода приведен в примере.

- Входные данные
1234 1234 4
2323 99999999999 8
4 99999 9
888 888 8
0 0 0

- Выходные данные
Case #1: 736
Case #2: 39087387
Case #3: 494777344
Case #4: 91255296
*/

#include <iostream>
#include <stdlib.h>
using namespace std;

int F(int n, int r, int k) {
    int S = 0;
    if (n == 0 && r == 0) {
        return 1;
    }
    else if (n > 0 && r >= 0 && r < n * (k - 1) + 1) {
        for (int i = 0; i <= k - 1; i++)
            S += F(n - 1, r - i, k);
        return S;
    }
    else {
        return 0;
    }
}

int power(int x, int n) {
    if (n == 0)
        return 1;
    else
        return x * power(x, n - 1);
}

int main()
{
    setlocale(LC_ALL, "Rus");

    // Ввод данных
    cout << "Введите тройки чисел (k, n, t):\n";

    int k, n, t;
    int S = 0;

    int* ArrayX = 0; // Массив со всеми суммами
    int N = 0; // Число элементов в массиве ArrayX

    cin >> k >> n >> t;
    while (k > 0 && n > 0 && t > 0) {
        S = 0;
        for (int i = 0; i <= n * (k - 1); i++) {
            S += F(n, i, k);
        }


        int x = S % power(10, t);

        // Увеличиваем массив и добавляем в него элемент
        ArrayX = (int*)realloc(ArrayX, ++N * sizeof(int));
        ArrayX[N - 1] = x;

        cin >> k >> n >> t;
    }

    // Вывод
    cout << "\n";
    for (int i = 0; i < N; i++) {
        cout << "Case #" << i + 1 << ": " << ArrayX[i] << "\n";
    }

    free(ArrayX);

    return 0;
}