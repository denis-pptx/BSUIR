// Лабораторная 5, задача 2. Выполнена: Кончик Д. С.

/*
[Варианрт 14]
Для заданного одномерного массива Y из N элементов проверить, 
что для всех элементов массива выполняется условие  Yi < 0. 
Рекурсивную функцию применять каждый раз отдельно для каждой из половин массива. 
Рекурсивные вызовы заканчивать, когда останется только один элемент.
*/

#include <iostream>
#include "..\Input\input.h"
using namespace std;

bool NegativeCheck(double* array, int first, int last, bool negative) {

    if (first > last) { // first == last — последний элемент
        return negative;
    }
    else if (array[first] >= 0) {
        negative = false;
        return negative;
    }
    else {
        NegativeCheck(array, first + 1, last, negative);
    }

}

bool Half(double* array, int N) {
    
    if (N == 1 && array[0] >= 0)
        return false;
    if (N == 1 && array[0] < 0)
        return true;

    int mid = 0; // Индекс середины
    if (N % 2 == 0)
        mid = N / 2 - 1;
    else
        mid = N / 2;

    bool negative = true; // Все элементы отрицательные
    negative = NegativeCheck(array, 0, mid, negative);
    negative = NegativeCheck(array, mid + 1, N - 1, negative);

    return negative;
}

int main()
{


    setlocale(LC_ALL, "Rus");

    // Ввод данных
    cout << "Число элементов массива: ";
    int N = input_natural();

    // Создание и ввод массива
    double* array = new double [N];
    cout << "\nВведите массив: \n";
    array = input_arr1_double(array, N);

 
    // Все элементы отрицательные?
    bool negative = Half(array, N);


    if (negative) 
        cout << "\nУсловие Y(i) < 0 выполняется\n";
    else 
        cout << "\nУсловие Y(i) < 0 не выполняется\n";
    
    delete[] array;

    return 0;
}

