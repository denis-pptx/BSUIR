//
// pch.cpp
//

#include "pch.h"
#define ll unsigned long long

ll Foo(ll k, ll n, ll m)
{
    // ���� ������� ��������, �� ��������� a^(n+1) = a * a^n, n - ������

    if (n == 0)
        return 1;
    else if (n % 2 == 1)
        return (k * Foo((k * k) % m, n / 2, m)) % m;
    else
        return Foo((k * k) % m, n / 2, m);

}