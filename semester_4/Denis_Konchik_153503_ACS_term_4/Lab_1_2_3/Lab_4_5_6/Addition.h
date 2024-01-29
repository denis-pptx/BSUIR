#pragma once

#include <iostream>
#include <string>
#include "Helpers.h"
using namespace std;

void Addition(string a, string b) {
    cout << "Сложение" << endl;
    Print("a", a);
    Print("b", b);

    string ans = string(32, '0');

    if (!IsZero(a) && !IsZero(b)) {

        if (Exp(a) > Exp(b)) {
            cout << "Порядок 'a' выше порядка 'b'. Меняем 'a' и 'b' местами.\n";
            swap(a, b);
            Print("a", a);
            Print("b", b);
        }

        cout << "Включаем неявный старший разряд мантиссы.\n";

        int SignA = Sign(a), SignB = Sign(b);
        int ExpA = Exp(a), ExpB = Exp(b);
        int MantA = Mant(a), MantB = Mant(b);

        if (ExpA < ExpB) {
            cout << "Порядки чисел не равны. Делаем выравнивание порядков.\n";
            while (ExpA < ExpB) {
                ExpA++;
                MantA >>= 1;
            }
            if (ExpB < ExpA) {
                throw string("Ошибка в выравивании порядков.");
            }
        }

        cout << "a = " << (SignA == 1 ? "0" : "1") << " " << bitset<8>(ExpA + 127).to_string() << " " << bitset<24>(MantA).to_string() << endl;
        cout << "b = " << (SignB == 1 ? "0" : "1") << " " << bitset<8>(ExpB + 127).to_string() << " " << bitset<24>(MantB).to_string() << endl;

        
        if (MantA == 0) {
            cout << "a ≈ 0.0\n";
            ans = b;
        }
        else {
            int M = MantA * SignA + MantB * SignB;
            int E = ExpA;
            int S = 1;


            if (M != 0) {

                if (M < 0) {
                    S = -1;
                    M = -M;
                }

                // Нормализация
                while (M >= (1 << 24)) {
                    M >>= 1;
                    E++;
                    if (E >= 128) {
                        cout << endl;
                        throw string("Переполнение порядка");
                    }
                }
                while ((M & (1 << 23)) == 0) {
                    M <<= 1;
                    E--;
                    if (E <= -127) {
                        cout << endl;
                        throw string("Потеря значимости порядка");
                    }
                }
                cout << endl;

                SetSign(ans, S);
                SetExp(ans, E);
                SetMant(ans, M);
            }
        }
        

        
    }
    else {

        if (IsZero(a)) {
            ans = b;
        }
        else if (IsZero(b)) {
            ans = a;
        }
    }

    Print("a + b", ans);
    
    return;
}

void Addition(float a, float b) {
    Addition(String(a), String(b));
}