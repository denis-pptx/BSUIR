//
// pch.cpp
//

#include "pch.h"
#include <cstring>
using namespace std;


string ElseTernary(int n) {

    // Перевод в троичную
    string ternary = ToTernaryStr(n);


    // Перевод в систему по условию

    // Если бит 0, то забираем на него
    // единицу у более старшего бита

    int P = find(ternary, "10");
    while (P != -1) {
        replace(ternary, P, "03");
        P = find(ternary, "10");
    }

    P = find(ternary, "20");
    while (P != -1) {
        replace(ternary, P, "13");
        P = find(ternary, "20");
    }

    P = find(ternary, "30");
    while (P != -1) {
        replace(ternary, P, "13");
        P = find(ternary, "30");
    }

    while (len(ternary) > 1 && ternary[0] == '0')
        erase(ternary, 0);

    if (len(ternary) == 0)
        ternary = "0";
    
    return ternary;
}


string ToTernaryStr(int n) {
    // Перевод из int в string троичную систему

    string ternary = "";
    while (n) {
        ternary = (char)(n % 3 + 48) + ternary;
        n /= 3;
    }

    return ternary;
}

int len(string str) {
    // Длина строки

    int count = 0;
    while (str[count] != '\0')
        count++;

    return count;
}

int find(string str, string f) {

    int pos = -1;

    for (int i = 0; i < len(str); i++) {
        if (str[i] == f[0]) {
            bool eq = true;
            int _i = i;
            for (int j = 0; j < len(f); j++) {
                if (f[j] != str[_i++]) {
                    eq = false;
                    break;
                }
            }

            if (eq) return i;
        }
    }

    return pos;
}

void replace(string& str, int pos, string on) {
    string NewStr;

    int j = 0;
    for (int i = pos; i < pos + len(on); i++)
        str[i] = on[j++];
}

void erase(string& str, int pos) {
    for (int i = pos; i < len(str); i++)
        str[i] = str[i + 1];
}


