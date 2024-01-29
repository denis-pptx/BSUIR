// Лабораторная 5, задача Дополнительно(#1). Выполнена: Кончик Д. С.

/*
Определим следующую функцию F(n): 
        n % 10,      if (n % 10 > 0)
F(n) =  0,           if (n = 0)
        F(n / 10),   otherwise

Определим функцию S (p, q) следующим образом:
    S(p,q) = sum(F(i)), p <= i <= q

Входные данные
Состоит из нескольких тестов. Каждая строка содержит два неотрицательных целых числа p и q (p ≤ q), 
разделенных пробелом. p и q являются 32 битовыми знаковыми целыми. 
Последняя строка содержит два отрицательных целых числа и не обрабатывается.

Выходные данные
Для каждой пары p и q в отдельной строке вывести значение S (p, q).
Входные данные #1
1 10
10 20
30 40
-1 -1
Выходные данные #1
46
48
52
*/

#include <iostream>
#include <stdlib.h>
#include "..\Input\input.h"
using namespace std;

int F(int n) {
    if (n % 10 > 0)
        return n % 10;
    else if (n == 0)
        return 0;
    else 
        return F(n / 10);
}

int main()
{

    setlocale(LC_ALL, "Rus");

    // Ввод данных
    cout << "Введите пары чисел (p, q):\n";

    int p, q;
    int S = 0; // Сумма F(i)

    int* ArrayS = 0; // Массив со всеми суммами
    int N = 0; // Число элементов в массиве ArrayS

    p = input_int_pairs();
    q = input_int_pairs();
    while (p >= 0 && q >= 0 && p <= q) {
        S = 0;
        for (int i = p; i <= q; i++) 
            S += F(i);

        // Увеличиваем массив и добавляем в него элемент
        ArrayS = (int*)realloc(ArrayS, ++N * sizeof(int));
        ArrayS[N - 1] = S;

        p = input_int_pairs();
        q = input_int_pairs();
    }
 
    // Вывод
    cout << "\n";
    for (int i = 0; i < N; i++) {
        cout << ArrayS[i] << "\n";
    }

    free(ArrayS);

    return 0;
}