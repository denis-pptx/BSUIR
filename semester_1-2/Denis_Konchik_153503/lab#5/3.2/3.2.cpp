// Лабораторная 5, задача 3.2. Выполнена: Кончик Д. С.

/*
Создать двумерный динамический массив вещественных чисел. 
Определить, встречаются ли среди них элементы с нулевым значением. 
Если встречаются такие элементы, то определить их индексы и общее количество. 
Переставить элементы этого массива в обратном порядке и вывести на экран.
Использовать функции.
*/

#include <iostream>
#include "..\Input\input.h"
#include <windows.h>
using namespace std;

/*
void ZeroElements(double** array, int &N, int &M, int &amount) {

    cout << "\nИндексы нулей: \n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (array[i][j] == 0) {
                cout << i << " " << j << "\n";
                amount++;
            }
        }
    }
    cout << "\nЧисло нулей: " << amount;
}

void ReverseArray(double** array, double** ArrayRev, int &N, int &M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ArrayRev[N - i - 1][M - j - 1] = array[i][j];
        }
    }
}

void Output(double** ArrayRev, int& N, int& M) {
    cout << "\n\nВ обратном порядке: \n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << ArrayRev[i][j] << " ";
        }
        cout << "\n";
    }
}
*/

int main()
{

    HMODULE lib = LoadLibrary(L"Dynamic3.2.dll");
    typedef void (*f1)(double** array, double** ArrayRev, int& N, int& M);
    typedef void (*f2)(double** array, int& N, int& M, int& amount);
    typedef void (*f3)(double** ArrayRev, int& N, int& M);

    f1 ReverseArray = (f1)GetProcAddress(lib, "ReverseArray");
    f2 ZeroElements = (f2)GetProcAddress(lib, "ZeroElements");
    f3 Output =       (f3)GetProcAddress(lib, "Output");

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

    int amount = 0; // Число нулевых элементов
    ZeroElements(array, N, M, amount); // Вывод нулей

    // Массив в обратном порядке
    double** ArrayRev = new double* [N];
    for (int i = 0; i < N; i++) {
        ArrayRev[i] = new double[M];
    }

    // Переставить массив в обратном порядке
    ReverseArray(array, ArrayRev, N, M);

    // Вывод массива
    Output(ArrayRev, N, M);

    // Удаление массивов
    for (int i = 0; i < N; i++) {
        delete[] ArrayRev[i];
    } delete[] ArrayRev;

    for (int i = 0; i < N; i++) {
        delete[] array[i];
    } delete[] array;

    FreeLibrary(lib);
    return 0;
}

