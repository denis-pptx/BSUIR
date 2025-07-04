﻿// Лабораторная 4, задача 15. Выполнена: Кончик Д. С.

/*
Таблица заполняется по следующему алгоритму: В таблицу вносятся все натуральные числа по порядку. 
1 становится в левую верхнюю ячейку, затем выбирается самая левая незаполненная ячейка в самой первой строке таблицы и заполняется.  
Затем, пока у последней заполненной ячейки сосед слева существует и заполнен, опускаемся вниз и заполняем очередную ячейку. 
Когда же не окажется соседа слева, то начинается заполнение клеток справа налево. 
После того как будет заполнена ячейка в первом столбце, После этого алгоритм заполнения повторятся.
Необходимо вывести строку и столбец в котором будет находится число, введенное с клавиатуры.
*/

#include <iostream>
#include <cmath>
using namespace std;

int input_N();

int main()
{
    setlocale(LC_ALL, "Rus");

    // Ввод данных
    cout << "Введите натуральное число: "; 
    int x = input_N();
    int x_copy = x;

    // Поиск порядка матрицы, которая получится 
    // при заполнении таблицы до данного N
    int N = sqrt(x_copy);
    while (sqrt(x_copy) != trunc(sqrt(x_copy))) {
        N = sqrt(++x_copy);
    }

    // Определение строки и столбца введенного числа
    int line = 0, column = 0;

    int start = (N - 1) * (N - 1) + 1;
    int end = N * N;
    int middle = (start + end) / 2;

    if (x == middle) {
        line = N;
        column = N;
    } else if (x < middle) {
        column = N;
        line = 1;
        for (int i = start; i < middle; i++) {
            if (i == x) break;
            line++;
        }
    } else {
        line = N;
        column = N - 1;
        for (int i = middle + 1; i <= end; i++) {
            if (i == x) break;
            column--;
        }
    }

    // Вывод ответа
    cout << "Строка: " << line << "\nСтолбец: " << column;

    return 0;
}

/*
Алгоритм решения задачи:

Заполним таблицу до 16:
    1   2   5   10
    4   3   6   11
    9   8   7   12
    16  15  14  13

Например, пользователь вводит число x = 13. Программа определяет порядок матрицы, необходимой
для заполнения такой таблицы (в данном случае N = 4). 

Далее переменные, которые получатся для данного случая (x = 13):
    start = (N - 1) * (N - 1) + 1
    end = N * N
    middle = (start + end) / 2
start = 10, end = 16, middle = 13

Если middle = 13, то номера строки и столбца равны N = 4
Если x < middle, то 10 <= x <= 12. Номер столбца числа 'x' равен N = 4
Если x > middle, то 13 <= x <= 16. Номер строки числа 'x' равен N = 4

Далее через цикл for определяется номер столбца / строки числа 'x'

*/


int input_N() {
    int x;

    // Пока не будет введено корректное значение
    while (true) {
        cin >> x;

        // Пропуск пробелов после элемента
        while (cin.peek() == ' ')
            cin.ignore(1, ' ');

        // Проверка предыдущего извлечения данных из буфера
        // Извлечение неудачное / удачное, но остались неизвлеченные символы / число отрицательное
        if (cin.fail() || cin.peek() != '\n' || x <= 0) {
            cin.clear(); // Возвращение в обычный режим работы
            cin.ignore(10000, '\n'); // Игнор 'n' символов до Enter
            cout << "Повторите ввод: ";
        }
        else {
            return x;
        }
    }
}