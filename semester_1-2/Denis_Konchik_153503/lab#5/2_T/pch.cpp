//
// pch.cpp
//

#include "pch.h"
bool NegativeCheck(int* array, int first, int last, bool negative) {

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

bool Half(int* array, int N) {

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