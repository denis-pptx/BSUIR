// Лабораторная 5, задача 3.3. Выполнена: Кончик Д. С.

/*
Дан двумерный динамический массив целых чисел. Значения элементов данного массива ввести с клавиатуры. 
Создать динамический массив из элементов, расположенных в четных столбцах данного массива и имеющих нечетное значение.
Вычислить среднее арифметическое элементов динамического массива.
Вывести результат на экран.
Использовать функции.
*/

#include <iostream>
#include "..\Input\input.h"
using namespace std;

void sort_columns(int** array, int* mass, int& N, int& M, int& sum, int& amount) {

    for (int j = 1; j < M; j += 2) {
        for (int i = 0; i < N; i++) {
            if (array[i][j] != 0 && array[i][j] % 2 != 0) {
                mass[amount++] = array[i][j];
                sum += array[i][j];
            }
        }
    }
}

void result(int& sum, int& amount, int* mass) {
    if (amount != 0) {
        cout << "\nНечетные элементы в четных столбцах: \n";
        for (int i = 0; i < amount; i++) {
            cout << mass[i] << " ";
        }
        cout << "\nСреднее арифметическое: " << (double)sum / amount << "\n";
    }
    else {
        cout << "\nВ четных столбцах нет нечетных элементов\n";
    }
}

int main()
{
 
    
    setlocale(LC_ALL, "Rus");

    // Ввод данных
    cout << "Задайте размер массива.\n";
    cout << "Строки: "; int N = input_natural();
    cout << "Столбцы: "; int M = input_natural();

    // Создание массива
    int** array = new int* [N];
    for (int i = 0; i < N; i++) {
        array[i] = new int[M];
    }

    // Ввод массива 
    cout << "\nВведите массив " << N << "x" << M << ": \n";
    array = input_arr2_int(array, N, M);

    int* mass = new int[N * (M / 2)]; // Массив для нечетных элементов в четных столбцах
    int sum = 0; // Их сумма
    int amount = 0; // Их количество

    sort_columns(array, mass, N, M, sum, amount); // Заполнение массива 'mass'

    result(sum, amount, mass); // Вывод результата

    for (int i = 0; i < N; i++) {
        delete[] array[i];
    } delete[] array;

    delete[] mass;

    return 0;
}

