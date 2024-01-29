// Лабораторная 2, задача 15. Выполнена: Кончик Д. С.

/*
Для дробного числа К напечатать фразу "мы нашли К грибов в лесу", согласовав окончание слова "гриб" с числом К.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Rus");
    int K;
    double K_double;

    // Ввод данных
    cout << "Введите вещественное число грибов K:";
    cout << "\nK = "; cin >> K_double;

    if (K_double == 0) {
        cout << "Мы не нашли ни одного гриба в лесу";
    } else if (K_double - trunc(K_double) == 0) {
        K = fabs(K_double);

        if (K_double > 0)
            cout << "Мы нашли " << K;
        else 
            cout << "Мы потеряли " << K;

        // Решение задачи
        if (K % 100 == 11 || K % 100 == 12 || K % 100 == 13 || K % 100 == 14)
            cout << " грибов";
        else if ((K % 10 <= 9 && K % 10 >= 5) || (K % 10 == 0))
            cout << " грибов";
        else if (K % 10 >= 2 && K % 10 <= 4)
            cout << " гриба";
        else if (K % 10 == 1)
            cout << " гриб";

        cout << " в лесу";

    } else {
        // Грибов дробное число
        if (K_double > 0)
            cout << "Мы нашли " << K_double << " гриба в лесу";
        else 
            cout << "Мы потеряли " << fabs(K_double) << " гриба в лесу";
    }

    return 0;
}


