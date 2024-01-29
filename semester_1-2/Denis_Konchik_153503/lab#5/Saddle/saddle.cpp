#include "saddle.h"
#include <iostream>

bool Saddle(double** array, int i, int j, int M, int N) {
    // Максимальный элемент в столбце j
    double max = array[0][j];
    for (int k = 0; k < M; k++) {
        max = array[k][j] > max ? array[k][j] : max;
    }

    // Минимальный элемент в строке i
    double min = array[i][0];
    for (int k = 0; k < N; k++) {
        min = array[i][k] < min ? array[i][k] : min;
    }

    if (array[i][j] == max && array[i][j] == min)
        return true;
    else
        return false;
}

void answear(double** array, double** ZeroArr, int& i, int& j, int& N, int& M) {
    // Номер строки и столбца седлового элемента
    int iRow = i, jColumn = j;


    // Создание массива нулей
    ZeroArr = new double* [N];
    for (int i = 0; i < N; i++) {
        ZeroArr[i] = new double[M];
    }

    // Вывод по условию
    std::cout << "\nСедловая точка [" << iRow << "; " << jColumn << "]:\n";
    for (int a = 0; a < N; a++) {
        for (int b = 0; b < M; b++) {
            if (a == iRow && b == jColumn)
                ZeroArr[a][b] = array[a][b];
            else
                ZeroArr[a][b] = 0;

            std::cout << ZeroArr[a][b] << " ";
        }
        std::cout << "\n";
    }

    // Удаление массива с нулями
    for (int i = 0; i < N; i++) {
        delete[] ZeroArr[i];
    }
    delete[] ZeroArr;
    ZeroArr = 0;
}