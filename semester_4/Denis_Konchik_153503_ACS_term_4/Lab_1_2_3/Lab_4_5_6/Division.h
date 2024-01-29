#pragma once

#include <iostream>
#include <string>
#include "Helpers.h"
using namespace std;

static void Division(string a, string b) {

    cout << "Деление\n";

    Print("a", a);
    Print("b", b);

    if (IsZero(b)) {
        throw string("Деление на ноль");
    }
    if (IsZero(a)) {
        cout << "a / b = 0\n";
        return;
    }

    bool SignBitA = SignBit(a), SignBitB = SignBit(b);
    int SignA = Sign(a), SignB = Sign(b);
    int ExpA = Exp(a), ExpB = Exp(b);
    int MantA = Mant(a), MantB = Mant(b);

    int S = SignA * SignB;
    int E = ExpA - ExpB;
    long long M = ((long long)MantA << 23) / MantB;

    if (E >= 128) {
        throw string("Переполнение порядка");
    }
    if (E <= -127) {
        throw string("Потеря значимости порядка");
    }

    if (M == 0) {
        throw string("M = 0 при делении");
    }

    // Нормализация
    while (M >= (1 << 24)) {
        throw string("Что-то пошло не так");
    }
    if ((M & (1 << 23)) == 0) {
        M <<= 1;
        E--;
        if (E <= -127) {
            cout << endl;
            throw string("Потеря значимости порядка");
        }
    }


    string ans(32, '0');
    SetSign(ans, S);
    SetExp(ans, E);
    SetMant(ans, M);
    Print("a / b", ans);
    return;
}
static void Division(float a, float b) {
    Division(String(a), String(b));
}
