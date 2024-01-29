#pragma once

#include <iostream>
#include <string>
#include "Helpers.h"
#include "Addition.h"
using namespace std;

static void Subtraction(string a, string b) {
    cout << "Вычитание\n";
    Print("a", a);
    Print("b", b);
    Addition(a, Negate(b));
}
static void Subtraction(float a, float b) {
    Subtraction(String(a), String(b));
}
