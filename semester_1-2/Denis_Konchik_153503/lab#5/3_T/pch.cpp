//
// pch.cpp
//

#include "pch.h"

void DiagonalEvenFill(int** array, int* EvenDiagonal, int& N, int& M, int& EvenAmount) {

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (i == j && array[i][j] != 0 && array[i][j] % 2 == 0)
                EvenDiagonal[EvenAmount++] = array[i][j];
}