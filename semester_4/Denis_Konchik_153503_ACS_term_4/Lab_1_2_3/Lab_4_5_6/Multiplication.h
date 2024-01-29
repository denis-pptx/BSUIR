#pragma once

#include <iostream>
#include <string>
#include "Helpers.h"
using namespace std;

void Multiplication(string a, string b) {
    cout << "���������\n";
    Print("a", a);
    Print("b", b);
    
    if (IsZero(a)) {
        cout << "a * b = 0\n";
        return;
    }
    if (IsZero(b)) {
        cout << "a * b = 0\n";
        return;
    }

    int SignA = Sign(a), SignB = Sign(b);
    int ExpA = Exp(a), ExpB = Exp(b);
    int MantA = Mant(a), MantB = Mant(b);

    int S = SignA * SignB;
    int E = ExpA + ExpB;
    long long M = ((long long)MantA * MantB) >> 23;

    

    if (E >= 128) {
        throw string("������������ �������");
    }
    if (E <= -127) {
        throw string("������ ���������� �������");
    }

    if (M == 0) {
        throw string("�������� ������������ 0");
    }

    while (M >= (1 << 24)) {
        M >>= 1;
        E++;
        if (E >= 128) {
            cout << endl;
            throw string("������������ �������");
        }
    }
    if ((M & (1 << 23)) == 0) {
        throw string("���-�� ����� �� ���");
    }

    string ans(32, '0');
    SetSign(ans, S);
    SetExp(ans, E);
    SetMant(ans, M);
    Print("a * b", ans);
    return;
}

void Multiplication(float a, float b) {
    Multiplication(String(a), String(b));
}
