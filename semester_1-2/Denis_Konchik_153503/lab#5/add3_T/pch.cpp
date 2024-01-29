//
// pch.cpp
//

#include "pch.h"
int Foo(int n) {
    int divider = 1;
    for (int i = n; i > 0; i--) {
        if (n % i == 0 && i % 2 == 1) {
            divider = i;
            break;
        }
    }

    return divider;
}