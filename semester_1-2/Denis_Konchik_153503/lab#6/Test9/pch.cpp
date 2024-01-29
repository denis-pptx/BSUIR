//
// pch.cpp
//

#include "pch.h"
#include <cstring>
#include <string>
using namespace std;

void ReduceSigns(string& str) {
    bool repeat = true;
    do {
        repeat = false;

        // Замена +- на -
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '+' && str[i + 1] == '-') {
                str[i] = '-';
                str.erase(str.begin() + i + 1);
                repeat = true;
            }
        }

        // Замена -+ на -
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '-' && str[i + 1] == '+') {
                str[i] = '-';
                str.erase(str.begin() + i + 1);
                repeat = true;
            }
        }

        // Замена -- на +
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '-' && str[i + 1] == '-') {
                str[i] = '+';
                str.erase(str.begin() + i + 1);
                repeat = true;
            }
        }

        // Убираем плюсы, которые повторяются
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '+' && str[i + 1] == '+') {
                str.erase(str.begin() + i);
                repeat = true;
            }
        }

    } while (repeat);
}

bool isPossible(char x, char y) {


    if (isdigit(x) || x == '-' && isdigit(y) || x == '+' && isdigit(y))
        return true;

    return false;
}

double FuncSum(string str) {

    // Убрать повторы знаков
    ReduceSigns(str);

    double sum = 0; // Сумма чисел
    double digit = 0; // Промежуточное число

    size_t p = 0;
    while (str.length()) {

        if (isPossible(str[0], str[1])) {
            sum += stod(str, &p);

            // Удаляем символы, на которых остановился stod
            for (int j = 0; j < p; j++)
                str.erase(str.begin());
        }

        // Пока нет цифры, удаляем по сиволу
        while (str.length() && !isPossible(str[0], str[1])) {
            str.erase(str.begin());
        }

        p = 0;
    }


    return sum;
}