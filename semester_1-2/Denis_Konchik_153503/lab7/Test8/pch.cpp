//
// pch.cpp
//

#include "pch.h"
#define ull unsigned long long

ull AnsByNumber(int n) {
    ull num = 1; // Число в десятичной форме
    int N = 0; // Номер двудесятичного числа

    while (true) {
        // Если суффикс в бинарном коде равен числу в десятичной форме
        if (BinarySuffix(num) == num)
            N++;

        if (N == n)
            break;

        num++;

        // Если хотя бы одна цифра в числе не 0 или не 1
        for (int i = 0; i < len(num) - 1; i++) {
            if (!(DigitByNumber(num, i) == 0 || DigitByNumber(num, i) == 1)) {
                num -= num % power(10, i + 1);
                num += power(10, i + 1);
            }
        }
    }

    return num;
}

int DigitByNumber(ull number, int N) {
    // Цифра с конца по номеру (индекс с 0)
    return (number % power(10, N + 1) - (number % power(10, N))) / power(10, N);
}

int len(ull n) {
    // Число цифр в числе

    int symb = 0;
    while (n) {
        symb++;
        n /= 10;
    }
    return symb;
}

ull BinarySuffix(ull num) {
    // Перевести в бинарный код,
    // цифр столько же, сколько в num

    ull Binary = 0, BitNum = 0, k = 1;

    while (num && len(Binary) <= len(num)) {
        Binary += (num % 2) * k;
        num /= 2;
        k *= 10;
    }

    return Binary;
}

ull power(ull x, int n) {
    if (n == 0)
        return 1;
    else
        return x * power(x, n - 1);
}
