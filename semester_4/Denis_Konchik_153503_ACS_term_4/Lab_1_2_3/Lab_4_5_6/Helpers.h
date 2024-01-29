#pragma once

#include <string>
#include <bitset>
using namespace std;

float Float(string f) {
    unsigned int x = bitset<32>(f).to_ulong();
    return *((float*)&x);
}

string String(float f) {
    return bitset<32>(*((int*)&f)).to_string();
}

void Print(float f) {
    cout << String(f).insert(9, " ").insert(1, " ") << " = " << f << endl;
}

void Print(string f) {
    cout << f.insert(9, " ").insert(1, " ") << " = " << Float(f) << endl;
}

void Print(string s, float f) {
    cout << s << " = ";
    Print(f);
}

void Print(string s, string f) {
    cout << s << " = ";
    Print(f);
}

bool SignBit(string f) {
    return (f[0] == '1');
}

int Sign(string f) {
    return (SignBit(f) ? -1 : 1);
}

void SetSign(string& f, bool s) {
    f[0] = (s ? '1' : '0');
}

void SetSign(string& f, int s) {
    SetSign(f, ((s < 0) ? true : false));
}

int Exp(string f) {
    return (bitset<32>(f.substr(1, 8)).to_ulong() - 127);
}

void SetExp(string& f, int e) {
    if ((e <= -127) || (128 <= e)) {
        throw string("Порядок превышен");
    }
    f.replace(1, 8, bitset<8>(e + 127).to_string());
}

int Mant(string f) {
    return bitset<32>("1" + f.substr(9, 23)).to_ulong();
}

void SetMant(string& f, int e) {
    if ((e < 0) || ((1 << 24) <= e)) {
        throw string("Мантисса превышена");
    }
    if ((e & (1 << 23)) == 0) {
        throw string("Мантисса не начинается с 1");
    }
    f.replace(9, 23, bitset<23>(e ^ (1 << 23)).to_string());
}

bool IsZero(string f) {
    return count(f.begin() + 1, f.end(), '0') == 31;
}

string Negate(string f) {
    cout << "Отрицание\n";
    string ans = f;
    Print(" b", ans);
    ans[0] = '0' + '1' - ans[0];
    Print("-b", ans);
    return ans;
}