//
// pch.cpp
//

#include "pch.h"

int F(int n) {
    if (n % 10 > 0)
        return n % 10;
    else if (n == 0)
        return 0;
    else
        return F(n / 10);
}

