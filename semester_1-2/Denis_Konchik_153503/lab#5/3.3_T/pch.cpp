//
// pch.cpp
//

#include "pch.h"

void sort_columns(int** array, int* mass, int& N, int& M, long long& sum, int& amount) {

    for (int j = 1; j < M; j += 2) {
        for (int i = 0; i < N; i++) {
            if (array[i][j] != 0 && array[i][j] % 2 != 0) {
                mass[amount++] = array[i][j];
                sum += array[i][j];
            }
        }
    }
}
