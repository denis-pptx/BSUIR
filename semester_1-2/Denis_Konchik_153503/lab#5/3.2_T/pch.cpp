//
// pch.cpp
//

#include "pch.h"

void ZeroElements(int** array, int& N, int& M, int& amount, int* IndexI, int* IndexJ) {

    // ������� ���������� ������� ����� � ������� �� �����
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (array[i][j] == 0) {
                IndexI[amount] = i;
                IndexJ[amount++] = j;
            }
        }
    }
}
