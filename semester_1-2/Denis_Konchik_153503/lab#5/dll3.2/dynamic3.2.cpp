#include "dynamic3.2.h"
#include <iostream>

extern "C" _declspec(dllexport)
void ZeroElements(double** array, int& N, int& M, int& amount) {

    std::cout << "\nИндексы нулей: \n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (array[i][j] == 0) {
                std::cout << i << " " << j << "\n";
                amount++;
            }
        }
    }
    std::cout << "\nЧисло нулей: " << amount;
}

extern "C" _declspec(dllexport)
void ReverseArray(double** array, double** ArrayRev, int& N, int& M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ArrayRev[N - i - 1][M - j - 1] = array[i][j];
        }
    }
}

extern "C" _declspec(dllexport)
void Output(double** ArrayRev, int& N, int& M) {
    std::cout << "\n\nВ обратном порядке: \n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cout << ArrayRev[i][j] << " ";
        }
        std::cout << "\n";
    }
}