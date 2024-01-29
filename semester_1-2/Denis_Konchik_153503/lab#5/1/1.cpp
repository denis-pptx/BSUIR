// Лабораторная 5, задача 1. Выполнена: Кончик Д. С.

/*
[Вариант 14]
Составить программу определения координат седловой точки двумерного динамического массива B размерностью N x M. 
Размерность массива (N = 5, M = 4) ввести с клавиатуры. Значения элементов массива В ввести с клавиатуры.

Примечание. 
Элемент массива называется седловой точкой, если он является одновременно наименьшим в своей строке и наибольшим в своем столбце.
Определение координат седловой точки (номеров строки и столбца) оформить в виде функции для любых N и M. 
На экран вывести в виде матриц исходный массив, а также массив, размерностью N x M, в котором все элементы, кроме седловой точки, равны 0. 
Если седловая точка не обнаружена, вывести на экран текст СЕДЛОВОЙ ТОЧКИ НЕТ.
Использовать функции.
*/

#include <iostream>
#include "..\Saddle\saddle.h"
#include "..\Input\input.h"
using namespace std;

/*
bool Saddle(double** array, int i, int j, int M, int N) {
    // Максимальный элемент в столбце j
    int max = array[0][j];
    for (int k = 0; k < M; k++) {
        max = array[k][j] > max ? array[k][j] : max;
    }

    // Минимальный элемент в строке i
    int min = array[i][0];
    for (int k = 0; k < N; k++) {
        min = array[i][k] < min ? array[i][k] : min;
    }

    if (array[i][j] == max && array[i][j] == min)
        return true;
    else
        return false;
}


void answear(double** array, double** ZeroArr, int&i, int&j, int& N, int&M) {
    // Номер строки и столбца седлового элемента
    int iRow = i, jColumn = j;


    // Создание массива нулей
    ZeroArr = new double* [N];
    for (int i = 0; i < N; i++) {
        ZeroArr[i] = new double[M];
    }

    // Вывод по условию
    cout << "\nСедловая точка [" << iRow << "; " << jColumn << "]:\n";
    for (int a = 0; a < N; a++) {
        for (int b = 0; b < M; b++) {
            if (a == iRow && b == jColumn)
                ZeroArr[a][b] = array[a][b];
            else
                ZeroArr[a][b] = 0;

            cout << ZeroArr[a][b] << " ";
        }
        cout << "\n";
    }

    // Удаление массива с нулями
    for (int i = 0; i < N; i++) {
        delete[] ZeroArr[i];
    }
    delete[] ZeroArr;
    ZeroArr = 0;
}
*/

int main()
{

    setlocale(LC_ALL, "Rus");

    // Ввод данных
    cout << "Задайте размер массива.\n";
    cout << "Строки: "; int N = input_natural();
    cout << "Столбцы: "; int M = input_natural();

    // Создание массива
    double** array = new double* [N];
    for (int i = 0; i < N; i++) {
        array[i] = new double[M];
    }

    // Ввод массива 
    cout << "\nВведите массив " << N << "x" << M << ": \n";
    array = input_arr2_double(array, N, M);

    // Поиск седловой точки
    bool NoSaddle = true;

    double** ZeroArr = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (Saddle(array, i, j, N, M)) {
                NoSaddle = false;
                answear(array, ZeroArr, i, j, N, M); 
            }
        }
    }

    if (NoSaddle) 
        cout << "\nСедловых точек нет\n";
    

    for (int i = 0; i < N; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;

}

