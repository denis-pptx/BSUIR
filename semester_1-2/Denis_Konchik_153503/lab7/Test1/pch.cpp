//
// pch.cpp
//

#include "pch.h"
#define ull unsigned long long 

void FourteenToTernary(char* fourteen, char* three) {

    bool minus = fourteen[0] == '-' ? true : false;

    // Перевод в 10
    ull ten = 0;
    Reverse(fourteen);

    if (minus) fourteen[len(fourteen) - 1] = '\0';

    for (int i = 0; i < len(fourteen); i++)
        ten += CharToInt(fourteen[i]) * (ull)pow(14, i);

    // Перевод в 3

    if (ten == 0) {
        three[0] = '0';
        three[1] = '\0';
    }
    else {
        int j = 0;
        while (ten) {
            three[j++] = ten % 3 + '0';
            ten /= 3;
        } three[j] = '\0';

        if (minus) {
            three[j] = '-';
            three[j + 1] = '\0';
        }
    }

    Reverse(three);
}


int CharToInt(char x) {
    if (48 <= x && x <= 57)
        return x - '0';
    else if (65 <= x && x <= 68)
        return x - 55;
    else if (97 <= x && x <= 100)
        return x - 87;

    exit(0);
}

void Reverse(char* str) {
    // Реверс строки

    for (int i = 0; i < len(str) / 2; i++) {
        char temp = str[i];
        str[i] = str[len(str) - 1 - i];
        str[len(str) - 1 - i] = temp;
    }
}

int len(char* str) {
    // Длина строки

    int count = 0;
    while (str[count] != '\0')
        count++;

    return count;
}