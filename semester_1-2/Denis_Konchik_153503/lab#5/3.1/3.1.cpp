// Лабораторная 5, задача 3.1. Выполнена: Кончик Д. С.

/*
Дан двумерный динамический массив целых чисел А размерностью n x k .
Размерность массива (n = 5,  k = 6) ввести с клавиатуры. Значения элементов массива ввести с клавиатуры. 
Создать динамический массив из элементов, расположенных на главной диагонали матрицы и имеющих четное значение. 
Вычислить произведение элементов динамического массива.
Созданный массив и результат произведения вывести на экран.
Использовать функции.
*/

#include <iostream>
#include "..\Input\input.h"
using namespace std;

void DiagonalEvenFill(int** array, int* EvenDiagonal, int &N, int &M, int &EvenAmount) {

    for (int i = 0; i < N; i++) 
        for (int j = 0; j < M; j++) 
            if (i == j && array[i][j] != 0 && array[i][j] % 2 == 0) 
                EvenDiagonal[EvenAmount++] = array[i][j];
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
    for (int i = 0; i < N; i++) 
        array[i] = new int[M];
    
    // Ввод массива 
    cout << "\nВведите массив " << N << "x" << M << ": \n";
    array = input_arr2_int(array, N, M);

    int* DiagonalEven = new int[N]; // Диагональ матрицы с четными элементами
    int EvenAmount = 0; // Число четных элементов

    DiagonalEvenFill(array, DiagonalEven, N, M, EvenAmount); // Заполнение

    if (EvenAmount) {
        int p = 1; // Произведение четных элементов диагонали

        cout << "\nЧетные элементы на главной диагонали: \n";
        for (int i = 0; i < EvenAmount; i++) {
            cout << DiagonalEven[i] << " ";
            p *= DiagonalEven[i];
        }

        cout << "\nПроизведение: " << p << "\n";
    }
    else {
        cout << "На главной диагонали нет четных элементов";
    }
    
    for (int i = 0; i < N; i++) 
        delete[] array[i];
    delete[] array;
    delete[] DiagonalEven;

    return 0;
}

