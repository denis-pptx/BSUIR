#include "saddle.h"

// task1

bool Saddle(double** array, int i, int j, int M, int N) {
    // ������������ ������� � ������� j
    int max = array[0][j];
    for (int k = 0; k < M; k++) {
        max = array[k][j] > max ? array[k][j] : max;
    }

    // ����������� ������� � ������ i
    int min = array[i][0];
    for (int k = 0; k < N; k++) {
        min = array[i][k] < min ? array[i][k] : min;
    }

    if (array[i][j] == max && array[i][j] == min)
        return true;
    else
        return false;
}